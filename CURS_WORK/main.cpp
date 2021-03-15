#include <iostream>
#include <fstream>
#include <math.h>
#include <windows.h>
#include <queue>
#include <string>
#define basesize 4000


struct record
{
    char a[30];
    unsigned short int b;
    char c[10];
    char d[22];
};

void printlist(std::queue<record> myqueue)
{
    int count=0;
    std::queue<record> temp;
    temp = myqueue;
    while (!temp.empty())
    {
        count++;
        std::cout << temp.front().a << " " << temp.front().b << " " << temp.front().c << " " << temp.front().d << std::endl;
        while (count % 20 == 0)
        {
            std::cout << "Continue? (y/n)" << std::endl;
            char choice;
            std::cin >> choice;
            if (choice == 'y')
            {
                break;
            }
            else
                if (choice == 'n')
                {
                    return;
                }
        }
        temp.pop();
    }
}

int getdigit(int n, int x) //returns specific digit, counting from end and 0
{
    for (int i = 0; i < x; i++)
    {
        n = n / 10;
    }

    return (n % 10);
}


int countdigit(int x)
{
    int n=0;
    while (x > 0)
    {
        x = x / 10;
        n++;
    }
    return n;
}

int maxdigitb(std::queue <record> myqueue)
{
    int max = 0;
    std::queue<record> temp;
    temp = myqueue;
    while (!temp.empty())
    {
        if (countdigit(temp.front().b) > max)
        {
            max = countdigit(temp.front().b);
        }
        temp.pop();
    }
    return max;
}

std::string getcapitals(char *a)
{
    std::string out = "";
    for (int i = 29; i >= 0; i--) //идем справа налево в фио
    {
        char d = a[i]; //
        if (d >= -128 && d <= -97) //если большая буква
        {
            out += d;
        }
    }
    //std::cout << out << std::endl;
    return out;
}

std::string getcapitalsreverse(char* a)
{
    std::string out = "";
    for (int i = 0; i <30; i++) //идем слева направо в фио
    {
        char d = a[i]; //
        if (d >= -128 && d <= -97) //если большая буква
        {
            out += d;
        }
    }
    //std::cout << out << std::endl;
    return out;
}

std::queue<record>* radixb(std::queue<record> *l, int t) // сортировка по b
{ 
  int d, m=1;
  std::queue<record> * out;
  std::queue<record> list[10];
  out=l;

  for (int j=0; j<t; j++) // разряды
  {
      for (int i = 0; i <= 9; i++) // обнуляем листы
          list[i] = {};
    
    while (!out->empty())
    {
        d = getdigit(out->front().b, j);
        list[d].push(out->front());
        out->pop();
    }
    for (int i = 0; i <= 9; i++)
    {
        while (!list[i].empty())
        {
            out->push(list[i].front());
            list[i].pop();
        }
    }

  }
  return (out);
}


std::queue<record> radixa(std::queue<record> l) // сортировка по a
{
    int d, m = 1;
    std::queue<record> out;
    std::queue<record> list[33];
    out = l;
    int counter = 0;
    for (int j = 2; j >= 0; j--) // разряды
    {
        for (int i = 0; i <= 32; i++) // обнуляем листы
            list[i] = {};
        while (!out.empty())
        {
            counter = 2;
            for (int i = 29; i >= 0; i--) //идем справа налево в фио
            {
                d = (int)out.front().a[i]; //
                if (d >= -128 && d <= -97) //если большая буква
                {                   
                    if (counter == j) // смотрим какая букву ищем на данный момент
                    {
                    //std::cout << "BREAK " << d+128 << " " ; //для профессионального дебага
                    break;
                    }
                    else
                    {
                        counter--; // если изменился разряд
                    }
                }
            }
            
            d += 128; //смещение
            //std::cout << out.front().a << " " << j << " " << (int)out.front().a[j] << std::endl; // профессиональный дебаг
            list[d].push(out.front());
            out.pop();
        }
        for (int i = 0; i <= 32; i++)
        {
            while (!list[i].empty())
            {
                //std::cout << list[i].front().a << counter << std::endl; // еще дебаг
                out.push(list[i].front());
                list[i].pop();
            }
        }

    }

    return (out);
}

std::queue<record> radixab(std::queue<record> l)
{
    std::queue<record> newqueue; // массив для вывода
    std::queue<record> tempqueue; // массив для сохранения подсписков
    while (!l.empty())
        {
        record temp = l.front();
        record tempnext;
        l.pop();
        if (!l.empty())
        {
            tempnext = l.front();
        }

        if (getcapitals(temp.a) == getcapitals(tempnext.a))
        {
            tempqueue.push(temp);
        }
        else
        {
            tempqueue.push(temp);
            tempqueue = *radixb(&tempqueue, maxdigitb(tempqueue));
            while (!tempqueue.empty())
            {
                newqueue.push(tempqueue.front());
                tempqueue.pop();
            }
        }
    }
    return newqueue;
}


std::queue<record> binarysearch(std::queue<record> l, char* query1)
{
    char* query = new char[50];
    CharToOemA(query1, query);
    record* A = new record[4000];
    for (int i = 0; i < 3999; i++)
    {
        A[i] = l.front();
        l.pop();
        //std::cout << getcapitalsreverse(A[i].a) << std::endl;
    }

    int L = 0;
    int R = 3999;
    int m;
    while (L < R)
    {
        m = (L + R) / 2;
        if (getcapitalsreverse(A[m].a) < query)
        {
            L = m + 1;
        }
        else
        {
            R = m;
        }
    }
    if ((getcapitalsreverse(A[R].a).compare(query)==0))
    {
        std::queue<record> newqueue;
        while (true)
        {
            if (R + 1 < 4000) // R = 3998
            {
                if (getcapitalsreverse(A[R].a) == getcapitalsreverse(A[R + 1].a))
                {
                    newqueue.push(A[R]);
                    R++;
                }
                else
                {
                    newqueue.push(A[R]);
                    break;
                }
            }
            else
            {
                newqueue.push(A[R]);
                break;
            }

        }
        return newqueue;
    }
    else
    {
        std::queue<record> newqueue;
        return newqueue;
    }

    
}


int main()
{
    FILE* fp;
    fp = fopen("testBase3.dat", "rb");
    std::queue <record> myqueue;
    record* temp = new record;
    for (int i = 0; i < basesize; i++)
    {
        int x = fread(temp, sizeof(record), 1, fp);
        myqueue.push(*temp);
    }

    //printlist(myqueue); //работает
    //printlist(*radixb(&myqueue, maxdigitb(myqueue))); работает
    //printlist(radixa(myqueue));
    //printlist(myqueue);
    myqueue = radixa(myqueue);
    myqueue = radixab(myqueue);
    //printlist(radixab(myqueue));

    std::queue<record> result;
    char query[5] = "АВА";
    result = binarysearch(myqueue, query);
    printlist(result);

    


    system("pause");
    return 0;
}