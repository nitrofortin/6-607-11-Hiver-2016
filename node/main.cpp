#include <iostream>
#include <vector>

#include "node.h"

using namespace std;

void link(Node *n1,Node *n2)
{
    n1->addNeighbor(n2);
    n2->addNeighbor(n1);
}

int main()
{
    vector<Node *> nodes;

    nodes.push_back(new Node("A"));//0
    nodes.push_back(new Node("B"));//1
    nodes.push_back(new Node("C"));//2
    nodes.push_back(new Node("D"));//3
    nodes.push_back(new Node("E"));//4
    nodes.push_back(new Node("F"));//5
    nodes.push_back(new Node("G"));//6
    nodes.push_back(new Node("H"));//7

    link(nodes[0],nodes[1]);
    link(nodes[0],nodes[2]);
    link(nodes[1],nodes[2]);
    link(nodes[1],nodes[3]);
    link(nodes[1],nodes[4]);
    link(nodes[2],nodes[3]);
    link(nodes[2],nodes[6]);
    link(nodes[3],nodes[5]);
    link(nodes[3],nodes[6]);
    link(nodes[4],nodes[5]);
    link(nodes[5],nodes[7]);
    link(nodes[6],nodes[7]);

    for(unsigned int i=0;i<nodes.size();i++)
        nodes[i]->display();

    list<Node *> temp;
    temp.push_back(nodes[0]);
    nodes[0]->setFlag(true);
    list<Node *> permanent;

    while(temp.size() >=1)
    {
        Node * n = temp.front();
        temp.pop_front();
        permanent.push_back(n);
        list<Node *> neigh = n->getNeighbors();
        for(list<Node *>::iterator it=neigh.begin();it != neigh.end();it++){
            if(!(*it)->getFlag()){
                (*it)->setFlag(true);
                (*it)->setPred(n);
                temp.push_back(*it);
            }
        }
    }

    for(unsigned int i=0;i<nodes.size();i++)
        if(nodes[i]->getPred())
            cout<<nodes[i]->getName()<<" pred = "<<nodes[i]->getPred()->getName()<<endl;
    for(unsigned int i=0;i<nodes.size();i++){
        Node *n = nodes[i];
        cout<<"Node "<<n->getName()<<": ";
        while(n->getPred()){
            n = n->getPred();
            cout <<n->getName()<<" ";
        }
        cout<<endl;
    }


    return 0;
}

