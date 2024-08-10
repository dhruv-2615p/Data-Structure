#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "drawing.c"

// typedef struct Tree_t* Tree;

// struct Tree_t{
//     Tree parent;
//     int key;
//     Tree left, right;
// };
 
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

Tree insertToBSTIterative(Tree tree, int key){
    if(!tree) return newTree(tree, key, NULL, NULL);
    Tree root = NULL;
    Tree p = tree;
    while(p){
        root = p;
        if(key < p->key)
            p = p->left;
        else
            p = p->right;
    }

    if(key < root->key){
        root->left = newTree(root, key, NULL, NULL);
    }
    else{
        root->right = newTree(root, key, NULL, NULL);
    }

    return tree;
}

Tree findMinimumInBST(Tree tree){
    if(!tree) return NULL;

    for(; tree->left; tree = tree->left)
        ;
    return tree;
}

Tree findMaximumInBST(Tree tree){
    if(!tree) return NULL;

    for(; tree->right; tree = tree->right)
        ;
    return tree;
}

Tree findKeyInBST(Tree tree, int key){
    if(!tree) return NULL;

    if(key == tree->key)
        return tree;
    
    if(key < tree->key){
        Tree left = findKeyInBST(tree->left, key);
    }
    
    if(key > tree->key){
        Tree right = findKeyInBST(tree->right, key);
    }
}

Tree deletKey(Tree tree, int key){
    if(!tree) return NULL;

    if(key < tree->key){
        tree->left = deletKey(tree->left, key);
        return tree;
    }

    if(key > tree->key){
        tree->right = deletKey(tree->right, key);
        return tree;
    }

    if(!tree->left && !tree->right){
        free(tree);
        return NULL;
    }

    if(!tree->right){
        Tree left = tree->left;
        left->parent = tree->parent;
        free(tree);
        return left;
    }
    
    if(!tree->left){
        Tree right = tree->right;
        right->parent = tree->parent;
        free(tree);
        return right;
    }

    Tree successor = findMinimumInBST(tree->right);
    tree->key = successor->key;
    tree->right = deletKey(tree->right, successor->key);

    return tree;
}

void preOrderRecursion(Tree tree){
    if(!tree) return ;
    printf("%4d", tree->key);
    preOrderRecursion(tree->left);
    preOrderRecursion(tree->right);
}

void inOrderRecursion(Tree tree){
    if(!tree) return ;
    inOrderRecursion(tree->left);
    printf("%4d ", tree->key);
    inOrderRecursion(tree->right);
}

void postOrderRecursion(Tree tree){
    if(!tree) return ;
    postOrderRecursion(tree->left);
    postOrderRecursion(tree->right);
    printf("%4d ", tree->key);
}

void printTree(Tree tree){
    printf("Preorder printing: ");
    preOrderRecursion(tree);
    printf("\n");
    printf("Postorder printing: ");
    postOrderRecursion(tree);
    printf("\n");
    printf("Inorder printing: ");
    inOrderRecursion(tree);
    printf("\n");
}

int height(Tree tree){
    if(!tree) return 0;

    int heightLeft = height(tree->left);
    int heightRight = height(tree->right);

    int height1 = fmax(heightLeft, heightRight);
    return height1;
}

int findMinKey(Tree tree){
    if(!tree) return 0;

    if(!tree->left && !tree->right){
        return tree->key;
    }

    if(!tree->left){
        return tree->key < findMinKey(tree->right) ? tree->key : findMinKey(tree->right);
    }

    if(!tree->right){
        return tree->key < findMinKey(tree->left) ? tree->key : findMinKey(tree->left);
    }

    int minLeftRight = findMinKey(tree->left) < findMinKey(tree->right) ? findMinKey(tree->left) : findMinKey(tree->right);
    if(tree->key < minLeftRight) return tree->key;

    return minLeftRight;
}

int findMaxKey(Tree tree){
    if(!tree) return 0;

    if(!tree->left && !tree->right){
        return tree->key;
    }

    if(!tree->left){
        return tree->key < findMaxKey(tree->right) ? findMaxKey(tree->right) : tree->key;
    }

    if(!tree->right){
        return tree->key < findMaxKey(tree->left) ? findMaxKey(tree->left) : tree->key;
    }

    int maxLeftRight = findMaxKey(tree->left) > findMaxKey(tree->right) ? findMaxKey(tree->left) : findMaxKey(tree->right);
    if(tree->key < maxLeftRight) return maxLeftRight;

    return tree->key;
}

int sumTree(Tree tree){
    if(!tree)
        return 0;
    
    return tree->key + (sumTree(tree->left) + sumTree(tree->right));
}

int isBST(Tree tree){
    if(!tree) return 1;

    if(tree->left){
        if(tree->key < findMaxKey(tree->left))  return 0;
    }

    if(tree->right){
        if(tree->key > findMinKey(tree->right)) return 0;
    }

    return isBST(tree->left) && isBST(tree->right);
}

int main(){

    Tree tree = NULL;

    int choise;
    int key;

    do{
        printf("\n\nMenu:\n");
        printf("1. Insert to BST Recusively.\n");
        printf("2. Insert to BST Iterative.\n");
        printf("3. Find minimum key in BST.\n");
        printf("4. Find maximum key in BST.\n");
        printf("5. Find key to BST.\n");
        printf("6. Delet key in BST.\n");
        printf("7. Print tree in In-Order.\n");
        printf("8. Print tree in Pre-Order.\n");
        printf("9. Print tree in Post-Order.\n");
        printf("10. Find minimum key value in tree.\n");
        printf("11. Find maximum key value in tree.\n");
        printf("12. Find is tree is BST or not.\n");
        printf("13. Printing of tree.\n");
        printf("14. Sum.\n");
        printf("15. Exit.\n");
        printf("Enter your choise: ");
        scanf("%d", &choise);

        switch(choise){
            case 1:
                printf("Enter key value: ");
                scanf("%d", &key);
                tree = insertToBSTRecusion(tree, key, NULL);
                break;

            case 2:
                printf("Enter key value: ");
                scanf("%d", &key);
                tree = insertToBSTIterative(tree, key);
                break;
            
            case 3:
                print_tree(findMinimumInBST(tree));
                break;

            case 4:
                print_tree(findMaximumInBST(tree));
                break;
            
            case 5:
                printf("Enter key value: ");
                scanf("%d", &key);
                print_tree(findKeyInBST(tree, key));
                break;

            case 6:
                printf("Enter key value: ");
                scanf("%d", &key);
                print_tree(deletKey(tree, key));
                break;
            
            case 7:
                inOrderRecursion(tree);
                break;

            case 8:
                preOrderRecursion(tree);
                break;
            
            case 9:
                postOrderRecursion(tree);
                break;
            
            case 10:
                printf("Minimum key in tree is %d",findMinKey(tree));
                break;

            case 11:
                printf("Maximum key in tree is %d",findMaxKey(tree));
                break;

            case 12:
                printf("Tree is (%d) BST.", isBST(tree));
                break;
            case 13:
                print_tree(tree);
                break;
            case 14:
                printf("Sum is: %5d\n", sumTree(tree));
                break;
        }
    }
    while(choise < 15);


    int x;
    printf("\nEnter key : ");
    scanf("%d", &x);

    printf("Key found: %d\n", findKeyInBST(tree, x)->key);

    printf("\n\nSum is: %d\n", sumTree(findKeyInBST(tree, x)));

    return 0;
}