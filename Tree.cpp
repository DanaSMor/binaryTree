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
        Node *par = getNode(parent(i));
        bool isRight;
        if (par->getRight()->getData() == i)
            isRight = true;
        else
            isRight = false;
        //if the node has only left child
        if (dest->getRight() == NULL && dest->getLeft() != NULL) 
        {
           
            if (isRight){par->setRight(dest->getLeft());}
            else {par->setLeft(dest->getLeft());}
            delete dest;
        }
        //if the node has only right child
        else if (dest->getRight() != NULL && dest->getLeft() == NULL) 
        {
           
            if (isRight){par->setRight(dest->getRight());}
            else {par->setLeft(dest->getRight());}
            delete dest;
        }
        //if the node has no childs at all
        else if (dest->getRight() == NULL && dest->getLeft() == NULL)
        {
           
            if (isRight){par->setRight(NULL);}
            else {par->setLeft(NULL);}
            delete dest;
        }
        //if the node has two childrens
        else
        {
            Node *min = minNode(dest->getLeft());
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
    {return this->r->getData();}

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
             throw std::runtime_error("root does not have a parent");
        
        Node *par=this->r;
        while((cur != NULL)&&!contain)
        {
            if(cur->getData() ==i)
                {
                    contain=true;
                }
            else if(cur->getData() >i)
            {
                par=cur;
                cur = cur->getLeft();
            }
            else
            {
                par=cur;
                cur = cur->getRight();
            }                        
        }
        //if the tree doesn't contain the integer
        if(!contain)
            throw std::runtime_error("this num is not in the tree");
        return par->getData();   

    }

    //returns the left child of node
    int Tree::left(int i)
    {
        bool contain=false;

        Node *cur=this->r;

        if(cur==NULL)
             throw std::runtime_error("tree is empty");

        while((cur != NULL)&&!contain)
        {
            if(cur->getData() ==i)
                {
                    contain=true;
                }
            else if(cur->getData() >i)
            {
                cur = cur->getLeft();
            }
            else
            {             
                cur = cur->getRight();
            }                        
        }
        if(!contain)
            throw std::runtime_error("this num is not in the tree");
        cur = cur->getLeft();
        if(cur==NULL)
            throw std::runtime_error("no left child");
        return cur->getData();  
    }

    //returns the right child of node
    int Tree::right(int i)
    {
        bool contain=false;

        Node *cur=this->r;

        if(cur==NULL)
             throw std::runtime_error("tree is empty");

        while((cur != NULL)&&!contain)
        {
            if(cur->getData() ==i)
                {
                    contain=true;
                }
            else if(cur->getData() >i)
            {
                cur = cur->getLeft();
            }
            else
            {             
                cur = cur->getRight();
            }                        
        }
        if(!contain)
            throw std::runtime_error("this num is not in the tree");
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



