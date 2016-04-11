#ifndef COMMUNITY_H
#define COMMUNITY_H

#include <fstream>
#include <iostream>
#include <vector>
#include <tr1/tuple>
#include "node.h"


using namespace std;

class Community {
public:
	Community (Node*,int);
	Community (Community*);
	~Community();
	void addNode(Node*);
	void removeNode(Node*);
	virtual Community* clone() const {return(new Community(*this));};
	void setnbOfEdgesIO();
	void setModularity();

	const vector<Node *> & getCommunityNodes();
	int getnbOfEdgesIn();
	int getnbOfEdgesOut();
	double getModularity();
	int getCommunityId();
	bool isEmpty();
	int getNumberOfNodes();
	int getNetworknbOfEdges();

private:
	vector<Node *> community_nodes;
	int nbOfEdgesIn;
	int nbOfEdgesOut;
	double com_modularity;
	int community_id;
	int networknbOfEdges;
};

#endif // COMMUNITY_H