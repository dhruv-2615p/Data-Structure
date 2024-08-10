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

Tree insertToBSTRecusion(Tree tree, int key, Tree parent){
    if(!tree) return newTree(parent, key, NULL, NULL);

    if(tree->key < key) tree->right = insertToBSTRecusion(tree->right, key, tree);
    else tree->left = insertToBSTRecusion(tree->left, key, tree);

    return tree;
}

Tree findNodeInTree(Tree tree, int key){
    if(!tree)   
        return NULL;

    if(key == tree->key)    
        return tree;

    Tree left = findNodeInTree(tree->left, key);
    if(left)    
        return left;

    return findNodeInTree(tree->right, key);
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

int height(Tree tree){
    if(!tree)
        return 0;
    
    int hRight = height(tree->right);
    int hLeft = height(tree->left);

    return 1 + (hRight > hLeft ? hRight : hLeft);
}

int depth(Tree tree){
    if(!tree)
        return 0;
    else{
        int dLeft = depth(tree->left);
        int dRight = depth(tree->right);

        return (dLeft > dRight) ? (dLeft + 1): (dRight + 1);    
    }
}

Tree clone(Tree tree){
    if(!tree)
        return NULL;

    Tree left = clone(tree->left);
    Tree right = clone(tree->right);

    Tree new = newTree(NULL, tree->key, left, right);
    
    if(left)
        new->left->parent = new;

    if(right)
        new->right->parent = new;

    return new;
}

Tree mirror(Tree tree){
    if(!tree)
        return NULL;
    
    Tree left = mirror(tree->left);
    Tree right = mirror(tree->right);

    Tree mirror = newTree(NULL, tree->key, right, left);

    if(left)
        mirror->right->parent = mirror;

    if(right)
        mirror->left->parent = mirror;

    return mirror;
}

int compare(Tree tree1, Tree tree2){
    if(!tree1 && !tree2)
        return 1;
    
    if(!tree1 || !tree2)
        return 0;

    if(!(tree1->key == tree2->key))
        return 0;

    int left = compare(tree1->left, tree2->left);
    int right = compare(tree1->right, tree2->right);

    return left && right;
}

void deleteTree(Tree tree){
    if(!tree)
        return ;

    deleteTree(tree->left);
    deleteTree(tree->right);
    free(tree);
}

Tree inOrderSuccesor(Tree tree){
    if(!tree)
        return NULL;
    
    Tree succesor = findMinimumInBST(tree->right);
    
    if(succesor){
        while(succesor != NULL && succesor->right == tree){
            tree = succesor;
            succesor = succesor->parent;
        }
        return succesor;
    }

    if(!succesor){
        succesor = tree;
        while(succesor != NULL && succesor->left != tree){
            tree = succesor;
            succesor = succesor->parent;
        }
        return succesor;
    }
}

Tree inOrderPredecessor(Tree tree){
    if(!tree)
        return NULL; 

    Tree predecessor = findMaximumInBST(tree->left);

    if(predecessor){
        while(predecessor != NULL && predecessor->left == tree){
            tree = predecessor;
            predecessor = predecessor->parent;
        }

        return predecessor;
    }
    
    if(!predecessor){
        predecessor = tree;
        while(predecessor != NULL && predecessor->right != tree){
            tree = predecessor;
            predecessor = predecessor->parent;
        }
        return predecessor;
    }
}

int countNoedsInTree(Tree tree){
    if(!tree)
        return 0;

    return 1 + countNoedsInTree(tree->left) + countNoedsInTree(tree->right);
}

int countLeafNodes(Tree tree){
    if(!tree)
        return 0;
    
    if((!tree->left && !tree->right))
        return 1;

    return countLeafNodes(tree->left) + countLeafNodes(tree->right);
}

int countInternalNodes(Tree tree){
    if(!tree || (!tree->left && !tree->right))
        return 0;
        
    return 1 + countInternalNodes(tree->left) + countInternalNodes(tree->right);
}

void printKeysLeafNodesInorder(Tree tree){
    if(!tree)
        return ;
    
    printKeysLeafNodesInorder(tree->left);
    if((!tree->left && !tree->right))
        printf("%d ", tree->key);
    
    printKeysLeafNodesInorder(tree->right);
}

void printKeysNonLeafInOrder(Tree tree){
    if(!tree)
        return ;
    
    printKeysNonLeafInOrder(tree->left);
    if((tree->left && tree->right) || tree->left || tree->right)
        printf("%d ", tree->key);
    
    printKeysNonLeafInOrder(tree->right);
}

int sumTree(Tree tree){
    if(!tree)   return 0;

    return sumTree(tree->left) + sumTree(tree->right);
}

int main(){
    Tree bTree = NULL;

    int n;
    printf("Enter number of keys for binary tree: ");
    scanf("%d", &n);

    int key;
    printf("Enter key for binary tree: \n");
    for(int i = 0; i < n; i++){
        scanf("%d", &key);
        bTree = insertToBSTRecusion(bTree, key, NULL);
    }

    print_tree(bTree);
    printf("Enter key value that you want to find in tree: ");
    scanf("%d", &key);

    Tree found = findNodeInTree(bTree, key);
    if(found)
        print_tree(found);

    int heightBtree = height(bTree);
    printf("Height of binary tree is: %d\n", heightBtree - 1);
    /*
    // int depthBtree = depth(bTree);
    // printf("Depth of binary tree is: %d\n", depthBtree - 1);

    // printf("Atfter cloning tree: \n");
    // Tree clone1 = clone(bTree);
    // print_tree(clone1);

    // printf("Atfter making mirror of tree: \n");
    // Tree mirror1 = mirror(bTree);
    // print_tree(mirror1);

    // int keyCompare = compare(clone1, bTree);
    // printf("Keys are same or not : %d\n", keyCompare);

    // printf("After deleting tree: \n");
    // deleteTree(clone1);
    // print_tree(clone1);
    */

    printf("Inorder succesor of root node is: \n");
    Tree SuccesorInOrder = inOrderSuccesor(found);
    print_tree(SuccesorInOrder);

    printf("Inorder predecessor of root node is:\n");
    Tree PredecessorInOrder = inOrderPredecessor(found);
    print_tree(PredecessorInOrder);

    int nodesTotal = countNoedsInTree(bTree);
    printf("Total numbers of noes in tree are: %d\n", nodesTotal);

    int noedsLeafs = countLeafNodes(bTree);
    printf("Total numbers of leaf nodes are: %d\n", noedsLeafs);

    printf("Total numbers of non leaf nodes are: %d\n", countInternalNodes(bTree));

    printf("Printing leaf nodes key in in-Order: \n");
    printKeysLeafNodesInorder(bTree);
    printf("\n");

    printf("Printing non leaf nodes key in in-Order: \n");
    printKeysNonLeafInOrder(bTree);
    printf("\n");

}