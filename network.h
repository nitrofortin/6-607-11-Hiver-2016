#ifndef NETWORK_H
#define NETWORK_H

#include <fstream>
#include <iostream>
#include <vector>
// #include <random>
#include "community.h"
#define EPS 1e-10

using namespace std;

class Network {
public:
	Network (char*);
	Network (Network*);
	void copy(Network*);
	virtual Network* clone() const {return(new Network(*this));};
	void displayVisitedNodes();
	void displayCommunities();
	void setNetworkNodes();
	void setNetworkLinks();
	void setBestPartition();

	void initCommunities();
	void modifyNodeCommunity(Node*, int);
	void displayNodesNeighbors();
	void localSearch();
	void LPA();
	void LPAm();
	void softRandomPertubation(int);
	void hardRandomPertubation(int);
	void communityMerge();
	void communityDivision();
	void createSingletons();
	void communityRedistribution();
	int getnbOfEdges();
	int getNumberOfCommunties();
	double getTotalModularity();
	void flagTransmission(Node*,Node*);
	int randomNodeId();
	int randomCommunityId();
	void loadSavedPartition();
	void savePartition();
	void writeSolution();
	void dummyTransformation();
	void doubleCheck();
	vector<Node *> getNodes();
	vector<Community *> getCommunities();
	vector<int> getSavedPartition();
	vector<Community*> getEmptyCommunities();
	vector<Community*> getNonEmptyCommunities();

private:
	vector<Node *> network_nodes;
	vector<Node *> network_nodes_copy;
	vector<int> visited_nodes;
	vector<Community *> network_communities;
	vector<Community *> network_communities_copy;
	Node* random_node;
	vector<int> saved_partition;
	double totalModularity;
	char* fname;
	int nbOfEdges;
	int patience;
};

#endif // NETWORK_H