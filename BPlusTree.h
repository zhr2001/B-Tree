//
// Created by NSUS on 2021/4/27.
//

#ifndef B__BPLUSTREE_H
#define B__BPLUSTREE_H
#include "BPlusNode.h"
#include "BPlusNode.cpp"
#include <limits.h>
enum event { DELETE, INSERT };

class BPlusTree {
public:
    BPlusTree();

    void insertVal(value_type &theVal);
    void deleteVal(int theNo);
    void lentFromBooks(int theNo);
    void giveBackBook(int theNo);
    void print();
    void initTree(value_type* warehouse, int len) ;
    void KeepUpToNormative(event e, bool flag = false);
    BPlusOuterNode* findTarget(key_type no);
    int hasTheValue(BPlusOuterNode *theTarget, key_type no, int &i);

private:
    int allBookNum;
    BPlusInnerNode *root;
    BPlusOuterNode *minNode;
    BPlusInnerNode *target;     // 操作节点指针
};


#endif //B__BPLUSTREE_H
