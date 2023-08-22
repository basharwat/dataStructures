#ifndef DATASTRUCTURESHW1_BTREE_H
#define DATASTRUCTURESHW1_BTREE_H

#include "TreeNode.h"

template<class T>
class BTree {
public:
    TreeNode<T> *head;
//public:        
    BTree() : head(NULL){}
    ~BTree() {
        treeNodesDestroy(head);
    }
    
    bool insert(const int& key, T& value){
        if(!head){
            head = new TreeNode<T>(key,value);
            return true;
        }
        TreeNode<T>* temp;
        temp=this->head;
        while(temp) {
            if(key==temp->GetKey()) {
                return false;
            }
            if(key<temp->GetKey()) {
                if(!temp->GetLeft()) {
                    break;
                }
                else {
                    temp=temp->GetLeft();
                }
            }
            if(key>temp->GetKey()) {
                if(!temp->GetRight()) {
                    break;
                }
                else {
                    temp=temp->GetRight();
                }
            }
        }
        TreeNode<T>* newNode = new TreeNode<T>(key,value);
        newNode->SetUp(temp);
        if(key<temp->GetKey()) {
            temp->SetLeft(newNode);
        }
        else {
            temp->SetRight(newNode);
        }
        head=newNode->balance(head);
        return true;    
    }
    
    void Remove(int id) {
        TreeNode<T>* temp=head->findNode(id);
        if(!temp) {
            return;
        }
        TreeNode<T>* toDelete=temp;
        if(!(temp->GetLeft()) && !(temp->GetRight()))
        {
            if(temp == this->head) {
                //delete this->head;
                this->head = NULL;
            }    
            else
            {
                if(temp->GetUp()->GetLeft() == temp) {
                    temp->GetUp()->SetLeft(NULL) ;
                    if(temp->GetUp()->GetRight()) {
                        temp->GetUp()->GetRight()->balanceRemove(head);
                    }
                    else {
                        temp->GetUp()->balanceRemove(head);
                    }
                }    
                else {
                    temp->GetUp()->SetRight(NULL) ;
                    if(temp->GetUp()->GetLeft()) {
                        temp->GetUp()->GetLeft()->balanceRemove(head);
                    }
                    else {
                        temp->GetUp()->balanceRemove(head);
                    }
                }    
            }
            return;
        }
        
        if(temp->GetRight() && !(temp->GetLeft()))
        {
            if(temp == this->head)
            {
                this->head = this->head->GetRight();
                this->head->SetUp(NULL);
            }
            else
            {
                if(temp->GetUp()->GetRight() == temp)
                {
                    temp->GetUp()->SetRight(temp->GetRight()) ;
                    if(temp->GetRight()) {
                        temp->GetRight()->SetUp(temp->GetUp());
                    }
                    temp->GetUp()->balanceRemove(head);
                }
                else
                {
                    temp->GetUp()->SetLeft(temp->GetRight()) ;
                    if(temp->GetRight()) {
                        temp->GetRight()->SetUp(temp->GetUp());
                    }
                    temp->GetUp()->balanceRemove(head);
                }
            }
            return ;
        }
        
        if(temp->GetLeft() && !(temp->GetRight()))
        {
            if(temp == this->head)
            {
                this->head = this->head->GetLeft();
                this->head->SetUp(NULL);
            }
            else
            {
                /*if(temp->GetUp()->GetLeft() == temp)
                {
                    temp->GetUp()->SetLeft(temp->GetLeft()) ;
                    if(temp->GetLeft()) {
                        temp->GetLeft()->SetUp(temp->GetUp());
                    }
                    temp->GetUp()->balanceRemove(head);
                }
                else
                {
                    temp->GetUp()->SetRight(temp->GetLeft()) ;
                    if(temp->GetLeft()) {
                        temp->GetLeft()->SetUp(temp->GetUp());
                    }
                    temp->GetUp()->balanceRemove(head);
                }*/
                if(temp->GetUp()->GetRight() == temp)
                {
                    temp->GetUp()->SetRight(temp->GetLeft()) ;
                    if(temp->GetLeft()) {
                        temp->GetLeft()->SetUp(temp->GetUp());
                    }
                    temp->GetUp()->balanceRemove(head);
                }
                else
                {
                    temp->GetUp()->SetLeft(temp->GetLeft()) ;
                    if(temp->GetLeft()) {
                        temp->GetLeft()->SetUp(temp->GetUp());
                    }
                    temp->GetUp()->balanceRemove(head);
                }
            }
            return ;
        }
        
        TreeNode<T>* replace = temp->GetRight();
        while (replace->GetLeft()!= NULL) {
            replace=replace->GetLeft();
        }
        temp->SetValue(replace->GetValue());
        temp->SetKey(replace->GetKey());
        TreeNode<T>* toBalance=replace->GetUp();
        toDelete=replace;
        if(replace->GetUp()->GetLeft() == replace) {
            replace->GetUp()->SetLeft(replace->GetRight());
        }
        else {
            replace->GetUp()->SetRight(replace->GetRight());
        }
        if(replace->GetRight()) {
            replace->GetRight()->SetUp(replace->GetUp());
            toBalance=replace->GetRight();
        }
        else if(replace->GetUp()->GetRight()) {
            toBalance=replace->GetUp()->GetRight();
        }
        else {
            toBalance=replace->GetUp();
        }
        if(toBalance) {
            head=toBalance->balanceRemove(head);
        }
        delete toDelete;
        return;
    }

};

#endif //DATASTRUCTURESHW1_BTREE_H