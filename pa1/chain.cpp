#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
/* your code here */
    clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
/* your code here */
    
    Node* nNode = new Node(ndata);
    if(head_->next == head_){
        head_->next = nNode;
    }else{
        Node* last = walk(head_,length_);
        last->next = nNode;
        nNode->next = NULL;
    }
    

}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
/* your code here */
if(i==j){
    return;
}
Node* iNode = walk(head_, i);
Node* iNode_pre = walk(head_,i-1);
Node* iNode_next = walk(head_, i+1);

Node* jNode = walk(head_,j);
Node* jNode_pre = walk(head_,j-1);
Node* jNode_next = walk(head_,j+1);

iNode_pre->next = jNode;
jNode->next = iNode_next;

jNode_pre ->next = iNode;
iNode->next = jNode_next;

iNode = NULL;
iNode_next = NULL;
iNode_pre = NULL;
jNode = NULL;
jNode_next = NULL;
jNode_pre = NULL;
//draw a graph to see what happen when i=j-1
}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
/* your code here */
if(head_->next == head_){
    return;
}


if (head_->next!=NULL) {
    Node* temp = head_;
    head_= head_->next;
    reverse();
    temp->next->next= temp ;
} // need to put the sentinal to the front
Node* sNode = walk(head_,length_-2);
Node* hNode = sNode->next;
sNode->next = NULL;

hNode->next = head_;
head_ = hNode;

//still not figure out how to do, PROBLEM: MEMORY leak in the first head_

}

/*
* Modifies the current chain by "rotating" every group of k nodes by one position.
* In every k-node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{
/* your code here */
    if(k==0 || k==1){
        return;
    }
    Node* firstNode = head_->next;
    Node* firstNode_next = firstNode->next;

    Node* tarNode_pre = walk(head_,k-1);
    Node* targetNode = walk(head_,k);
    Node* tarNode_next = walk(head_,k+1); //when walk out of the range, it returns NULL
    

    head_->next = targetNode;
    targetNode->next = firstNode_next;
    tarNode_pre->next = firstNode;
    firstNode->next = tarNode_next;
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
/* your code here */
    if(head_->next == head_){
         delete head_;
         return;
    }
    while(head_->next!=NULL){
        Node* temp = head_;
        head_= head_->next;
        delete temp;
        length_--;
    }
    delete head_;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
/* your code here */
    height_ = other.height_;
    width_ = other.width_;
    length_ = other.length_;

    Node* otherHead = other.head_;
    //Node* head_ = new Node();
    Node* temp = head_; //if the clear is call, there would be no head_ pointer
    // if(otherHead->next==otherHead){
    //     return;
    // }
    
    for(int i =0; i < other.length_;i++){
        
        otherHead = otherHead->next;
        Block h = otherHead->data;
        Node* newNode = new Node(h);
        temp->next = newNode;
        temp=temp->next;

    }
}
