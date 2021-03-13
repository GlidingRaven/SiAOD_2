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
int turns;
static bool rost;

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



static Node* LLTurn(Node* p)
{
    Node* q;
    q = p->left;
    q->balance = 0;
    p->balance = 0;
    p->left = q->right;
    q->right = p;
    return q;
}

static Node* LRTurn(Node* p)
{
    Node* q;
    Node* r;
    q = p->left;
    r = q->right;
    if (r->balance < 0)
    {
        p->balance = 1;
    }
    else
    {
        p->balance = 0;
    }
    if (r->balance > 0)
    {
        q->balance = -1;
    }
    else
    {
        q->balance = 0;
    }
    r->balance = 0;
    p->left = r->right;
    q->right = r->left;
    r->left = q;
    r->right = p;
    return p;
}


static Node* RRTurn(Node* p)
{
    Node* q;
    q = p->right;
    q->balance = 0;
    p->balance = 0;
    p->right = q->left;
    q->left = p;
    return q;
}

static Node* RLTurn(Node* p)
{
    Node* q;
    Node* r;
    q = p->right;
    r = q->left;
    if (r->balance > 0)
    {
        p->balance = -1;
    }
    else
    {
        p->balance = 0;
    }
    if (r->balance < 0)
    {
        q->balance = 1;
    }
    else
    {
        q->balance = 0;
    }
    r->balance = 0;
    p->right = r->left;
    q->left = r->right;
    r->left = p;
    r->right = q;
    return r;
}




static Node* AddToAVL(Node* p, int x)
{
    Node* p1;
    if (p == nullptr)
    {
        p = new Node;
        p->value = x;
        p->left = nullptr;
        p->right = nullptr;
        p->balance = 0;
        rost = true;
        return p;
    }
    else // 1 8 6 2
    {
        if (p->value > x)
        {
            p->left = AddToAVL(p->left, x);
            if (rost)
            {
                if (p->balance > 0)
                {
                    p->balance = 0;
                    rost = false;
                }
                else
                {
                    if (p->balance == 0)
                    {
                        p->balance = -1;
                    }
                    else
                    {
                        if (p->left->balance < 0)
                        {
                            p1 = p->left;
                            if (p1->balance == -1)
                            {
                                p = LLTurn(p);
                            }
                            else
                            {
                                p = LRTurn(p);
                            }
                            turns++;
                            rost = false;
                        }
                    }
                }
            }
        }
        else
        {
            p->right = AddToAVL(p->right, x);
            if (rost)
            {
                if (p->balance < 0)
                {
                    p->balance = 0;
                    rost = false;
                }
                else
                {
                    if (p->balance == 0)
                    {
                        p->balance = 1;
                    }
                    else
                    {
                        if (p->right->balance > 0)
                        {
                            p1 = p->right;
                            if (p1->balance == 1)
                            {
                                p = RRTurn(p);
                            }
                            else
                            {
                                p = RLTurn(p);
                            }
                            turns++;
                            rost = false;
                        }
                    }
                }
            }
        }
    }
    return p;
}

Node* BuildAVL(int A[], int n)
{
    int i;
    turns = 0;
    Node* Root = new Node;
    Root->value = A[0];
    Root->left = nullptr;
    Root->right = nullptr;
    Root->balance = 0;
    for (i = 1; i < n; i++)
    {
        rost = false;
        Root = AddToAVL(Root, A[i]);
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
        std::cout << "4: Построить АВЛ дерево" << std::endl;
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
            p1 = BuildAVL(A, n); //TODO
            std::cout << "Turns count: " << turns << std::endl;
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