#include <iostream>
#include <fstream>
#include <math.h>

struct Node {
    int value;
    int balance;
    struct Node* left;
    struct Node* right;
};

Node* p1, p2;
char c1;
int n;
int A[500];
int x;
int c = 0;
bool vr, hr;

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




void GoFromLeftToRight(Node* p)
{
    if (p != nullptr)
    {
        GoFromLeftToRight(p->left);
        std::cout << p->value << " - ";
        GoFromLeftToRight(p->right);
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


Node* AddToBtree(Node* p, int x)
{
    Node* q;
    if (p == nullptr)
    {
        p = new Node;
        p->value = x;
        p->left = nullptr;
        p->right = nullptr;
        p->balance = 0;
        vr = true;
        return p;
    }
    else
    {
        if (p->value > x)
        {
            p->left = AddToBtree(p->left, x);
            if (vr)
            {
                if (p->balance == 0)
                {
                    q = p->left;
                    p->left = q->right;
                    q->right = p;
                    p = q;
                    q->balance = 1;
                    vr = false;
                    hr = true;
                }
                else
                {
                    p->balance = 0;
                    hr = true;
                }
            }
            else
            {
                hr = false;
            }
        }
        else
        {
            if (p->value < x)
            {
                p->right = AddToBtree(p->right, x);
                if (vr)
                {
                    p->balance = 1;
                    vr = false;
                    hr = true;
                }
                else
                {
                    if (hr)
                    {
                        if (p->balance > 0)
                        {
                            q = p->right;
                            p->right = q->left;
                            p->balance = 0;
                            q->balance = 0;
                            q->left = p;
                            p = q;
                            vr = true;
                            hr = false;
                        }
                    }
                    else
                    {
                        hr = false;
                    }
                }
            }
        }
    }
    return p;
}

Node* BuildBTree(int A[], int n)
{
    int i;
    Node* p;
    Node* Root = new Node;
    Root->value = A[0];
    Root->left = nullptr;
    Root->right = nullptr;
    Root->balance = 0;
    for (i = 1; i < n; i++)
    {
        //p = Root;
        vr = false;
        hr = false;
        Root = AddToBtree(Root, A[i]);
    }
    return Root;
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
        std::cout << "4: Построить двоичное Б-дерево" << std::endl;
        std::cout << "5: Вычисление средней высоты дерева" << std::endl;
        std::cout << "6: Определить, является ли дерево деревом поиска" << std::endl;
        std::cout << "7: Поиск в дереве" << std::endl;
        std::cout << "8: Вывод дерева" << std::endl;
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
            p1 = BuildBTree(A, n);
            system("pause");
            break;
        case 5:
            std::cout << "Average tree height: " << avgtreeheight(p1) << std::endl;
            system("pause");
            break;
        case 6:
            std::cout << "Is search tree? : " << IsSearchTree(p1) << std::endl;
            system("pause");
            break;
        case 7:
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
        case 8:
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