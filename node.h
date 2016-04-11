#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{
public:
    Node(string,int);
    Node(Node*);
    void addNeighbor(Node *);
    const vector<Node *> & getNeighbors();
    virtual Node* clone() const {return(new Node(*this));};
    string getName();
    void displayNeighbors();
    int getDegree();
    int getId();
    void setCommunityId(int);
    int getCommunityId();

private:

    vector<Node *> neighbors;
    string name;
    int id;
    int community_id;
};

#endif // NODE_H
