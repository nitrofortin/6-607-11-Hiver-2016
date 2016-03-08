#ifndef NETWORK_H
#define NETWORK_H

#include <fstream>
#include <iostream>
#include <vector>
#include "community.h"

using namespace std;

class Network {
public:
	Network (char*);
	Network (const Network&);
	void displayVisitedNodes();
	void setNetworkNodes();
	void setNetworkLinks();
	void initCommunities();
	void modifyNodeCommunity(Node*, int);
	void displayNodesNeighbors();
	// void optimizeModularity();
	// void partitionProposition();
	// bool partitionEvaluation(double,double,double);
	// void partitionAcception();
	int getnbOfEdges();
	double getTotalModularity();


private:
	vector<Node *> network_nodes;
	vector<int> visited_nodes;
	vector<Community *> network_communities;
	double totalModularity;
	char* fname;
	int nbOfEdges;
	int patience;
};

#endif // NETWORK_H