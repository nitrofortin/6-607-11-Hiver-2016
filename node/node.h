#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Node
{
public:
    Node(string);
    void addNeighbor(Node *);
    bool getFlag();
    void setFlag(bool);
    Node *getPred();
    void setPred(Node *);
    list<Node *> getNeighbors();
    string getName();
    void display();
private:
    bool flag;
    list<Node *> neighbors;
    Node *pred;
    string name;
};

#endif // NODE_H

