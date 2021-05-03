//
// Created by NSUS on 2021/4/27.
//

#include "BPlusTree.h"
#include <queue>
#include <iostream>
using namespace std;

Book init_book[70] = {
        {1, "a"},
        {2, "b"},
        {3, "c"},
        {4, "d"},
        {5, "e"},
        {6, "f"},
        {7, "g"},
        {8, "h"},
        {9, "i"},
        {10,"j"},
        {11,"k"},
        {12,"l"},
        {13,"m"},
        {14,"n"},
        {15,"o"},
        {16,"p"},
        {17,"q"},
        {18,"r"},
        {19,"s"},
        {20,"t"},
        {21,"u"},
        {22,"v"},
        {23,"w"},
        {24,"x"},
        {25,"y"},
        {26,"z"}
};

BPlusTree::BPlusTree() {
    initTree(init_book, 20);
}

void BPlusTree::initTree(value_type* warehouse, int len) {
    BPlusOuterNode *theLeftNode = new BPlusOuterNode();
    BPlusOuterNode *theRightNode = new BPlusOuterNode();
    for (int i = 0; i < MIN_CHILD; i++) {
        theLeftNode->setVal(i, warehouse[i]);
        theRightNode->setVal(i, warehouse[i+MIN_CHILD]);
    }
    theLeftNode->setValNum(MIN_CHILD);
    theRightNode->setValNum(MIN_CHILD);
    root = new BPlusInnerNode();
    root->setKeyNum(2);
    root->setKey(0, warehouse[0].BookNo);
    root->setKey(1, warehouse[MIN_CHILD].BookNo);
    root->setChild(0, theLeftNode);
    root->setChild(1, theRightNode);
    root->setChildType(OUTER);
    theRightNode->setParent(root); theLeftNode->setParent(root);
    theLeftNode->setBrother(theRightNode);
    for(int i = 2*MIN_CHILD; i < len; i++) insertVal(warehouse[i]);
    minNode = theLeftNode;
}

BPlusOuterNode* BPlusTree::findTarget(key_type no) {
    target = root;
    BPlusOuterNode* lastTarget;
    int i;
    while(1) {
        for(i = 0; i < target->getKeyNum() && target->getKeyValue(i) <= no; i++);
        if(target->getChildType() == INNER) target = target->getInnerChild(i-1);
        else {
            lastTarget = target->getOuterChild(i-1); break;
        }
    }
    return lastTarget;
}

int BPlusTree::hasTheValue(BPlusOuterNode *lastTarget, key_type no, int &i) {
    for(i = 0; i < lastTarget->getValueNum() && lastTarget->getValue(i).BookNo < no; i++);
    if(i < lastTarget->getValueNum() && lastTarget->getValue(i).BookNo == no) return true;
    return false;
}

BPlusOuterNode * BPlusTree::preNode(BPlusOuterNode* node) {
    if(node->getParent()->getKeyIndex(node->getValue(0).BookNo) != 0)
        return node->getParent()->getOuterChild(node->getParent()->getKeyIndex(node->getValue(0).BookNo)-1);
    return findTarget(node->getValue(0).BookNo-1);
}

void BPlusTree::insertVal(value_type &theVal) {
    target = root;
    BPlusOuterNode* lastTarget = findTarget(theVal.BookNo);
    int i;
    if(hasTheValue(lastTarget, theVal.BookNo, i)) {
        cout << "The input No " << theVal.BookNo << " has been in the System !" << endl << endl;
        return;
    }
    for(int j = lastTarget->getValueNum(); j > i; j--)
        lastTarget->setVal(j, lastTarget->getValue(j-1));
    lastTarget->setVal(i, theVal);
    lastTarget->setValNum(lastTarget->getValueNum()+1);
    if(i == 0) {
        while(target != nullptr) {
            target->setKey(0, theVal.BookNo);
            target = target->getParent();
        }
        target = lastTarget->getParent();
    }
    if(lastTarget->getValueNum() > MAX_CHILD) {
        lastTarget->split();
        KeepUpToNormative(INSERT);
    }
    else return ;
}

