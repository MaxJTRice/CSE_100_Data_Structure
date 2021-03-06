#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

template <typename Data>
class RST : public BST<Data> {

public:

  /* Insert new data into the RST if it is not already present.
   * Input
   *    item - the data to insert.
   *    return - true if the item was inserted. If the item was already contained in
   *       the tree then return false.
   */
  virtual bool insert(const Data& item) {

    // TODO: Implement this function!
        BSTNode<Data>* newNode=new BSTNode<Data>(item);
        newNode->priority=rand();
        if (this->root==0) {
          this->root = newNode;
          return true;
        }
        else {
          BSTNode<Data>* current = this->root;
          BSTNode<Data>* last = 0;
          while ( current != 0 ) {
            if ( item < current->data ) {
              last = current;
              current = current->left;
            }
            else if ( current->data < item ) {
              last = current;
              current = current->right;
            }
            else {  // already in the tree
              delete newNode;
              newNode=0;
              return false;
            }
          }
          if ( item < last->data ) {
            last->left = newNode;
            newNode->parent = last;
          }
          else {
            last->right = newNode;
            newNode->parent = last;
          }
        }
        while(true){
            if(newNode->parent&&(newNode->parent->priority<newNode->priority)){
                    if(newNode==newNode->parent->left){
                        rotateRight(newNode->parent,newNode);
                    }
                    else if(newNode==newNode->parent->right){
                        rotateLeft(newNode->parent,newNode);
                    }
            }
            else break;
        }
        return true;
  }


private:

  /* Perform a 'right rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' pointers
   * of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a left child
   *    child - the left child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but switched
   *   in level, meaning 'par' will effectively become the right-child of 'child'.
   *
   */
  void rotateRight( BSTNode<Data>* par, BSTNode<Data>* child ) {

    // TODO: Implement this function!
      bool flag=true;
      BSTNode<Data>*gp=par->parent;
      BSTNode<Data>*temp=child->right;
      child->right=par;
      par->parent=child;
      par->left=temp;
      if(temp!=0){
          temp->parent=par;
      }
      if(gp==0){
          this->root=child;
          child->parent=0;
          return;
      }
      if(par==gp->right)flag=false;
      child->parent=gp;
      if(flag)gp->left=child;
      else gp->right=child;
      return;
  }


  /* Perform a 'left rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' pointers
   * of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a right child
   *    child - the right child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but switched
   *   in level, meaning 'par' will effectively become the left-child of 'child'.
   *
   */
  void rotateLeft( BSTNode<Data>* par, BSTNode<Data>* child )
  {

    // TODO: Implement this function!
      bool flag=true;
      BSTNode<Data>*gp=par->parent;
      BSTNode<Data>*temp=child->left;
      child->left=par;
      par->parent=child;
      par->right=temp;
      if(temp!=0){
          temp->parent=par;
      }
      if(gp==0){
          this->root=child;
          child->parent=0;
          return;
      }
      if(par==gp->right)flag=false;
      child->parent=gp;
      if(flag)gp->left=child;
      else gp->right=child;
      return;
  }

public:

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   *
   * Calls BST::insert so we can add data to test rotateRight and rotateLeft before
   * implementing the fully correct version of RST::insert.
   *
   */
  bool BSTinsert(const Data& item) {

    return BST<Data>::insert(item);

  }

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   *
   * Locates the node for an item and rotates it left or right without changing the
   * left->right order of nodes in the RST
   * Input
   *    item - the Data item to rotate.
   *    leftOrRight - if true then rotateLeft, otherwise rotateRight
   *    output - 0 if item could be found and had a child to rotate with, 1 if not. -1 if
   *         rotation failed for other reasons
   */
  int findAndRotate(const Data& item, bool leftOrRight) {

     BSTNode<Data>* current = RST<Data>::root;
     while ( current != 0 ) {
       if ( item < current->data ) {
         current = current->left;
       }
       else if ( current->data < item ) {
         current = current->right;
       }
       else {  // already in the tree
         break;
       }
     }

     if (current == 0 or current->data != item) {
       return 1;
     }

     if (leftOrRight) {
       if (current->right == 0) {
         return 1;
       }
       BSTNode<Data>* right = current->right;
       rotateLeft(current, current->right);

       // make sure we actually do a rotation
       
       // to be delete!!!!!!
       cout<<"doing left rotate"<<endl;
       if (current->right == right) {
         return -1;
       }

     } else {
       if (current->left == 0) {
         return 1;
       }
       BSTNode<Data>* left = current->left;
       rotateRight(current, current->left);

       // make sure we actually do a rotation
       // to be delete!!!!!!
       cout<<"doing right rotate"<<endl;
       if (current->left == left) {
         return -1;
       }
     }
     return 0;
  }
};
#endif // RST_HPP
