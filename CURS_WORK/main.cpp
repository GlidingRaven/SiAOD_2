#include <iostream>
#include <fstream>
#include <math.h>
#include <windows.h>
#include <queue>
#include <string>
#define basesize 4000


struct record
{
    char author[12];
    char title[32];
    char publisher[16];
    short int year;
    short int num_of_page;

};

void printlist(std::queue<record> myqueue)
{

    int count=0;
    std::queue<record> temp;
    temp = myqueue;
    if (myqueue.empty())
    {
        std::cout << "Queue is empty" << std::endl;
    }
    while (!temp.empty())
    {
        count++;
        std::cout << temp.front().author << " " << temp.front().title << " " << temp.front().publisher << " " << temp.front().year << " " << temp.front().num_of_page <<std::endl;
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
        if (countdigit(temp.front().year) > max)
        {
            max = countdigit(temp.front().year);
        }
        temp.pop();
    }
    return max;
}

std::string firstthree(char *a)
{
    std::string out = "";
    for (int i = 0; i < 3; i++) //идем слева направо 3 символа в фио
    {
        out += a[i];
    }
    std::cout << std::endl;
    return out;
}

std::queue<record>* radixb(std::queue<record> *l) // сортировка по b
{ 
  int d, m=1;
  std::queue<record> * out;
  std::queue<record> list[10];
  out=l;

  for (int j=0; j<3; j++) // разряды
  {
      for (int i = 0; i <= 9; i++) // обнуляем листы
          list[i] = {};
    
    while (!out->empty())
    {
        d = getdigit(out->front().year, j);
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
                d = (int)out.front().author[j]; //
                if (d >= -128 && d <= -97) //если большая буква
                    d += 128;
                else if (d >= -96 && d <= -81) //просто жесть
                    d += 96;
                else if (d >= -32 && d <= -17) // вот это кодировочка
                    d += 48;

            list[d].push(out.front());
            out.pop();
        }
        for (int i = 0; i <= 32; i++)
        {
            while (!list[i].empty())
            {
                out.push(list[i].front());
                list[i].pop();
            }
        }

    }

    return (out);
}

std::queue<record> radixba(std::queue<record> l)
{
    std::queue<record> newqueue; // массив для вывода
    std::queue<record> tempqueue; // массив для сохранения подсписков
    while (!l.empty())
    {
        record temp = l.front();
        int tempnextyear;
        l.pop();
        if (!l.empty())
        {
            tempnextyear = l.front().year;
        }
        else
        {
            tempnextyear = 0;
        }

        if (l.size() == 1 || (temp.year == tempnextyear))
        {
            tempqueue.push(temp);
        }
        else
        {
            tempqueue.push(temp);
            tempqueue = radixa(tempqueue);
            while (!tempqueue.empty())
            {
                newqueue.push(tempqueue.front());
                tempqueue.pop();
            }
        }
    }
    return newqueue;
}


std::queue<record> binarysearch(std::queue<record> l, int query)
{
    record* A = new record[4000];
    for (int i = 0; i < 3999; i++)
    {
        A[i] = l.front();
        l.pop();
    }

    int L = 0;
    int R = 3999;
    int m;
    while (L < R)
    {
        m = (L + R) / 2;
        if (A[m].year < query)
        {
            L = m + 1;
        }
        else
        {
            R = m;
        }
    }
    if (A[R].year == query)
    {
        std::queue<record> newqueue;
        while (true)
        {
            if (R + 1 < 4000) // R = 3998
            {
                if (A[R].year == A[R+1].year)
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
    fp = fopen("testBase1.dat", "rb");
    std::queue <record> myqueue;
    record* temp = new record;
    for (int i = 0; i < basesize; i++)
    {
        int x = fread(temp, sizeof(record), 1, fp);
        myqueue.push(*temp);
    }

    //printlist(myqueue); //работает
    //printlist (*radixb(&myqueue)); //работает
    //printlist(radixa(myqueue));
    //myqueue = radixa(myqueue);
    //printlist(myqueue);
    //myqueue = radixab(myqueue);
    //printlist(radixab(myqueue));
    //std::queue<record> result;
    //result = binarysearch(myqueue, query);
    //printlist(result);

    //myqueue = (*radixb(&myqueue));
    //myqueue = radixba(myqueue);
    //printlist(myqueue);
    //printlist(binarysearch(myqueue, 1900));

    while (true)
    {
        int choice;
        std::cout << "1. Print queue" << std::endl;
        std::cout << "2. Sort by year and author" << std::endl;
        std::cout << "3. Perform quick search" << std::endl;
        std::cout << "0. Exit" << std::endl;
        
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            printlist(myqueue);
            break;
        }
        case 2:
        {
            printlist(radixba(*radixb(&myqueue)));
            break;
        }
        case 3:
        {
            int query;
            std::cout << "Enter your query (date)" << std::endl;
            std::cin >> query;
            printlist(binarysearch((radixba(*radixb(&myqueue))), query));
            break;
        }
        case 0:
            return 0;
            break;
        default:
            std::cout << "Input error" << std::endl;
            break;
        }
    }


    system("pause");
    return 0;
}