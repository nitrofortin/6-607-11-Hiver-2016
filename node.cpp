#include "node.h"

Node::Node(string s, int i)
{
    id = i;
    name = s;
    // community_id = i;
}

Node::Node(Node* n){
    neighbors = getNeighbors();
    name = getName();
    id = getId();
    community_id = getCommunityId();
}

void Node::addNeighbor(Node *n)
{
    bool flag = true;
    for (unsigned int i; i<neighbors.size();i++){
        if (neighbors[i]->getId() == n->getId()){
            flag = false;
            if (n->getId() == 33){
                cout << "yolo" << endl;
            }
        }
    }
    if (flag){
        neighbors.push_back(n);
    }
}

void Node::setCommunityId(int id){
    community_id = id;
}

string Node::getName()
{
    return name;
}

const vector<Node *> & Node::getNeighbors()
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
    for(vector<Node *>::iterator it=neighbors.begin();it!=neighbors.end();it++)
        cout<<(*it)->getName()<<" ";
    cout<<endl;
}
