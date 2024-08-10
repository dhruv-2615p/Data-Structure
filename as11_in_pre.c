#include <stdio.h>
#include <stdlib.h>
#include "drawing.c"


Tree newTree(Tree parent, int key, Tree left, Tree right){
    Tree tree = (Tree) calloc(1, sizeof(struct Tree_t));
    tree->parent = parent;
    tree->left = left;
    tree->key = key;
    tree->right = right;

    return tree;
}

int linearSearch(int inOrder[], int inStart, int inEnd, int key){
    for(int i = inStart; i <= inEnd; i++){
        if(inOrder[i] == key)
            return i;
    }

    return -1;
}

Tree helper(int inOrder[], int preOrder[], int inStart, int inEnd, int *pPreIndex){
    if(inStart > inEnd)    return NULL;

    Tree tree = newTree(NULL, preOrder[*pPreIndex], NULL, NULL);
    (*pPreIndex)++;

    int index = linearSearch(inOrder, inStart, inEnd, tree->key);
    tree->left = helper(inOrder, preOrder, inStart, index - 1, pPreIndex);
    tree->right = helper(inOrder, preOrder, index + 1, inEnd, pPreIndex);

    if(tree->left)  tree->left->parent = tree;
    if(tree->right) tree->right->parent = tree;
    
    return tree;
}

Tree makeTree(int n, int inOrder[], int preOrder[]){
    int inStart = 0;
    int inEnd = n - 1;
    int preIndex = 0;

    return helper(inOrder, preOrder, inStart, inEnd, &preIndex);
}

int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int inOrder[n];
    printf("Enter elements for in-Order: \n");
    for(int i = 0; i < n; i++){
        scanf("%d", &inOrder[i]);
    }

    int pre[n];
    printf("Enter elements for pre order: \n");
    for(int i = 0; i < n; i++){
        scanf("%d", &pre[i]);
    }

    Tree binary = makeTree(n, inOrder,pre);
    print_tree(binary);

    return 0;
}