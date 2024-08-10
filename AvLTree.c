#include <stdio.h>
#include <stdlib.h>

typedef struct Tree_t *Tree;
struct Tree_t
{
    int key;
    Tree left;
    Tree right;
    int height;
};

Tree newTree(int key, Tree left, Tree right)
{
    Tree tree = (Tree)calloc(1, sizeof(struct Tree_t));
    tree->key = key;
    tree->left = left;
    tree->right = right;
    tree->height = 1;

    return tree;
}

#define max(a, b) (((a) > (b)) ? (a) : (b))

int height(Tree tree)
{
    if (!tree)
        return 0;

    return 1 + max(height(tree->left), height(tree->right));
}

int balenceFectore(Tree tree)
{
    if (!tree->left && !tree->right)
        return 0;

    return height(tree->left) - height(tree->right);
}

Tree rightRotate(Tree y)
{

    Tree x = y->left;
    Tree t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = 1 + max(
                        height(y->left), height(y->right));

    x->height = 1 + max(
                        height(x->left), height(x->right));

    return x;
}

Tree leftRotate(Tree x)
{

    Tree y = x->right;
    Tree t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = 1 + max(
                        height(x->left), height(x->right));

    y->height = 1 + max(
                        height(y->left), height(y->right));

    return y;
}

Tree inseartAvl(Tree tree, int key)
{
    if (!tree)
        return newTree(key, NULL, NULL);

    if (key < tree->key)
        tree->left = inseartAvl(tree->left, key);
    else if (key > tree->key)
        tree->right = inseartAvl(tree->right, key);

    tree->height = 1 + max(
                           height(tree->left), height(tree->right));

    int balence = balenceFectore(tree);

    if (balence > 1 && balenceFectore(tree->left) >= 0)
    {
        tree = rightRotate(tree);
    }
    else if (balence < -1 && balenceFectore(tree->right) <= 0)
    {
        tree = leftRotate(tree);
    }
    else if (balence > 1 && balenceFectore(tree->left) <= 0)
    {
        tree->left = leftRotate(tree->left);
        tree = rightRotate(tree);
    }
    else if (balence < -1 && balenceFectore(tree->right) >= 0)
    {
        tree->right = rightRotate(tree->right);
        tree = leftRotate(tree);
    }

    return tree;
}

Tree findMinInBst(Tree tree)
{
    if (!tree)
        return NULL;

    for (; tree->left; tree = tree->left)
        ;

    return tree;
}

Tree deleteAVL(Tree tree, int key)
{
    if (!tree)
        return NULL;

    if (key < tree->key)
        tree->left = deleteAVL(tree->left, key);

    else if (key > tree->key)
        tree->right = deleteAVL(tree->right, key);
    else
    {
        if (!tree->left && !tree->right)
        {
            free(tree);
            return NULL;
        }
        else if (!tree->left)
        {
            Tree t = tree;
            tree = tree->right;
            free(t);
        }
        else if (!tree->right)
        {
            Tree t = tree;
            tree = tree->left;
            free(t);
        }
        else
        {
            Tree successor = findMinInBst(tree->right);
            tree->key = successor->key;
            tree->right = deleteAVL(tree->right, successor->key);
        }
    }
    tree->height = 1 + max(
                           height(tree->left), height(tree->right));

    int balence = balenceFectore(tree);

    if (balence > 1 && balenceFectore(tree->left) >= 0)
    {
        tree = rightRotate(tree);
    }
    else if (balence < -1 && balenceFectore(tree->right) <= 0)
    {
        tree = leftRotate(tree);
    }
    else if (balence > 1 && balenceFectore(tree->left) <= 0)
    {
        tree->left = leftRotate(tree->left);
        tree = rightRotate(tree);
    }
    else if (balence < -1 && balenceFectore(tree->right) >= 0)
    {
        tree->right = rightRotate(tree->right);
        tree = leftRotate(tree);
    }

    return tree;
}

int main()
{
    int n = 15;
    int *arr = (int *)calloc(n, sizeof(int));

    Tree avl = NULL;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 900 + 100;
        printf("Going to insert: %d\n", arr[i]);

        avl = inseartAvl(avl, arr[i]);
        printf("Inserted: %d\n", arr[i]);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        printf("Going to delete: %d\n", arr[i]);

        avl = deleteAVL(avl, arr[i]);
        printf("Deleted: %d\n", arr[i]);
    }

    return 0;
}