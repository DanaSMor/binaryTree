#include <iostream>
class Node{
    private:
        int data;
        Node* right;
        Node* left;
    
    public:
    Node(int i)
    {
        data=i;
        right=left=NULL;
    }

    int getData()
    {
        return data;
    }
    void setData(int i)
    {
        this->data=i;
    }

    Node* getRight()
    {
        return right;
    }

    Node* getLeft()
    {
        return left;
    }

    void setRight(Node *n)
    {
        right = n;
    }
        void setLeft(Node *n)
    {
        left = n;
    }

};
namespace ariel {

class Tree{
    private:
        Node *r;
        int capacity;
        
    public:
        Tree()
        {
            capacity=0;
            r=NULL;
        }
        Tree& insert(int i);
        void remove(int i);
        Node* removeR(Node* r, int i);
        int size();
        bool contains(int i);
        int root();
        int parent(int i);
        int left(int i);
        int right(int i);
        void print();
        void inorderP(Node *cur);
        Node* getNode(int i);
        Node* minNode(Node *root);


};
    }
