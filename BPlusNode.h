//
// Created by NSUS on 2021/4/27.
//

#ifndef B__BPLUSNODE_H
#define B__BPLUSNODE_H
#include <iostream>
using namespace std;

#define M 3
#define MAX_CHILD M
#define MIN_CHILD (M+1)/2

typedef int key_type;
typedef struct Book {
    int BookNo;
    string name;
    int all_stock;
    int now_stock;

    Book() {};

    Book(int aNo, string aName) {
        BookNo = aNo;
        name = aName;
    }

    void setStock(int num) {
        all_stock = num;
        now_stock = num;
    }

    void lent() { now_stock-- ; }
} value_type;

ostream & operator << (ostream &out, value_type &b) {
    out << "The Book No. = " << b.BookNo << endl;
    out << "The Book Name = " << b.name << endl;
    out << "The Book All Stock = " << b.all_stock << endl;
    out << "The Book Now Stock = " << b.now_stock << endl;
    return out;
}

enum NodeType {INNER, OUTER};

class BPlusOuterNode ;

class BPlusInnerNode {
public:
    BPlusInnerNode();
    ~BPlusInnerNode();

    int getKeyNum() const { return key_num; }
    int getKeyValue(int theIndex) { return key[theIndex]; }
    int getKeyIndex(key_type theKey) const;
    BPlusInnerNode* getParent() const { return parent; }
    void setKey(int theIndex, key_type newKey);
    void setKeyNum(int theNum);
    void setChild(int theIndex, BPlusInnerNode* theNext);
    void setChild(int theIndex, BPlusOuterNode* theNext);
    void setParent(BPlusInnerNode *theParent);
    NodeType getType() const { return type; }
    NodeType getChildType() const { return childType; }
    void setChildType(NodeType tt) { childType = tt; }
    BPlusInnerNode* getInnerChild(int theIndex) { return innerChild[theIndex]; }
    BPlusOuterNode* getOuterChild(int theIndex) { return leafChild[theIndex]; }

    void split();
    void borrowFrom(BPlusInnerNode *brother);
    void merge();
    void insert(int theIndex, BPlusInnerNode *theNode);
    void insert(int theIndex, BPlusOuterNode *theNode);

private:
    NodeType type;
    NodeType childType;
    int key_num;
    BPlusInnerNode *parent;
    key_type key[MAX_CHILD+1];
    BPlusInnerNode *innerChild[MAX_CHILD+1];
    BPlusOuterNode *leafChild[MAX_CHILD+1];
};

class BPlusOuterNode {
public:
    BPlusOuterNode();
    ~BPlusOuterNode();

    int getValueNum() const { return val_num; }
    value_type& getValue(int theIndex) { return val[theIndex]; }
    int getLeafIndex(int book) const;
    BPlusInnerNode* getParent() const { return parent; }
    void setVal(int leafIndex, value_type &bVal);
    void setValNum(int theNum);
    void setParent(BPlusInnerNode *theParent);
    void setBrother(BPlusOuterNode *theBrother);
    BPlusOuterNode* getBrother() { return brother ;}
    NodeType getType() const { return type; }

    void split();
    void borrowFrom(BPlusOuterNode *brother);
    void merge(BPlusOuterNode *brother);

private:
    NodeType type;
    int val_num;
    BPlusInnerNode* parent;
    BPlusOuterNode* brother;
    value_type val[MAX_CHILD+1];
};

#endif //B__BPLUSNODE_H
