//Faris Shaik

#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <vector>

template <typename T> class Node;

template <typename T> class BinTree {
    friend class Node<T>;
private:
    Node<T>* root;
    void destroyRecursively(Node<T>*);
    void insertHelper(Node<T>**, T);
    Node<T>* searchHelper(Node<T>* ,T);
    std::vector<T> orderedVectorHelper(Node<T>*);
    Node<T>* removeHelper(Node<T>*, T);
    Node<T>* minValueNode(Node<T>*);

public:
    BinTree();
    ~BinTree();
    void insert(T);
    Node<T>* search(T);
    Node<T>* remove(T);
    std::vector<T> inOrderTraversal();
};

template<typename T> BinTree<T>::BinTree() {    // empty tree constructor
    root = NULL;
}

template<typename T> void BinTree<T>::insert(T in) {    // call helper function to insert
    insertHelper(&root, in);
}

template<typename T> void BinTree<T>::insertHelper(Node<T>** curr, T in) {
    if(*curr == NULL){ *curr = new Node<T>(in); }   // if empty spot, create new node and place it there
    else{
        if(in < (*curr)->data){ insertHelper(&((*curr)->left), in); }               // if less than, go to left recursively
        else if(in > (*curr)->data){ insertHelper(&((*curr)->right), in); }         // if greater than, go to right recursively
        else{ (*curr)->data += in; }                                                     // append data is value is equal (in this case, if the exponent values are the same)
    }
}

template<typename T> Node<T> *BinTree<T>::search(T in) {    // call helper function to search
    return searchHelper(root, in);
}

template<typename T> Node<T> *BinTree<T>::searchHelper(Node<T>* curr, T in) {
    if(curr != NULL){                   // if not at the end (leaf) of tree
        if(curr->data == in){
            return curr;                // return pointer if value is equal
        }
        else if (in < curr->data){
            return searchHelper(curr->left, in);            // if less than, go to left recursively
        }
        else{ return searchHelper(curr->right, in); }       // if greater than, go to right recursively
    }
    else return NULL;                                            // return NULL if at end of tree
}

template<typename T> Node<T> *BinTree<T>::minValueNode(Node<T>* curr) {    // min value (helper for remove) if node has two children
    if(curr == NULL or curr->left == NULL){ return curr; }                 // leftmost value, after going right once
    else{ minValueNode(curr->left); }
}

template<typename T> Node<T> *BinTree<T>::remove(T in) {    // call helper function to remove
    return removeHelper(root, in);
}

template<typename T> Node<T> *BinTree<T>::removeHelper(Node<T>* curr, T in) {
    if(!curr){ return curr; }

    if(in < curr->data){ curr->left = removeHelper(curr->left, in); }           // if less than, go to left recursively
    if(in > curr->data){ curr->right = removeHelper(curr->right, in); }         // if greater than, go to right recursively
    else{
        if(curr->left == NULL and curr->right == NULL){ return NULL; }               // no child
        else if(curr->left == NULL){
            Node<T>* temp = curr->right;
            free(curr);
            return temp;
        }
        else if(curr->right == NULL){                                                // one child
            Node<T>* temp = curr->left;
            free(curr);
            return temp;
        }
        else{                                                                        // two children, replace with inorder successor
            Node<T>* temp = minValueNode(curr->right);
            curr->data = temp->data;
            curr->right = removeHelper(curr->right, temp->data);
        }
        return curr;
    }

}

template<typename T> BinTree<T>::~BinTree() {   // recursive delete tree
    destroyRecursively(root);
}

template<typename T> void BinTree<T>::destroyRecursively(Node<T>* curr) {
    if(curr){
        destroyRecursively(curr->left);     // go left recursively
        destroyRecursively(curr->right);    // go right recursively
        delete curr;                             // delete node
    }
}

template<typename T> std::vector<T> BinTree<T>::inOrderTraversal(){         // call helper function to traverse
    return orderedVectorHelper(root);
}

template<typename T> std::vector<T> BinTree<T>::orderedVectorHelper(Node<T>* curr){       // reverse in order traversal
    if(!curr){ return std::vector<T>(); }

    std::vector<T> out;
    if(curr->right){
        std::vector<T> rightSide = orderedVectorHelper(curr->right);                // go right recursively
        out.insert(out.end(), rightSide.begin(), rightSide.end());
    }
    out.push_back(curr->data);                                                           // add to output
    if(curr->left){
        std::vector<T> leftSide = orderedVectorHelper(curr->left);                  // go left recursively
        out.insert(out.end(), leftSide.begin(), leftSide.end());
    }
    return out;                                                                          // output vector of all T in (reverse) order
}

#endif //BINTREE_H

