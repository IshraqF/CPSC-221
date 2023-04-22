#include "chain.h"
#include <cmath>
#include <iostream>
#include <map>
#include <set>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  /* your code here */
  clear();
  delete head_;
  head_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  /* your code here */
  Node *newNode = new Node(ndata);
  length_++;

  if (p == NULL) {
    newNode->prev = NULL;
    newNode->next = head_;
    if (head_ != NULL) {
      head_->prev = newNode;
    }
    head_ = newNode;
  }
  else {
    newNode->prev = p;
    newNode->next = p->next;
    p->next = newNode;
    if (newNode->next !=NULL) {
      newNode->next->prev = newNode;
    }
  }

  return newNode;
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  if (!p || !q || p == q) {
    return;
  }

  Node *pPrev = p->prev;
  Node *qPrev = q->prev;
  Node *pNext = p->next;
  Node *qNext = q->next;

  if (pPrev) {
    pPrev->next = q;
  }
  if (qPrev) {
    qPrev->next = p;
  }
  if (pNext) {
    pNext->prev = q;
  }
  if (qNext) {
    qNext->prev = p;
  }

  std::swap(p->next, q->next);
  std::swap(p->prev, q->prev);

  if (head_ == p) {
    head_ = q;
  } else if (head_ == q) {
    head_ = p;
  }

}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  /* your code here */
  Node *curr = head_;
  Node *next;

  while (curr != NULL) {
    next = curr->next;
    delete curr;
    curr = next;
  }

  head_ = NULL;
  length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  
  // Create a new node and set it to the head
  this->insertAfter(head_,Block(other.head_->data));
  // Create two pointers to traverse both chains
  Node *current = head_;
  Node *otherCurrent = other.head_;
  
  // While the other chain has a next node
  while (otherCurrent->next) {
    // Set the next node for the current chain to a new node with the data from the other chain
    this->insertAfter(current, Block(otherCurrent->next->data));
    otherCurrent->prev=current;
    
    // Move both pointers to their next nodes
    current = current->next;
    otherCurrent = otherCurrent->next;
  }

}

/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  Node * current=head_;
  std::map<Node *, std::map<Node *, double>> distToMap; // stores the closest node to the key 
  std::map<Node *, double> minDistToMap; // stores the minimum distance to the key
  std::set<Node *> usedNodeSet;
  double minDist=200000000;

  while(current){
    Node * forwardNode=current;
    Node * backwardNode=current;

    double currentDist=0;

    // Check distance to all nodes ahead, keep the minimum
    while(forwardNode->next){
      currentDist=current->data.distanceTo(forwardNode->next->data);
      distToMap[current][forwardNode->next]=currentDist;

      if(minDistToMap.count(forwardNode->next)){
        if(minDistToMap[forwardNode->next]>currentDist){
          minDistToMap[forwardNode->next]=currentDist;
        }
      } else{
        minDistToMap[forwardNode->next]=currentDist;
      }

      forwardNode=forwardNode->next;

    }
    
    // Check distance to all nodes behind, keep the minimum
    while(backwardNode->prev){
      currentDist=current->data.distanceTo(backwardNode->prev->data);
      distToMap[current][backwardNode->prev]=currentDist;
      
      if(minDistToMap.count(backwardNode->prev)){
        if(minDistToMap[backwardNode->prev]>currentDist){
          minDistToMap[backwardNode->prev]=currentDist;
        }
      } else{
        minDistToMap[backwardNode->prev]=currentDist;
      }
      
      backwardNode=backwardNode->prev;

    }

    current=current->next;
  }

  double maxDistTo=0;
  Node * firstNode;

  for(auto const& node:minDistToMap){
      if(maxDistTo<node.second){
        maxDistTo=node.second;
        firstNode=node.first;
      }
  }

  this->swap(head_,firstNode);
  current=head_;
  usedNodeSet.insert(current);
  Node * nextCurrent;
  minDist=100000;
  //   // find maxDistanceTo
  for(uint i=0;i<distToMap.size()-1;i++){
    for(auto const& node:distToMap[current]){
      if(node.second<minDist && usedNodeSet.find(node.first)==usedNodeSet.end()){
        minDist=node.second;
        nextCurrent=node.first;
      }
    }
    this->swap(current->next,nextCurrent);
    usedNodeSet.insert(nextCurrent);
    current=current->next;
    minDist=100000;
  }

  current->next=NULL;

}
