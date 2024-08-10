#include <stdio.h>
#include <stdlib.h>
#include "drawing.c"

Tree newTree(Tree parent, int key, Tree left, Tree right){
    Tree tree = (Tree) calloc(1, sizeof(struct Tree_t));
    tree->parent = parent;
    tree->key = key;
    tree->left = left;
    tree->right = right;

    return tree;
}

int linearSearch(int inorder[], int inStart, int inEnd, int key){
    for(int i = inStart; i <= inEnd; i++){
        if(inorder[i] == key)
            return i;
    }
    return -1;
}

Tree helper(int inOrder[], int postOrder[], int inStart, int inEnd, int *pPostIndex){
    if(inStart > inEnd) return NULL;

    Tree tree = newTree(NULL, postOrder[*pPostIndex], NULL, NULL);
    (*pPostIndex)--;
    int index = linearSearch(inOrder,inStart, inEnd, tree->key);
    tree->right = helper(inOrder, postOrder,index + 1, inEnd, pPostIndex);
    tree->left = helper(inOrder, postOrder, inStart, index - 1, pPostIndex);

    if(tree->right)  tree->right->parent = tree;
    if(tree->left)   tree->left->parent = tree;

    return tree;
}

Tree makeTree(int n, int inOrder[], int postOrder[]){
    int inStart = 0;
    int inEnd = n - 1;
    int postIndex = n - 1;

    return helper(inOrder, postOrder, inStart, inEnd, &postIndex);
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

    int postOrder[n];
    printf("Enter elements for post order: \n");
    for(int i = 0; i < n; i++){
        scanf("%d", &postOrder[i]);
    }

    Tree binary = makeTree(n, inOrder,postOrder);
    print_tree(binary);

    return 0;
}