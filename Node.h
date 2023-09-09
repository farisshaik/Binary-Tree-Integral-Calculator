//Faris Shaik

#ifndef NODE_H
#define NODE_H

template <typename T> class BinTree;

template <typename T> class Node {
    friend class BinTree<T>;
private:
    T data;
    Node *left, *right;
public:
    Node(T);
    T getData();
    Node<T>* getLeft() const;
    Node<T>* getRight() const;
};

template<typename T> Node<T>::Node(T in) {
    data = in;
    left = NULL;
    right = NULL;
}

template<typename T> T Node<T>::getData() {
    return data;
}

template<typename T> Node<T>* Node<T>::getLeft() const {
    return left;
}

template<typename T> Node<T>* Node<T>::getRight() const {
    return right;
}


#endif //NODE_H
