//
// Created by NSUS on 2021/4/27.
//

#include "BPlusNode.h"

int BPlusInnerNode::getKeyIndex(key_type theKey) const {
    for(int i = 0; i < key_num; i++)
        if(key[i] == theKey) return i;

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

void BPlusInnerNode::merge(BPlusInnerNode* brother) {
    BPlusInnerNode *mergeTarget = new BPlusInnerNode();
    int i = 0, theIndex;
    for(; i < getKeyNum(); i++) {
        mergeTarget->setKey(i, getKeyValue(i));
        if(getChildType() == INNER) {
            mergeTarget->setChild(i, getInnerChild(i));
            getInnerChild(i)->setParent(mergeTarget);
        }
        else {
            mergeTarget->setChild(i, getOuterChild(i));
            getOuterChild(i)->setParent(mergeTarget);
        }
    }
    for(; i < getKeyNum() + brother->getKeyNum(); i++) {
        mergeTarget->setKey(i, brother->getKeyValue(i - getKeyNum()));
        if (getChildType() == INNER) {
            mergeTarget->setChild(i, brother->getInnerChild(i - getKeyNum()));
            brother->getInnerChild(i - getKeyNum())->setParent(mergeTarget);
        }
        else {
            mergeTarget->setChild(i, brother->getOuterChild(i - getKeyNum()));
            brother->getOuterChild(i - getKeyNum())->setParent(mergeTarget);
        }
    }

    mergeTarget->setChildType(getChildType());
    mergeTarget->setParent(getParent());
    mergeTarget->setKeyNum(getKeyNum()+brother->getKeyNum());

    theIndex = parent->getKeyIndex(getKeyValue(0));

    parent->setChild(theIndex, mergeTarget);
    for(i = theIndex+1; i < parent->getKeyNum()-1; i++){
        parent->setKey(i, parent->getKeyValue(i+1));
        parent->setChild(i, parent->getInnerChild(i+1));
    }
    parent->setKeyNum(parent->getKeyNum()-1);
    delete brother;
    delete this;
};

void BPlusInnerNode::borrowFrom(BPlusInnerNode *brother) {
    setKey(getKeyNum(), brother->getKeyValue(0));
    if(getChildType() == INNER) {
        setChild(getKeyNum(), brother->getInnerChild(0));
        brother->getInnerChild(0)->setParent(this);
    }
    else {
        setChild(getKeyNum(), brother->getOuterChild(0));
        brother->getOuterChild(0)->setParent(this);
    }
    setKeyNum(getKeyNum()+1);
    int theIndex= getParent()->getKeyIndex(getKeyValue(getKeyNum()-1));
    getParent()->setKey(theIndex, brother->getKeyValue(1));
    for(int i = 0; i < brother->getKeyNum()-1 ;i++){
        brother->setKey(i, brother->getKeyValue(i+1));
        if(getChildType() == INNER) brother->setChild(i, brother->getInnerChild(i+1));
        else brother->setChild(i, brother->getOuterChild(i+1));
    }
    brother->setKeyNum(brother->getKeyNum()-1);
    return ;
};

void BPlusOuterNode::merge(BPlusOuterNode *brother) {
    BPlusOuterNode *mergeTarget = new BPlusOuterNode();
    int i, theIndex;
    for(i = 0; i < getValueNum(); i++)
        mergeTarget->setVal(i, getValue(i));
    for(; i < getValueNum() + brother->getValueNum(); i++)
        mergeTarget->setVal(i, brother->getValue(i - getValueNum()));
    mergeTarget->setValNum(getValueNum() + brother->getValueNum());
    theIndex = parent->getKeyIndex(mergeTarget->getValue(0).BookNo);
    parent->setChild(theIndex, mergeTarget);
    for(theIndex = theIndex+1; theIndex < parent->getKeyNum()-1; theIndex++){
        parent->setKey(theIndex, parent->getKeyValue(theIndex+1));
        parent->setChild(theIndex, parent->getOuterChild(theIndex+1));
    }
    parent->setKeyNum(parent->getKeyNum()-1);
    mergeTarget->setParent(getParent());
    mergeTarget->setBrother(brother->getBrother());
    delete brother;
    delete this;
};

void BPlusOuterNode::borrowFrom(BPlusOuterNode *brother) {
    setVal(getValueNum(), brother->getValue(0));
    setValNum(getValueNum()+1);
    int theIndex= getParent()->getKeyIndex(getValue(getValueNum()-1).BookNo);
    getParent()->setKey(theIndex, brother->getValue(1).BookNo);
    for(int i = 0; i < brother->getValueNum()-1 ;i++)
        brother->setVal(i, brother->getValue(i+1));
    brother->setValNum(getValueNum()-1);
    return ;
};
