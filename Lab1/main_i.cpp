#include <iostream>
#include <fstream>

struct Node {
    int value;
    struct Node *left;
    struct Node *right;
    
};

Node* addtree(int x)
{
       Node* tree = new Node;
       tree->value = x;
       tree->right = NULL;
       tree->left = NULL;
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
    std::fstream file(".\\data.txt");
    int currvalue = 1;
    Node* root = addtree(0);
    Node* curr = root;
    while(!file.eof())
    {
        int direction;
        file >> direction;
        if (direction==0)
        {
            curr->left = addtree(currvalue);
            curr = curr->left;
        }
        else
        {
            curr->right = addtree(currvalue);
            curr = curr->right;
        }
    currvalue++;
    }

    std::cout << "Tree size: " << sizetree(root) << std::endl;
    std::cout << "Tree height: "<< heighttree(root) << std::endl;
    std::cout << "Tree average height: " << sumpathlentree(root, 1)/sizetree(root) << std::endl;
    std::cout << "Tree checksum: "<< checksumtree(root) << std::endl;
    std::cout << "Tree traversal (left-right): ";
    printtree(root);
}