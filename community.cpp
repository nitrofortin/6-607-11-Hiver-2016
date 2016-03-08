#include "community.h"
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <string>
#include <sstream>
#include <cmath>


using namespace std;


Community::Community(int id,int net_nbOfEdges){
	// networknbOfEdges = net->getnbOfEdges();
	networknbOfEdges = net_nbOfEdges;
	community_id = id;
}

Community::~Community(){
	;// 
}

void Community::setnbOfEdgesIO(){
	nbOfEdgesIn = 0;
	nbOfEdgesOut = 0;
	for(std::vector<int>::size_type i = 0; i != community_nodes.size(); i++) {
		list<Node*> com_node_neigh = community_nodes[i]-> getNeighbors();
		for(list<Node *>::iterator j=com_node_neigh.begin();j != com_node_neigh.end();j++){
			if((*j)->getCommunityId() == community_id){
				nbOfEdgesIn += 1;
			} else {
				nbOfEdgesOut += 1;
			}
		}
		nbOfEdgesIn /= 2;
	}
	setModularity();
}

void Community::addNode(Node* n){
	community_nodes.push_back(n);
	n->setCommunityId(community_id);
	setnbOfEdgesIO();
}

void Community::removeNode(Node* n){
   community_nodes.erase(std::find(community_nodes.begin(),community_nodes.end(),n));
	setnbOfEdgesIO();
}


void Community::setModularity(){
	cout << "Network nb of edges: " << networknbOfEdges << endl;
	com_modularity = (double)nbOfEdgesIn/(double)networknbOfEdges - pow(((2*(double)nbOfEdgesIn+(double)nbOfEdgesOut)/(2*(double)networknbOfEdges)),2);
}

vector<Node *> Community::getCommunityNodes(){
	return community_nodes;
}

int Community::getCommunityId(){
	return community_id;
}

int Community::getnbOfEdgesIn(){
	return nbOfEdgesIn;
}

int Community::getnbOfEdgesOut(){
	return nbOfEdgesOut;
}

double Community::getModularity(){
	return com_modularity;
}