void BPlusTree::lentFromBooks(int theNo) {
    int i;
    BPlusOuterNode *lastTarget = findTarget(theNo);
    if(!hasTheValue(lastTarget, theNo, i)) {
        cout << "Wrong number!" << endl;
        return ;
    }
    lastTarget->getValue(i).setStock(lastTarget->getValue(i).now_stock-1);
}

void BPlusTree::giveBackBook(int theNo) {
    int i;
    BPlusOuterNode *lastTarget = findTarget(theNo);
    if(!hasTheValue(lastTarget, theNo, i)) {
        cout << "Wrong number!" << endl;
        return ;
    }
    lastTarget->getValue(i).setStock(lastTarget->getValue(i).now_stock+1);
}

void BPlusTree::EditTheMinValue(int pre) {
    while(target != root){
        int theIndex = target->getParent()->getKeyIndex(pre);
        BPlusInnerNode *temp = target->getParent();
        if(theIndex != -1) temp->setKey(theIndex, target->getKeyValue(0));
        target = temp;
        if(theIndex == 0) {
            EditTheMinValue(pre);
            return ;
        }
        else return ;
    }
    if(root->getKeyIndex(pre) == 0 && root->getChildType() == INNER)
        root->setKey(0, root->getInnerChild(0)->getKeyValue(0));
    else if(root->getKeyIndex(pre) == 0 && root->getChildType() == OUTER) root->setKey(0, root->getOuterChild(0)->getValue(0).BookNo);
    return ;
}

void BPlusTree::deleteVal(int theNo) {
    target = root;
    int i, j;
    BPlusOuterNode *lastTarget = findTarget(theNo);
    if(hasTheValue(lastTarget, theNo, i)) {
        cout << "Delete success" << endl;
        BPlusInnerNode *temp = target;
        if(i == 0) {
            int preValue = target->getKeyValue(target->getKeyIndex(lastTarget->getValue(0).BookNo));
            lastTarget->getParent()->setKey(lastTarget->getParent()->getKeyIndex(lastTarget->getValue(0).BookNo),
                                            lastTarget->getValue(1).BookNo);
            target = lastTarget->getParent();
            EditTheMinValue(preValue);
            target = lastTarget->getParent();
        }
        for(j = i; j < lastTarget->getValueNum()-1; j++)
            lastTarget->setVal(j, lastTarget->getValue(j+1));
        lastTarget->setValNum(lastTarget->getValueNum()-1);
        if(lastTarget->getValueNum() < MIN_CHILD) {
            if(lastTarget->getBrother() != nullptr &&
               lastTarget->getParent()->getKeyIndex(lastTarget->getBrother()->getValue(0).BookNo) != -1 &&
               lastTarget->getBrother()->getValueNum() > MIN_CHILD){
               lastTarget->borrowFrom(lastTarget->getBrother());
                return ;
            }
            if(lastTarget->getParent()->getKeyIndex(lastTarget->getValue(0).BookNo) != 0 &&
                lastTarget->getParent()->getOuterChild(
                lastTarget->getParent()->getKeyIndex(lastTarget->getValue(0).BookNo)-1)->getValueNum() > MIN_CHILD) {
                lastTarget->borrowFrom(lastTarget->getParent()->getOuterChild(lastTarget->getParent()->getKeyIndex(lastTarget->getValue(0).BookNo)-1));
                return ;
            }
            if(lastTarget->getBrother() != nullptr &&
               lastTarget->getParent()->getKeyIndex(lastTarget->getBrother()->getValue(0).BookNo) != -1)
                lastTarget->merge(lastTarget->getBrother(), preNode(lastTarget));
            else
                preNode(lastTarget)->merge(lastTarget, preNode(preNode(lastTarget)));
            target = temp;
            KeepUpToNormative(DELETE);
            return ;
        }
        else return ;
    }
    cout << "Wrong number!" << endl;
    return ;
}

void BPlusTree::search(int theNo) {
    BPlusOuterNode* lastTarget = findTarget(theNo);
    int i = 0;
    if(hasTheValue(lastTarget, theNo, i)) cout << "The BookNo exists." << endl;
    else cout << "Not exists" << endl;
}

