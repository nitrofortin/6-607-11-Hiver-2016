#include "node.h"

Node::Node(string s, int i)
{
    id = i;
    name = s;
    flag = false;
    // community_id = i;
}

void Node::addNeighbor(Node *n)
{
    neighbors.push_back(n);
}

void Node::setCommunityId(int id){
    community_id = id;
}

string Node::getName()
{
    return name;
}

list<Node *> Node::getNeighbors()
{
    return neighbors;
}

int Node::getDegree(){
    return getNeighbors().size();
}

int Node::getId(){
    return id;
}

int Node::getCommunityId(){
    return community_id;
}

void Node::displayNeighbors(){
    cout<<"Node "<<name<<endl;
    for(list<Node *>::iterator it=neighbors.begin();it!=neighbors.end();it++)
        cout<<(*it)->getName()<<" ";
    cout<<endl;
}
