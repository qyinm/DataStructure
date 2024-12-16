#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H

typedef struct _btreenod {
    int data;
    struct _btreenod *left;
    struct _btreenod *right;
} BTreeNode;

BTreeNode *MakeBTreeNode(void);
int GetData(BTreeNode *bTreeNode);
void SetData(BTreeNode *bTreeNode, int data);

BTreeNode *GetLeftSubTree(BTreeNode *bTreeNode);
BTreeNode *GetRightSubTree(BTreeNode *bTreeNode);

void MakeLeftSubTree(BTreeNode *main, BTreeNode *sub);
void MakeRIghtSubTree(BTreeNode *main, BTreeNode *sub);

typedef void (*VisitedPtrData)(int data);

void InorderTraverse(BTreeNode *bTreeNode, VisitedPtrData action);
void PreorderTraverse(BTreeNode *bTreeNode, VisitedPtrData action);
void PostorderTraverse(BTreeNode *bTreeNode, VisitedPtrData action);

void DeleteTree(BTreeNode * bTreeNode);

#endif; //BINARYTREE_BINARYTREE_H