void BPlusTree::KeepUpToNormative(event e) {
    BPlusInnerNode *temp = target->getParent();
    if (e == DELETE) {
        while(target != root) {
            if (target->getKeyNum() >= MIN_CHILD) return ;
            else if(target->getParent()->getKeyIndex(target->getKeyValue(0)) != 0 &&
                    target->getParent()->getInnerChild(
                            target->getParent()->getKeyIndex(target->getKeyValue(0))-1)->getKeyNum() > MIN_CHILD) {
                target->borrowFrom(target->getParent()->getInnerChild(target->getParent()->getKeyIndex(target->getKeyValue(0))-1))  ;
                return ;
            }
            else if(target->getParent()->getKeyIndex(target->getKeyValue(0)) != target->getParent()->getKeyNum()-1  &&
                     target->getParent()->getInnerChild(target->getParent()->getKeyIndex(target->getKeyValue(0))+1)->getKeyNum() > MIN_CHILD){
                target->borrowFrom(target->getParent()->getInnerChild(target->getParent()->getKeyIndex(target->getKeyValue(0))+1));
                return ;
            }
            else {
                if(target->getParent()->getKeyIndex(target->getKeyValue(0)) != 0)
                    target->getParent()->getInnerChild(target->getParent()->getKeyIndex(target->getKeyValue(0))-1)->merge(target);
                else target->merge(target->getParent()->getInnerChild(target->getParent()->getKeyIndex(target->getKeyValue(0))+1));
            }
            target = temp;
            KeepUpToNormative(DELETE);
            return;
        }
        if(target->getKeyNum() > 1) return ;
        else root = root->getInnerChild(0);
        root->setParent(nullptr);
        delete target;
        return ;
    }

    else {
        while(target != root) {
            if (target->getKeyNum() <= MAX_CHILD) return ;
            target->split();
            target = target->getParent();
            KeepUpToNormative(INSERT);
        }
        if (target->getKeyNum() <= MAX_CHILD) return ;
        BPlusInnerNode *newRoot = new BPlusInnerNode();
        newRoot->setChild(0, root);
        newRoot->setKey(0, root->getKeyValue(0));
        newRoot->setKey(1, root->getKeyValue(MIN_CHILD));
        newRoot->setChildType(INNER);
        root->setParent(newRoot);
        newRoot->setKeyNum(2);
        root = newRoot;
        int i;
        BPlusInnerNode *newNode = new BPlusInnerNode();
        for(i = MIN_CHILD; i <= MAX_CHILD; i++) {
            newNode->setKey(i-MIN_CHILD, target->getKeyValue(i));
            if (target->getChildType() == INNER) {
                newNode->setChild(i-MIN_CHILD, target->getInnerChild(i));
                target->getInnerChild(i)->setParent(newNode);
            }
            else {
                newNode->setChild(i-MIN_CHILD, target->getOuterChild(i));
                target->getOuterChild(i)->setParent(newNode);
            }
        }
        newNode->setParent(target->getParent());
        root->setChild(1, newNode);
        newNode->setKeyNum(target->getKeyNum()-MIN_CHILD);
        newNode->setChildType(target->getChildType());
        target->setKeyNum(MIN_CHILD);
        return ;
    }
}

void BPlusTree::print() {
    queue<BPlusInnerNode*> que;
    queue<BPlusOuterNode*> outQ;
    BPlusOuterNode* theTarget;
    que.push(root);
    int theLast = root->getKeyValue(root->getKeyNum()-1);
    cout << "The Inner structure: " << endl;
    while(que.size() > 0) {
        target = que.front();
        que.pop();
        for(int i = 0; i <= target->getKeyNum(); i++) {
            if(i != target->getKeyNum()) cout << target->getKeyValue(i) << " ";
            else {
                if(target == root) cout << endl;
                else if(target->getKeyValue(0) == theLast) {
                    cout << endl;
                    theLast = target->getKeyValue(target->getKeyNum()-1);
                } else cout << "    ";
                break;
            }
            if(target->getChildType() == INNER) que.push(target->getInnerChild(i));
            else outQ.push(target->getOuterChild(i));
        }
    }
    cout << endl << "The all value: " << endl;
    while(outQ.size() > 0) {
        theTarget = outQ.front();
        outQ.pop();
        for(int i = 0; i < theTarget->getValueNum(); i++) cout << theTarget->getValue(i) << endl;
        cout << endl;
    }
}

