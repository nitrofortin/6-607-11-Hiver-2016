#include "network.h"
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// #include <random>

using namespace std;

bool simpleSort (int i,int j) { 
	return (i<j);
}

Network::Network(char* filename){
	patience = 10;
	ifstream input;
	fname = filename;
	input.open(fname, fstream::in);
	nbOfEdges = 0;
	while (!input.eof()){
		nbOfEdges++;
		int origine, destination;
		input >> origine >> destination;
		if(find(visited_nodes.begin(), visited_nodes.end(), origine) != visited_nodes.end()) {
			;
		} else {
			visited_nodes.push_back(origine);
		}
		if(find(visited_nodes.begin(), visited_nodes.end(), destination) != visited_nodes.end()) {
			;
		} else {
			visited_nodes.push_back(destination);
		}
	}
	nbOfEdges -= 1;
	// cout << "Number of edges: " << nbOfEdges << endl;
	input.close();
	setNetworkNodes();
	setNetworkLinks();
	// cout << "Taille de visited_nodes: " << visited_nodes.size() << endl;
	sort(visited_nodes.begin(),visited_nodes.end(),simpleSort);
}

Network::Network(const Network &net){
	network_nodes = net.network_nodes;
	visited_nodes = net.visited_nodes;
	network_communities = net.network_communities;
	totalModularity = net.totalModularity;
	fname = net.fname;
	nbOfEdges = net.nbOfEdges;
}

void Network::setNetworkNodes(){
	for(std::vector<int>::size_type i = 0; i != visited_nodes.size(); i++) {
		stringstream node_id; 
		node_id << i;
		network_nodes.push_back(new Node(node_id.str(),i));
	}
}

void Network::setNetworkLinks()
{
	ifstream input;
	input.open(fname, fstream::in);
	bool flag = true;
	int temp = 99999;
	int temp2 = 99999;
	while (!input.eof()){
		unsigned int origine, destination;
		input >> origine >> destination;
		list<Node *> neighbors = network_nodes[origine]->getNeighbors();

		if (temp==origine && temp2==destination){
			flag = false;
		}
		if(flag){
			network_nodes[origine] -> addNeighbor(network_nodes[destination]);
			network_nodes[destination] -> addNeighbor(network_nodes[origine]);
		}
		flag = true;
		temp = origine;
		temp2 = destination;
	}
	input.close();
}

void Network::initCommunities(){
	for(vector<int>::size_type i = 0; i != network_nodes.size(); i++) {
		int node_id = network_nodes[i]->getId();
	    network_communities.push_back(new Community(node_id,nbOfEdges));
	    network_communities[i] -> addNode(network_nodes[i]);
	}
	for(vector<int>::size_type i = 0; i != network_nodes.size(); i++) {
		network_communities[i] -> setnbOfEdgesIO();
		cout << "Nb of edges out (com. " << i << "): " << network_communities[i] -> getnbOfEdgesOut() << endl;
	   	cout << "Nb of edges in (com. " << i << "): " << network_communities[i] -> getnbOfEdgesIn() << endl;
	   	cout << "Com. modularity " << network_communities[i]->getModularity() << endl;
	}
}

void Network::modifyNodeCommunity(Node* n, int com_id){
	for(vector<int>::size_type i = 0; i != network_communities.size(); i++){
		if ((network_communities[i]->getCommunityId())==n->getCommunityId()){
			network_communities[i]->removeNode(n);
		} else if ((network_communities[i]->getCommunityId())==com_id){
			n->setCommunityId(com_id);
			network_communities[i] -> addNode(n);
		}
	}
}

// void Network::partitionProposition(){

// }

// bool Network::partitionEvaluation(double temperature){
// 	srand (time(NULL));
// 	double Q = getTotalModularity();
// 	double transProb;
// 	if (newQ > Q){
// 		return 1;
// 	}
// 	if (temperature == 0.0) {
// 		return 0;
// 	}
// 	transProb = exp(-(Q-newQ)/temperature);
// 	return ((rand()%100 + 1)/100.0) < transProb;
// }

// void Network::partitionAcception(){
// 	;
// }

// void Network::optimizeModularity(Network copy, Network original){
// 	double T = 1.0;
// 	while(T>0.01){
// 		partitionProposition();
// 		if(partitionEvaluation(T)){
// 			partitionAcception();
// 		}
// 		T = T - 0.0001;
// 	}
// }

void Network::displayVisitedNodes(){
	for(vector<int>::size_type i = 0; i != visited_nodes.size(); i++) {
	    cout << visited_nodes[i] << endl;
	}
}

void Network::displayNodesNeighbors(){
	// int k =0;
	for(std::vector<int>::size_type i = 0; i != visited_nodes.size(); i++) {
		network_nodes[i]->displayNeighbors();
		// cout << "Node degree: " << network_nodes[i]->getDegree() << endl;
		// cout << "Node " << network_nodes[i]->getName() << " got neighbor(s) " << endl;
		// list<Node *> neigh = network_nodes[i]->getNeighbors();
		// for(list<Node *>::iterator j=neigh.begin();j != neigh.end();j++){
		// 	cout << (*j)->getName() << endl;
		// 	k++;
        // }
	}
	// cout << k << " neighbors" << endl;
}

double Network::getTotalModularity(){
	totalModularity = 0;
	for(vector<int>::size_type i = 0; i != network_communities.size(); i++) {
		totalModularity += network_communities[i] -> getModularity();
	}
	return totalModularity;
}

int Network::getnbOfEdges(){
	return nbOfEdges;
}

