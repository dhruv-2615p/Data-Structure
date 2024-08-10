#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree_t* Tree;
struct Tree_t{
    int key;
    Tree left;
    Tree right;
    int height;
    char* name;
};

Tree newTree(int key, Tree left, Tree right, char* name1){
    Tree tree = (Tree) calloc(1, sizeof(struct Tree_t));
    tree->key = key;
    tree->left = left;
    tree->right = right;
    tree->height = 1;
    tree->name = (char *) calloc(20, sizeof(char));
    strcpy(tree->name, name1);

    return tree;
}

int max(int a, int b){
    return a > b ? a : b;
}

int height(Tree tree){
    if(!tree)   return 0;

    return 1 + max(height(tree->left), height(tree->right));
}

int balenceFectore(Tree tree){
    if(!tree->left && !tree->right)   return 0;

    return height(tree->left) - height(tree->right);
}

Tree rightRotate(Tree y){
    Tree x = y->left;
    Tree t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = 1 + max(
            height(y->left), height(y->right)
    );

    x->height = 1 + max(
            height(x->left), height(x->right)
    );

    return x;
}

Tree leftRotate(Tree x){
    Tree y = x->right;
    Tree t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = 1 + max(
            height(x->left), height(x->right)
    );

    y->height = 1 + max(
            height(y->left), height(y->right)
    );

    return y;
}

Tree inseartAvl(Tree tree, int key, char* name){
    if(!tree)   return newTree(key, NULL, NULL, name);

    if(key < tree->key)
        tree->left = inseartAvl(tree->left, key, name);
    if(key < tree->key)
        tree->left = inseartAvl(tree->left, key, name);
    else if(key > tree->key)
        tree->right = inseartAvl(tree->right, key, name);

    tree->height = 1 + max(
            height(tree->left), height(tree->right)
    );

    int balence = balenceFectore(tree);

    if(balence > 1 && balenceFectore(tree->left) >= 0){
        tree = rightRotate(tree);
    }
    else if(balence < -1 && balenceFectore(tree->right) <= 0){
        tree = leftRotate(tree);
    }
    else if(balence > 1 && balenceFectore(tree->left) <= 0){
        tree->left = leftRotate(tree->left);
        tree = rightRotate(tree);
    }
    else if(balence < -1 && balenceFectore(tree->right) >= 0){
        tree->right = rightRotate(tree->right);
        tree = leftRotate(tree);
    }

    return tree;
}

void inOrder(Tree root){
 if(root != NULL) {
        inOrder(root->left);
        printf("Roll: %d, Name: %s\n", root->key, root->name);
        inOrder(root->right);
    }

}

int main() {
    Tree root = NULL;

    FILE *file = fopen("data_students.txt", "r");
    if (file == NULL) {
        printf("Could not open file data_students.txt");
        return 1;
    }
    int num;
    fscanf(file, "%d", &num);
    for (int i = 0; i < num; i++) {
        int roll;
        char name[50];
        fscanf(file, "%d%s", &roll, name);
        root = inseartAvl(root, roll, name);
    }
    fclose(file);
    printf("Preorder traversal of the constructed AVL tree is \n");
    inOrder(root);
    return 0;
}