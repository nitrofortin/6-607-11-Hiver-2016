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
	Community (int,int);
	~Community();
	void addNode(Node*);
	void removeNode(Node*);

	void setnbOfEdgesIO();
	void setModularity();

	vector<Node *>  getCommunityNodes();
	int getnbOfEdgesIn();
	int getnbOfEdgesOut();
	double getModularity();
	int getCommunityId();

private:
	vector<Node *> community_nodes;
	int nbOfEdgesIn;
	int nbOfEdgesOut;
	int sumOfDegrees;
	double com_modularity;
	int community_id;
	int networknbOfEdges;
};

#endif // COMMUNITY_H