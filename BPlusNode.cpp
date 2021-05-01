//
// Created by NSUS on 2021/4/27.
//

#include "BPlusNode.h"

int BPlusInnerNode::getKeyIndex(key_type theKey) const {
    for(int i = 0; i < key_num; i++)
        if(key[i] == theKey) return i;

    return -1;
}

int BPlusOuterNode::getLeafIndex(int book) const {
    for(int i = 0; i < val_num; i++)
        if(val[i].BookNo == book) return i;

    return -1;
}

void BPlusInnerNode::setKeyNum(int theNum) {
    key_num = theNum;
}

void BPlusOuterNode::setValNum(int theNum) {
    val_num = theNum;
}

void BPlusInnerNode::setKey(int theIndex, key_type newKey) {
    key[theIndex] = newKey;
}

void BPlusOuterNode::setVal(int leafIndex, value_type &bVal) {
    val[leafIndex] = bVal;
}

BPlusInnerNode::BPlusInnerNode() {
    setKeyNum(0);
    type = INNER;
    parent = nullptr;
}

BPlusOuterNode::BPlusOuterNode() {
    setValNum(0);
    brother = nullptr;
    parent = nullptr;
    type = OUTER;
}

BPlusInnerNode::~BPlusInnerNode() {

}

BPlusOuterNode::~BPlusOuterNode() {}

void BPlusInnerNode::setChild(int theIndex, BPlusInnerNode *theNext) {
    innerChild[theIndex] = theNext;
}

void BPlusInnerNode::setChild(int theIndex, BPlusOuterNode *theNext) {
    leafChild[theIndex] = theNext;
}

void BPlusInnerNode::setParent(BPlusInnerNode *theParent) {
    parent = theParent;
}

void BPlusOuterNode::setParent(BPlusInnerNode *theParent) {
    parent = theParent;
}

void BPlusOuterNode::setBrother(BPlusOuterNode *theBrother) {
    brother = theBrother;
}

void BPlusInnerNode::insert(int theIndex, BPlusInnerNode* theNode) {
    for(int j = getKeyNum(); j > theIndex; j--) {
        setKey(j, getKeyValue(j-1));
        setChild(j, getInnerChild(j-1));
    }
    setKey(theIndex, theNode->getKeyValue(0));
    setChild(theIndex, theNode);
    setKeyNum(getKeyNum()+1);
}

void BPlusInnerNode::insert(int theIndex, BPlusOuterNode* theNode) {
    for(int j = getKeyNum(); j > theIndex; j--) {
        setKey(j, getKeyValue(j-1));
        setChild(j, getOuterChild(j-1));
    }
    setKey(theIndex, theNode->getValue(0).BookNo);
    setChild(theIndex, theNode);
    setKeyNum(getKeyNum()+1);
}

void BPlusInnerNode::split() {
    int i;
    if (getKeyNum() < MAX_CHILD + 1) return ;
    BPlusInnerNode *newNode = new BPlusInnerNode();
    for(i = MIN_CHILD; i <= MAX_CHILD; i++) {
        newNode->setKey(i-MIN_CHILD, getKeyValue(i));
        if (getChildType() == INNER) {
            newNode->setChild(i-MIN_CHILD, getInnerChild(i));
            getInnerChild(i)->setParent(newNode);
        }
        else {
            newNode->setChild(i-MIN_CHILD, getOuterChild(i));
            getOuterChild(i)->setParent(newNode);
        }
    }
    newNode->setParent(getParent());
    getParent()->insert(getParent()->getKeyIndex(key[0])+1, newNode);
    newNode->setKeyNum(getKeyNum()-MIN_CHILD);
    newNode->setChildType(getChildType());
    setKeyNum(MIN_CHILD);
    return ;
}

void BPlusOuterNode::split() {
    int i;
    if (getValueNum() < MAX_CHILD + 1) return ;
    BPlusOuterNode *newNode = new BPlusOuterNode();
    for(i = MIN_CHILD; i <= MAX_CHILD; i++)
        newNode->setVal(i-MIN_CHILD, getValue(i));
    newNode->setParent(getParent());
    getParent()->insert(getParent()->getKeyIndex(val[0].BookNo)+1, newNode);
    newNode->setValNum(getValueNum()-MIN_CHILD);
    setValNum(MIN_CHILD);
    newNode->setBrother(getBrother());
    setBrother(newNode);
    return ;
}

void BPlusInnerNode::merge() {};

void BPlusInnerNode::borrowFrom(BPlusInnerNode *brother) {};

void BPlusOuterNode::borrowFrom(BPlusOuterNode *brother) {
};

void BPlusOuterNode::merge(BPlusOuterNode *brother) {};