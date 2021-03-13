#include <iostream>
#include <fstream>
#include <math.h>

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};

Node* p1, p2;
char c1;
int n;
int A[500];
int x;
int c = 0;

void createmass(int t, int n, int A[])
{
    for (int i = 0; i < n; i++)
    {
        if (t == 1) A[i] = i;
        else if (t == 2) A[i] = n - i;
        else if (t == 3) A[i] = rand() / 100;
        std::cout << A[i] << ' ';
    }
    std::cout << std::endl;
    system("pause"); // нажмите любую клавишу
}


void quicksort(int arr[], int beg, int end)
{
    int i = beg;
    int j = end;
    int mid = arr[(i + j) / 2];
    while (i <= j)
    {
        while (arr[i] < mid)
        {
            i++;
        }
        while (arr[j] > mid)
        {
            j--;
        }
        if (i <= j)
        {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (beg < j)
        quicksort(arr, beg, j);
    if (i < end)
        quicksort(arr, i, end);

}

Node* AddToSDP(Node* p, int x)
{
    if (p == nullptr)
    {
        Node* p = new Node;
        p->value = x;
        p->right = nullptr;
        p->left = nullptr;
        return p;
    }
    else
    {
        if (x < p->value)
        {
            p->left = AddToSDP(p->left, x);
        }
        else
        {
            p->right = AddToSDP(p->right, x);
        }
    }

    return p;
}


Node* BuildSDP(int A[], int n) //{построение СДП}
{
    Node* temp = nullptr;
    Node* Root = new Node;
    Root->value = A[0];
    Root->left = nullptr;
    Root->right = nullptr;
    for (int i = 1; i < n; i++)
    {
        temp = Root;
        temp = AddToSDP(temp, A[i]);
    }
    return Root;
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


Node* BuildISDP(int L, int R, int A[])
{
    int m;
    if (L > R)
    {
        return nullptr;
    }
    {
        m = (L + R) / 2;
        Node* p = new Node;
        p->value = A[m];
        p->left = BuildISDP(L, m - 1, A);
        p->right = BuildISDP(m + 1, R, A);
        return p;
    }
}

int sizetree(Node* tree)
{
    if (tree != NULL)
        return(1 + sizetree(tree->left) + sizetree(tree->right));
    else
        return 0;
}

int heighttree(Node* tree)
{
    if (tree != NULL)
        return(1 + std::max(heighttree(tree->left), heighttree(tree->right)));
    else
        return 0;
}

int sumpathlentree(Node* tree, int L)
{
    if (tree != NULL)
        return(L + sumpathlentree(tree->left, L + 1) + sumpathlentree(tree->right, L + 1));
    else
        return 0;
}

int avgtreeheight(Node* tree)
{
    return (sumpathlentree(tree, 1) / sizetree(tree));
}


bool IsSearchTree(Node* p)
{
    if (p != nullptr and (((p->left != nullptr) and ((p->value <= p->left->value) or (!IsSearchTree(p->left)))) or ((p->right != nullptr) and \
        ((p->value >= p->right->value) or (!IsSearchTree(p->right)))))) return false;
    else
        return true;
}

bool SearchInTree(Node* p, int x)
{
    while (p != nullptr)
    {
        if (p->value < x)
        {
            p = p->right;
            c++;
        }
        else
            if (p->value > x)
            {
                p = p->left;
                c++;
            }
            else break;
    }
    if (p != nullptr)
    {
        return true;
    }
    else
    {
        return false;
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
        std::cout << "1: Заполнить массив упорядоченными числами" << std::endl;
        std::cout << "2: Заполнить массив числами в обратном порядке" << std::endl;
        std::cout << "3: Заполнить массив случайными числами" << std::endl;
        std::cout << "4: Построить случайное дерево поиска" << std::endl;
        std::cout << "5: Построить идеально сбалансированное дерево поиска" << std::endl;
        std::cout << "6: Вычисление средней высоты дерева" << std::endl;
        std::cout << "7: Определить, является ли дерево деревом поиска" << std::endl;
        std::cout << "8: Поиск в дереве" << std::endl;
        std::cout << "9: Вывод дерева" << std::endl;
        std::cout << "0: Выход" << std::endl;
        std::cout << "ВАШ ВЫБОР:";
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            createmass(1, n, A);
            break;
        case 2:
            createmass(2, n, A);
            break;
        case 3:
            createmass(3, n, A);
            break;
        case 4:
            p1 = BuildSDP(A, n);
            system("pause");
            break;
        case 5:
            quicksort(A, 0, n - 1);
            p1 = BuildISDP(0, n - 1, A);
            system("pause");
            break;
        case 6:
            std::cout << "Average tree height: " << avgtreeheight(p1) << std::endl;
            system("pause");
            break;
        case 7:
            std::cout << "Is search tree? : " << IsSearchTree(p1) << std::endl;
            system("pause");
            break;
        case 8:
            std::cout << "Enter search query: ";
            std::cin >> x;
            if (SearchInTree(p1, x))
            {
                std::cout << "Search successfull, operations count: " << c << std::endl;
            }
            else
            {
                std::cout << "Search failed " << std::endl;
            }
            system("pause");
            break;
        case 9:
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