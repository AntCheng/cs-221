#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>
using namespace std;

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
/* your code here */
    clear();
    head_=NULL;
    length_=0;
    height_=0;
    width_=0;
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
    Node* last = walk(head_,length_);
    last->next = nNode;
    nNode->next = NULL;
    length_++;
    height_=ndata.height();
    width_=ndata.width();
    
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
if(j==i+1){
    Node* iNode = walk(head_, i);
    Node* iNode_pre = walk(head_,i-1);
    Node* jNode = walk(head_,j);
    Node* jNode_next = walk(head_,j+1);

    iNode_pre->next = jNode;
    jNode->next=iNode;
    iNode->next=jNode_next;
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
int i = 0;
int start = 1;
int end = length_;

while(end>start){
    
    swap(start,end);
    start++;
    end--;
    i++;
}

// if (head_->next!=NULL) {
//     Node* temp = head_;
//     head_= head_->next;
//     reverse();  //this is not going to work
//     temp->next->next= temp ;
// } // need to put the sentinal to the front
// Node* sNode = walk(head_,length_-2);
// Node* hNode = sNode->next;
// sNode->next = NULL;

// hNode->next = head_;
// head_ = hNode;

// //still not figure out how to do, PROBLEM: MEMORY leak in the first head_

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
// do the wrong thing
    if(k==0 || k==1){
        return;
    }
    int count = 0;
    int start;
    int end;
    Node* sub_start_pre;
    Node* sub_start;
    Node* sub_start_next;

    Node* sub_end;
    Node* sub_end_next;
    for(int i =1; i<=length_;i++){
        count++;
        if(count==1){
            start=i;
            sub_start_pre = walk(head_,start-1);
            sub_start = walk(head_,start);
            sub_start_next = walk(head_,start+1);
            cout<<start<<endl;
        }
        if(count==k){
            end=i;
            //swap(start,end);
            sub_end = walk(head_,end);
            sub_end_next = walk(head_,end+1);

            sub_start_pre->next = sub_start_next;
            sub_end->next= sub_start;
            sub_start->next = sub_end_next;

            count=0;
            cout<<end<<endl;
        }
    }

    // Node* sub_start_pre;
    // Node* sub_start;
    // Node* sub_start_next;

    // Node* sub_end_pre;
    // Node* sub_end;
    // Node* sub_end_next;
    // while(int i =0; i<length_;i++){
    //     count++;
    //     if(count==1){
    //         sub_start_pre = walk(head_,i-1);
    //         sub_start = walk(head_,i);
    //         sub_start_next= walk(head_,i);
    //     }
    //     if(count==k){
    //         sub_end_pre = walk(head_,i);
    //         sub_end = walk(head_,i);
    //         sub_end_next = walk(head_,i);

    //         count=0;

    //         sub_start_pre->next = sub_end;
    //         sub_end->next = sub_start_next;

    //         sub_end_pre->next =sub_start;
    //         sub_start->next = sub_end_next;
    //     }
        
    // }
    
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
/* your code here */
    
    
    if(head_->next == head_){ ///don't even have a head_
         delete head_;
         head_=NULL;
         return;
    }
    
    while(head_->next!=NULL){
        Node* temp = head_;
        head_= head_->next;
        temp->next = NULL;
        delete temp;
        temp=NULL;
    }
   
    delete head_;
    head_=NULL;
    length_=0;
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
    length_ = 0;
    height_ = other.height_;
    width_ = other.width_;
    
    Node* otherHead = other.head_;
    head_ = new Node(); //memory leak
    
    //if the clear is call, there would be head_ pointer, but it point to nowhere
    // if(otherHead->next==otherHead){
    //     return;
    // }
   
    for(int i =0; i < other.length_;i++){
        
        otherHead = otherHead->next;
        insertBack(otherHead->data);
        // Block h = otherHead->data; //BUG
        // Node* newNode = new Node(h);
        // temp->next = newNode;
        // temp=temp->next;

    }
    
}
