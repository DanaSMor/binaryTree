#include <iostream>
#include "Tree.hpp"
using namespace ariel;
    
    Tree& Tree::insert(int i)
    {
        //checks if the tree caontains i
        if(contains(i)) 
            throw std::runtime_error("duplicate numbers");
        if(this->r==NULL)
        { 
                this->r=new Node(i);
                this->r->setLeft(NULL);
                this->r->setRight(NULL);
        }
                else
        {
            Node *cur=this->r;
            bool flag=true;
            while(flag)
            {
                if(cur->getData() >i)
                {
                    if(cur->getLeft()==NULL)
                    {
                        cur->setLeft(new Node(i));
                        flag=false;
                    }
                    else
                    {
                        cur=cur->getLeft();
                    }                   
                }
                else
                {
                    if(cur->getRight()==NULL)
                    {
                        cur->setRight(new Node(i));
                        flag=false;
                    }
                    else
                    {
                        cur=cur->getRight();
                    }  
                } 
            }
            
        }
        capacity++;
        return *this;
    }

//returns true if exist such i in tree
bool Tree::contains(int i)
{
    Node *current = r;

    while (current != NULL)
    {
        if (i==current->getData())
            return true;
        else if (i > current->getData())
        {
            current = current->getRight();
        }
        else 
        {
            current = current->getLeft();
        }
    }
    return false;
}

void Tree::remove(int i)
{
    if (!contains(i) || r == NULL)
        throw std::runtime_error("this num is not in the tree");
    //if the root is equal to i
    if (r->getData() == i)
    {
        //if the root has only right child
        if(r->getRight()!=NULL && r->getLeft()== NULL) 
        {
            Node *temp = r->getRight();
            delete r;
            r = temp;
        }
        //if the root has only left child
        else if(r->getRight()==NULL && r->getLeft()!= NULL) 
        {
            Node *temp = r->getLeft();
            delete r;
            r = temp;
        }
        //if the root has no children
        else if(r->getRight()==NULL && r->getLeft()== NULL) 
        { 
            delete r;
            r=NULL;
        }
        //if the rot has two childrens
        else 
        {
            //search for the smalles value in the right tree, removes it and set it to be the root
            Node *min = minNode(r->getRight());
            int minimum = min->getData();
            remove(minimum); 
            r->setData(minimum); 
            capacity++; 
        }
    }
    //regular node
    else 
    {
        Node *dest = getNode(i);
        Node *ancestor = getNode(parent(i));
        bool isRight;
        if (ancestor->getRight()!=NULL && ancestor->getRight()->getData() == i)
            isRight = true;
        else
            isRight = false;
        //if the node has only left child
        if (dest->getRight() == NULL && dest->getLeft() != NULL) 
        {
           
            if (isRight){ancestor->setRight(dest->getLeft());}
            else {ancestor->setLeft(dest->getLeft());}
            delete dest;
        }
        //if the node has only right child
        else if (dest->getRight() != NULL && dest->getLeft() == NULL) 
        {
           
            if (isRight){ancestor->setRight(dest->getRight());}
            else {ancestor->setLeft(dest->getRight());}
            delete dest;
        }
        //if the node has no childs at all
        else if (dest->getRight() == NULL && dest->getLeft() == NULL)
        {
           
            if (isRight){ancestor->setRight(NULL);}
            else {ancestor->setLeft(NULL);}
            delete dest;
        }
        //if the node has two childrens
        else
        {
            Node *min = minNode(dest->getRight());
            int minimum = min->getData();
            remove(minimum);
            dest->setData(minimum);
            capacity++;
        }
    }
    capacity--;
}

//returns the size of the tree
    int Tree::size()
    {return this->capacity;}
    
    
//returns the value of the root
    int Tree::root()
    {
        if(this->r != NULL) return r->getData();
        throw std::runtime_error("tree is empty");
    }

 //returns the value of the parent of the node   
    int Tree::parent(int i)
    {
        bool contain=false;

        Node *cur=this->r;
        //if the tree is empty
        if(cur==NULL)
             throw std::runtime_error("tree is empty");
        //if the root is the given integer
        if(cur->getData() ==i)
             throw std::runtime_error("root does not have a ancestorent");
        
        Node *ancestor=this->r;
        while((cur != NULL)&&!contain)
        {
            if(cur->getData() ==i)
                {
                    contain=true;
                }
            else if(cur->getData() >i)
            {
                ancestor=cur;
                cur = cur->getLeft();
            }
            else
            {
                ancestor=cur;
                cur = cur->getRight();
            }                        
        }
        //if the tree doesn't contain the integer
        if(!contain)
            throw std::runtime_error("this num is not in the tree");
        return ancestor->getData();   

    }

    //returns the left child of node
    int Tree::left(int i)
    {
        if(!contains(i))
            throw std::runtime_error("this num is not in the tree");
        bool contain=false;

        Node *cur=getNode(i);

        if(cur==NULL)
             throw std::runtime_error("tree is empty");

        cur = cur->getLeft();
        
        if(cur==NULL)
            throw std::runtime_error("no left child");

        return cur->getData();  
    }

    //returns the right child of node
    int Tree::right(int i)
    {
        if(!contains(i))
            throw std::runtime_error("this num is not in the tree");
        bool contain=false;

        Node *cur=getNode(i);

        if(cur==NULL)
             throw std::runtime_error("tree is empty");

        cur = cur->getRight();
        
        if(cur==NULL)
            throw std::runtime_error("no right child");

        return cur->getData();  
    }

    //print tree inorder
    void Tree::print()
    {
        inorderP(this->r);
    }

    Tree::~Tree()
    {
        destroyT(r);
    }

    //////////////////////private methods///////////////////////
    
    //destroy the tree
    void Tree::destroyT(Node * leaf)
    {
        if(leaf!=NULL)
        {
            destroyT(leaf->getLeft());
            destroyT(leaf->getRight());
            delete leaf;
        }
    }
    //prints inorder
    void Tree::inorderP(Node *cur)
    {
        if(cur!=NULL)
        {
            inorderP(cur->getLeft());
            std::cout <<cur->getData() <<" ";
            inorderP(cur->getRight());

        }

    }

    // return the node 
    Node *Tree::getNode(int i)
    {
        Node *current = r;

        while (current != NULL)
        {
            if (i==current->getData())
                return current;
            else if (i > current->getData())
            {
                current = current->getRight();
            }
            else 
            {
                current = current->getLeft();
            }
        }
        return NULL;
    }
    // Search for the min data from the dest node
    Node* Tree::minNode(Node *root)
    {
        while (root->getLeft() != NULL)
        {
            root = root->getLeft();
        }
        return root;
    }



