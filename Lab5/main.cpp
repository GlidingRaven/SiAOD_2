#include <iostream>
#include <fstream>
#include <math.h>

struct Node {
    int value;
    int weight;
    struct Node* left;
    struct Node* right;
};

Node* p1, p2;
char c1;
int n;
int A[500];
int B[500];
int x;
int c = 0;
bool vr, hr;

void createmass(int t, int n, int C[], int maxvalue)
{
    for (int i = 0; i < n; i++)
    {
        if (t == 1) C[i] = i+1;
        else if (t == 2) C[i] = n - i;
        else if (t == 3) C[i] = rand() % maxvalue + 1;
        std::cout << C[i] << ' ';
    }
    std::cout << std::endl;
    system("pause"); // нажмите любую клавишу
}


void GoFromLeftToRight(Node* p)
{
    if (p != nullptr)
    {
        GoFromLeftToRight(p->left);
        std::cout << p->value << " - ";
        GoFromLeftToRight(p->right);
    }
}


Node* AddToSDP(Node* p, int x, int w)
{
    if (p == nullptr)
    {
        Node* p = new Node;
        p->value = x;
        p->right = nullptr;
        p->left = nullptr;
        p->weight = w;
        return p;
    }
    else
    {
        if (x < p->value)
        {
            p->left = AddToSDP(p->left, x, w);
        }
        else
        {
            if (x > p->value)
            {
                p->right = AddToSDP(p->right, x, w);
            }
            else return p; // dont add existing element
        }
    }
    return p;
}

Node* BuildDOP_A1(int A[], int B[], int n)
{
    Node* p;
    int i,j;
    Node* Root;
    bool Used[500];
    int max;
    int Index;

    Root = nullptr;
    for (i = 0; i < n; i++)
    {
        Used[i] = false;
    }
    for (i = 0; i < n; i++)
    {
        p = Root;
        max = -1;
        Index = 0;
        for (j = 0; j < n; j++)
        {
            if ((B[j] > max) && (Used[j] == false))
            {
                max = B[j];
                Index = j;
            }
        }
        Used[Index] = true;
        if (i == 0)
        {
            Root = AddToSDP(Root, A[Index], B[Index]);
        }
        else
        {
            p = AddToSDP(p, A[Index], B[Index]);
        }
    }
    return Root;
}

Node* BuildDOP_A2(Node* Root, int A[], int B[], int n, int L, int R)
{
    int i;
    float w = 0;
    //int w = 0;
    int sum = 0;
    bool first = true;
    Node* p;
    if (L <= R)
    {
        for (i = L; i <= R; i++)
        {
            w += B[i];
        }
        i = L;

        while ((i <= R) && (!((sum < w / 2) && (sum + B[i] >= w / 2))))
        {
            sum += B[i];
            i++;
        }

        p = Root;
        p = AddToSDP(p, A[i], B[i]);
        p = BuildDOP_A2(p, A, B, n, L, i-1);
        p = BuildDOP_A2(p, A, B, n, i + 1, R);
        if (first)
        {
            Root = p;
            first = false;
        }
    }
    return Root;
}

float GetAverageWeightedHeight(Node* p, int h)
{
    if (p == nullptr)
    {
        return 0;
    }
    else
    {
        return (p->weight*h + GetAverageWeightedHeight(p->left, h + 1) \
            + GetAverageWeightedHeight(p->right, h + 1));
    }
}

float GetWeight(Node* p)
{
    if (p == nullptr)
    {
        return 0;
    }
    else
    {
        return(p->weight + GetWeight(p->left) + GetWeight(p->right));
    }
}

int main()
{
    system("chcp 1251");
    std::cout << "Введите число элементов дерева" << std::endl;
    int n;
    std::cin >> n;

    while (true)
    {
        std::cout << "1: Заполнить массив данных упорядоченными числами" << std::endl;
        std::cout << "2: Заполнить массив данных числами в обратном порядке" << std::endl;
        std::cout << "3: Заполнить массив данных случайными числами" << std::endl;
        std::cout << "4: Заполнить массив весов упорядоченными числами" << std::endl;
        std::cout << "5: Заполнить массив весов числами в обратном порядке" << std::endl;
        std::cout << "6: Заполнить массив весов случайными числами" << std::endl;
        std::cout << "7: Построить ДОП методом А1" << std::endl;
        std::cout << "8: Построить ДОП методом А2" << std::endl;
        std::cout << "9: Вычисление средневзвешенной высоты дерева" << std::endl;
        std::cout << "10: Вывод дерева" << std::endl;
        std::cout << "0: Выход" << std::endl;
        std::cout << "ВАШ ВЫБОР:";
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            createmass(1, n, A,n);
            break;
        case 2:
            createmass(2, n, A,n);
            break;
        case 3:
            createmass(3, n, A,n);
            break;
        case 4:
            createmass(1, n, B, 10);
            break;
        case 5:
            createmass(2, n, B, 10);
            break;
        case 6:
            createmass(3, n, B, 10);
            break;
        case 7:
            p1 = nullptr;
            p1 = BuildDOP_A1(A, B, n);
            system("pause");
            break;
        case 8:
            p1 = nullptr;
            p1 = BuildDOP_A2(p1, A,B, n, 0,n-1);
            system("pause");
            break;
        case 9:
            std::cout << "Средневзвешенная высота дерева - " << GetAverageWeightedHeight(p1, 0) / GetWeight(p1) << std::endl;
            system("pause");
            break;
        case 10:
            GoFromLeftToRight(p1);
            std::cout << std::endl;
            system("pause");
            break;
        case 0:
            return 0;
            break;
        default:
            break;
        }

    }
}