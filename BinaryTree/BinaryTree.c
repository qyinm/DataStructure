#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

BTreeNode *MakeBTreeNode(void) {
    BTreeNode *node = (BTreeNode *) malloc(sizeof(BTreeNode));
    node->right = NULL;
    node->left = NULL;
    return node;
}

int GetData(BTreeNode *bTreeNode) {
    return bTreeNode->data;
}

void SetData(BTreeNode *bTreeNode, int data) {
    bTreeNode->data = data;
}

BTreeNode *GetLeftSubTree(BTreeNode *bTreeNode) {
    return bTreeNode->left;
}

BTreeNode *GetRightSubTree(BTreeNode *bTreeNode) {
    return bTreeNode->right;
}

void MakeLeftSubTree(BTreeNode *main, BTreeNode *sub) {
    if (main->left != NULL) {
        free(main->left);
    }
    main->left = sub;
}

void MakeRightSubTree(BTreeNode *main, BTreeNode *sub) {
    if (main->right != NULL) {
        free(main->right);
    }
    main->right = sub;
}

/** 중위 순회 */
void InorderTraverse(BTreeNode *bTreeNode, VisitedPtrData action) {
    if (bTreeNode == NULL)  return;
    InorderTraverse(bTreeNode->left, action);
    action(bTreeNode->data);
    InorderTraverse(bTreeNode->right, action);
}
void PreorderTraverse(BTreeNode *bTreeNode, VisitedPtrData action) {
    if (bTreeNode == NULL)  return;
    action(bTreeNode->data);
    PreorderTraverse(bTreeNode->left, action);
    PreorderTraverse(bTreeNode->right, action);
}
void PostorderTraverse(BTreeNode *bTreeNode, VisitedPtrData action) {
    if (bTreeNode == NULL)  return;
    action(bTreeNode->data);
    PostorderTraverse(bTreeNode->right, action);
    PostorderTraverse(bTreeNode->left, action);
}

void DeleteTree(BTreeNode *bTreeNode) {
    if (bTreeNode == NULL)  return;
    DeleteTree(bTreeNode->left);
    free(bTreeNode->left);
    DeleteTree(bTreeNode->right);
    free(bTreeNode->right);
    bTreeNode->right = NULL;
    bTreeNode->left = NULL;
}

void ShowData(int data);

int main() {
    BTreeNode *bt1 = MakeBTreeNode();
    BTreeNode *bt2 = MakeBTreeNode();
    BTreeNode *bt3 = MakeBTreeNode();
    BTreeNode *bt4 = MakeBTreeNode();

    SetData(bt1, 1);
    SetData(bt2, 2);
    SetData(bt3, 3);
    SetData(bt4, 4);

    MakeLeftSubTree(bt1, bt2);
    MakeRightSubTree(bt1, bt3);
    MakeLeftSubTree(bt2, bt4);


    printf("left subtree of bt1 : %d \n", GetData(GetLeftSubTree(bt1)));
    printf("left subtree of left subtree of bt1 : %d \n", GetData(GetLeftSubTree(GetLeftSubTree(bt1))));

    printf("print Inorder!\n");
    InorderTraverse(bt1, ShowData);
    printf("-------------\n");
    printf("print Preorder!\n");
    PreorderTraverse(bt1, ShowData);
    printf("-------------\n");
    printf("print Postorder!\n");
    PostorderTraverse(bt1, ShowData);

    printf("-------------\n");
    printf("delete bt2!\n");
    DeleteTree(bt2);
    PreorderTraverse(bt1, ShowData);
    return 0;
}

void ShowData(int data) {
    printf("%d \n", data);
}