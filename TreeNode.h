#ifndef DATASTRUCTURESHW1_TREENODE_H
#define DATASTRUCTURESHW1_TREENODE_H

#include <iostream>

template <class T>
class TreeNode{
    int key;
    T value;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode* up;
public:
    //Constructor and destructors
    //The complexity equals to the complexity of the constructors and
    //destructors for the class members
    explicit TreeNode(const int& key, const T& value):key(key),value(value),
                      height(0),left(NULL),right(NULL),up(NULL){}
    ~TreeNode() = default;
    
    //Set and get functions in order to reach class members
    //complexity is O(1)
    void SetKey(const int & k) { 
        key = k; 
    }
    void SetValue(const T& t) { 
        value = t; 
    }
    void SetHeight(int newHeight){
        height = newHeight;
    }
    void SetRight(TreeNode* t){
        right = t;
    }
    void SetLeft(TreeNode* t){
        left = t;
    }
    void SetUp(TreeNode* t){
        up = t;
    }
    const int& GetKey(){
        return key;
    }
    T& GetValue(){
        return value;
    }
    int GetHeight(){
        return height;
    }
    TreeNode* GetRight(){
        return right;
    }
    TreeNode* GetLeft(){
        return left;
    }
    TreeNode* GetUp(){
        return up;
    }
    
    void LLFlip(){
        TreeNode<T>* father = this->up;
        TreeNode<T>* newHead = this->left;
        if(father) {
            if(this==father->right) {
                father->right=newHead;
            }
            else {
                father->left=newHead;
            }
        }
        newHead->up=father;
        this->left=newHead->right;
        if(newHead->right) {
            newHead->right->up=this;
        }
        newHead->right=this;
        this->up=newHead;
        if(this->left && balanceFactor()>=0) {
            this->height=1+this->left->height;
        }
        else if (this->right && balanceFactor()<0) {
            this->height=1+this->right->height;
        }
        else if (!this->right && !this->right) {
            this->height=0;
        }
        this->up->height=this->height+1;
    }
    void RRFlip(){
        TreeNode<T>* father = this->up;
        TreeNode<T>* newHead = this->right;
        if(father) {
            if(this==father->left) {
                father->left=newHead;
            }
            else {
                father->right=newHead;
            }
        }
        newHead->up=father;
        this->right=newHead->left;
        if(newHead->left) {
            newHead->left->up=this;
        }
        newHead->left=this;
        this->up=newHead;
        if(this->left && balanceFactor()>=0) {
            this->height=1+this->left->height;
        }
        else if (this->right && balanceFactor()<0) {
            this->height=1+this->right->height;
        }
        else if (!this->right && !this->right) {
            this->height=0;
        }
        this->up->height=this->height+1;
        
    }
    
    int balanceFactor(){
        int l,r;
        if (!this->left) {
            l=-1;
        }
        else {
            l=(this->left)->height;
        }
        if (!this->right) {
            r=-1;
        }
        else {
            r=(this->right)->height;
        }
        return l-r;
    }
    
    TreeNode<T>* fatherNode(const int &id) { 
        TreeNode<T>* temp=this;
        while(temp) {
            if(key==temp->key) {
                return NULL;
            }
            if(key<temp->key) {
                if(!temp->left) {
                    return temp;
                }
                else {
                    temp=temp->left;
                }
            }
            if(key>temp->key) {
                if(!temp->right) {
                    return temp;
                }
                else {
                    temp=temp->right;
                }
            }
        }
        return NULL;
    }
    TreeNode<T>* balance(TreeNode<T>* head) {
        TreeNode<T>* temp=this;
        TreeNode<T>* balanced=temp;
        while(temp->GetUp()) {
            TreeNode<T>* balanced=temp->GetUp();
            if(!(balanced->GetHeight()>temp->GetHeight())) {
                balanced->SetHeight(balanced->GetHeight()+1);
            }
            if(balanced->balanceFactor()==2){
                if(balanced->GetLeft()->balanceFactor()==-1){
                    balanced->GetLeft()->RRFlip();
                    balanced->LLFlip();
                } else {
                    balanced->LLFlip();
                }
                if(balanced==head){
                    head = head->GetUp();
                }
            }else if(balanced->balanceFactor()==-2){
                if(balanced->GetRight()->balanceFactor()==1){
                    balanced->GetRight()->LLFlip();
                    balanced->RRFlip();
                } else {
                    balanced->RRFlip();
                }
                if(balanced==head){
                    head = head->GetUp();
                }
            } else {
                temp = temp->GetUp();
            }
        }
        return head;
    }
    
    TreeNode<T>* findNode(int key) {
        TreeNode<T>* temp=this;
        while(temp) {
            if(key==temp->key) {
                return temp;
            }
            if(key<temp->GetKey()) {
                temp=temp->GetLeft();
            }
            if(key>temp->GetKey()) {
                temp=temp->GetRight();
            }
        }
        return NULL;
    }
    TreeNode<T>* balanceRemove(TreeNode<T>* head) {
        TreeNode<T>* temp=this;
        TreeNode<T>* balanced=temp;
        int rightHeight=0;
        int leftHeight=0;
        if(this->right) {
            rightHeight=this->right->height;
            temp=temp->right;
        }
        else if(this->left) {
            leftHeight=this->left->height;
            temp=temp->left;
        }
        else if(!this->right && !this->left) {
            balanced=balanced->up;
        }
        if(rightHeight > leftHeight) {
            this->height=rightHeight;
        }
        else {
            this->height=leftHeight;
        }
        while(temp->GetUp()) {
            TreeNode<T>* balanced=temp->GetUp();
            rightHeight=0;
            leftHeight=0;
            if(balanced->right) {
                rightHeight=balanced->right->height;
            }
            if(balanced->left) {
                leftHeight=balanced->left->height;
            }
            if(rightHeight > leftHeight) {
                balanced->height=rightHeight+1;
            }
            else {
                balanced->height=leftHeight+1;
            }
            if(balanced->balanceFactor()==2){
                if(balanced->GetLeft()->balanceFactor()==-1){
                    balanced->GetLeft()->RRFlip();
                    balanced->LLFlip();
                } else {
                    balanced->LLFlip();
                }
                if(balanced==head){
                    head = head->GetUp();
                }
            }else if(balanced->balanceFactor()==-2){
                if(balanced->GetRight()->balanceFactor()==1){
                    balanced->GetRight()->LLFlip();
                    balanced->RRFlip();
                } else {
                    balanced->RRFlip();
                }
                if(balanced==head){
                    head = head->GetUp();
                }
            } else {
                temp = temp->GetUp();
            }
            std::cout << temp->key << "-----" << std::endl;
        }
        return head;
    }
};


//Destroy all The Tree
//The Complexity is O(n) while n is the number of TreeNodes which is below
//treeNode
template <class T>
void treeNodesDestroy(TreeNode<T>* treeNode){
    if(treeNode){
        treeNodesDestroy(treeNode->GetLeft());
        treeNodesDestroy(treeNode->GetRight());
        delete treeNode;
    }
}

//InOrder pass on Tree
template<class T,typename fO>
void inOrder(TreeNode<T>* treeNode,fO& fo){
    if(treeNode){
        inOrder(treeNode->GetLeft(),fo);
        fo(treeNode);
        inOrder(treeNode->GetRight(),fo);
    }
}

#endif //DATASTRUCTURESHW1_TREENODE_H