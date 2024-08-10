#include<stdio.h>
#include<stdlib.h>
typedef struct Tree_t* Tree;
struct Tree_t{
    int key;
    Tree parent;
    Tree left;
    Tree right;
};


int _print_t(Tree tree, int is_left, int offset, int depth, char s[20][255]){
    char b[20];
    int width = 5;
    if(!tree) return 0;
    sprintf(b, "(%03d)", tree->key);
    
    int left = _print_t(tree->left, 1, offset, depth + 1, s);
    int right = _print_t(tree->right, 0, offset + width + left, depth + 1, s);

    for(int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];
    if(depth && is_left){
        for(int i = 0; i < width + right; i++){
            s[depth - 1 ][offset + left + width/2 + i] = '-';
        }
        s[depth - 1][offset + left + width/2] = '.';
    }else if(depth && !is_left){
        for(int i = 0; i < width + left; i++){
            s[depth - 1][offset - width/2 + i] = '-';
        }
        s[depth - 1][offset + left + width/2] = '.';
    }
    return left + width + right;
}

void print_tree(Tree tree){
    char s[20][255];
    for(int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");
    _print_t(tree, 0, 0, 0, s);
    int flag = 0;
    for(int i = 0; i < 20 && !flag; i++){
        printf("%s\n", s[i]);
        flag = 1;
        for(int j = 0; j < 255; j++){
            if(s[i][j] == '.' || s[i][j] == '(' || s[i][j] == ')' || s[i][j] == '-'){
                flag = 0;
                break;
            }
        }
    }
}
Tree newTree(Tree parent, int key, Tree left, Tree right){
    Tree tree = (Tree) calloc(1, sizeof(struct Tree_t));
    tree->parent = parent;
    tree->key = key;
    tree->left = left;
    tree->right = right;

    return tree;
}

Tree insertToBSTRecusion(Tree tree, int key, Tree parent){
    if(!tree) return newTree(parent, key, NULL, NULL);

    if(tree->key < key) tree->right = insertToBSTRecusion(tree->right, key, tree);
    else tree->left = insertToBSTRecusion(tree->left, key, tree);

    return tree;
}

int main(){
    int a[10] = {5, 4, 6, 3, 7, 8, 1, 9, 2, 0};
    Tree bst = NULL;
    for(int i = 0; i < 10; i++){
        bst = insertToBSTRecusion(bst, a[i], NULL);
    }
    print_tree(bst);
}
