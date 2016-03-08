#include "node.h"

Node::Node(string s)
{
    name = s;
    flag = false;
    pred = 0;
}

void Node::addNeighbor(Node *n)
{
    neighbors.push_back(n);
}

void Node::setFlag(bool b)
{
    flag = b;
}

bool Node::getFlag()
{
    return flag;
}

void Node::setPred(Node *n)
{
    pred = n;
}

Node * Node::getPred()
{
    return pred;
}

string Node::getName()
{
    return name;
}

list<Node *> Node::getNeighbors()
{
    return neighbors;
}

void Node::display()
{
    cout<<"Node "<<name<<endl;
    for(list<Node *>::iterator it=neighbors.begin();it!=neighbors.end();it++)
        cout<<(*it)->getName()<<" ";
    cout<<endl;
}

