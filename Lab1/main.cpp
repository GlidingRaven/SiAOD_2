#include <iostream>
#include <fstream>

struct Node {
    int value;
    struct Node *left;
    struct Node *right;
    
};

Node* addtree()
{
       Node* tree = new Node;
       tree->value = rand() % 100;
       tree->right = nullptr;
       tree->left = nullptr;
       return (tree);
}

void printtree(Node *tree)
{
    if (tree != NULL)
    {
        printtree(tree->left);
        std::cout << tree->value << " ";
        printtree(tree->right);
    }
}

int sizetree(Node *tree)
{
    if (tree != NULL)
        return(1 + sizetree(tree->left) + sizetree(tree->right));
    else
        return 0;
}

int heighttree(Node *tree)
{
    if (tree != NULL)
        return(1 + std::max(heighttree(tree->left), heighttree(tree->right)));
    else
        return 0;
}

int sumpathlentree(Node *tree, int L)
{
    if (tree != NULL)
        return(L + sumpathlentree(tree->left, L+1) + sumpathlentree(tree->right, L+1));
    else
        return 0;
}

int checksumtree(Node *tree)
{
    if (tree != NULL)
    {
        return(tree->value + checksumtree(tree->left) + checksumtree(tree->right));
    }
    else
        return 0;
}

int main ()
{
    Node* root = addtree();
    root->left = addtree();
    root->left->right = addtree();
    root->left->right->left = addtree();
    root->left->right->left->right = addtree();
    root->left->right->left->right->right = addtree();

    std::cout << "Tree size: " << sizetree(root) << std::endl;
    std::cout << "Tree height: "<< heighttree(root) << std::endl;
    std::cout << "Tree average height: " << sumpathlentree(root, 1)/sizetree(root) << std::endl;
    std::cout << "Tree checksum: "<< checksumtree(root) << std::endl;
    printtree(root);
    std::cout << std::endl;
    system("pause");
    return 0;
}