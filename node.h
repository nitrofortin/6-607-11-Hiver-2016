#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Node
{
public:
    Node(string,int);
    void addNeighbor(Node *);
    list<Node *> getNeighbors();
    string getName();
    void displayNeighbors();
    int getDegree();
    int getId();
    void setCommunityId(int);
    int getCommunityId();

private:
    bool flag;
    list<Node *> neighbors;
    Node *pred;
    string name;
    int id;
    int community_id;
};

#endif // NODE_H
