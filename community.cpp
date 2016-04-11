#include "community.h"
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <string>
#include <sstream>
#include <cmath>


using namespace std;


Community::Community(Node* n,int net_nbOfEdges){
	// networknbOfEdges = net->getnbOfEdges();
	networknbOfEdges = net_nbOfEdges;
	community_id = n->getId();
	// nbOfEdgesOut = n->getDegree();
	// cout << nbOfEdgesOut << endl;
	// nbOfEdgesIn = 0;
}

Community::Community(Community* c){
	community_nodes = c -> getCommunityNodes();
	for (unsigned int i; i<community_nodes.size();i++){
		*community_nodes[i] = new Node(community_nodes[i]);
	}
	// int community_nodes_size = (c -> getCommunityNodes()).size();
	// for (unsigned int i; i<community_nodes_size;i++){
	// 	community_nodes.push_back(new Node(community_nodes[i]));
	// }
	nbOfEdgesIn = getnbOfEdgesIn();
	nbOfEdgesOut = getnbOfEdgesOut();
	com_modularity = getModularity();
	community_id = getCommunityId();
	networknbOfEdges = getNetworknbOfEdges();
}

Community::~Community(){
	;// 
}

void Community::setnbOfEdgesIO(){
	int _nbOfEdgesIn = 0;
	int _nbOfEdgesOut = 0;
	nbOfEdgesOut = 0;
	nbOfEdgesIn = 0;
	if(!isEmpty()){
		for(unsigned int i = 0; i<community_nodes.size();i++){
			// cout << "NODE ID: " << community_nodes[i]->getId() << ", CLASS ID: " << community_nodes[i]->getCommunityId() << endl;
			vector<Node *> com_node_neigh = community_nodes[i] -> getNeighbors();
			for(unsigned int j =0; j<com_node_neigh.size();j++){
				// cout << "Neigh ID: " << com_node_neigh[j]->getId() << ", Class ID: " << com_node_neigh[j]->getCommunityId() << endl;
				if (com_node_neigh[j]->getCommunityId() == community_id){
					_nbOfEdgesIn += 1;
				} else {
					_nbOfEdgesOut += 1;
				}
			}
		}
		// afficher classe noeuds voisins
		// cout << "nb in: " << nbOfEdgesIn << endl;
		// cout << "nb out: " << nbOfEdgesOut << endl;
		if(_nbOfEdgesIn % 2 != 0){
			int compteur = 0;
			int compteur2 = 0;
			cout << "COMM NODES:" << endl;
			for(unsigned int i = 0; i< community_nodes.size(); i++){
				cout << community_nodes[i]->getId() << ", ";
			}
			cout << endl;
			cout << "EDGES IN: " << _nbOfEdgesIn << ", EDGES OUT: " << _nbOfEdgesOut << ", COMM ID: " << community_id << endl;
			for(unsigned int i = 0; i<community_nodes.size();i++){
				cout << i << " - " << "NODE ID: " << community_nodes[i]->getId() << ", CLASS ID: " << community_nodes[i]->getCommunityId() << endl;
				vector<Node *> com_node_neigh = community_nodes[i] -> getNeighbors();
				for(unsigned int j =0; j<com_node_neigh.size();j++){
					cout << j << ". "  << "Neigh ID: " << com_node_neigh[j]->getId() << ", Class ID: " << com_node_neigh[j]->getCommunityId() << endl;
					if (com_node_neigh[j]->getCommunityId() == community_id){
						compteur += 1;
					} else {
						compteur2 +=1;
					}
				}
				cout << endl;
			}
			cout << "COMPTEUR IN: " << compteur << ", COMPTUER OUT: " << compteur2 << endl;
			cout << endl;
			cout << endl;
		}
		nbOfEdgesIn = _nbOfEdgesIn/2;
		nbOfEdgesOut = _nbOfEdgesOut;
	}
	// setModularity();
	// nbOfEdgesIn = 0;
	// nbOfEdgesOut = 0;
	// for(std::vector<int>::size_type i = 0; i != community_nodes.size(); i++) {
	// 	vector<Node*> com_node_neigh = community_nodes[i]-> getNeighbors();
	// 	for(vector<Node *>::iterator j=com_node_neigh.begin();j != com_node_neigh.end();j++){
	// 		if((*j)->getCommunityId() == community_id){
	// 			nbOfEdgesIn += 1;
	// 		} else {
	// 			nbOfEdgesOut += 1;
	// 		}
	// 	}
	// 	nbOfEdgesIn /= 2;
	// }
	// setModularity();
}

void Community::addNode(Node* n){
	// if (isEmpty()){
	community_nodes.push_back(n);
	n->setCommunityId(community_id);
	// 	nbOfEdgesOut = n->getDegree();
	// 	nbOfEdgesIn = 0;	
	// } else {
	// 	community_nodes.push_back(n);
	// 	n->setCommunityId(community_id);
	// 	vector<Node*> n_neighbors = n->getNeighbors();
	// 	for (unsigned int i = 0; i<n_neighbors.size();i++){
	// 		if (n->getCommunityId() == n_neighbors[i]->getCommunityId()){
	// 			nbOfEdgesIn += 1;
	// 			nbOfEdgesOut -= 1;
	// 		} else {
	// 			nbOfEdgesOut += 1;
	// 		}
	// 	}
	// }
	// setnbOfEdgesIO();
}

void Community::removeNode(Node* n){
	community_nodes.erase(std::find(community_nodes.begin(),community_nodes.end(),n));
	// if(isEmpty()){
	// 	nbOfEdgesIn = 0;
	// 	nbOfEdgesOut = 0;
	// } else {
	// 	vector<Node*> n_neighbors = n->getNeighbors();
	// 	for (unsigned int i=0; i<n_neighbors.size();i++){
	// 		if (old_com_id == n_neighbors[i]->getCommunityId()){
	// 			nbOfEdgesIn -= 1;
	// 			nbOfEdgesOut += 1;
	// 		} else {
	// 			nbOfEdgesOut -= 1;
	// 		}
	// 	}
	// }
   // setnbOfEdgesIO();
}


void Community::setModularity(){
	// cout << "Network nb of edges: " << networknbOfEdges << endl;
	// cout << "Com. id: " << community_id << " Edges in: " <<  nbOfEdgesIn << ", edges out: " << nbOfEdgesOut << ", networknbOfEdges: " << networknbOfEdges << endl;
	com_modularity = (double)nbOfEdgesIn/(double)networknbOfEdges - pow(((2*(double)nbOfEdgesIn+(double)nbOfEdgesOut)/(2*(double)networknbOfEdges)),2);
	// cout << "com mod: " << com_modularity << endl;
}

const vector<Node *> & Community::getCommunityNodes(){
	return community_nodes;
}

int Community::getNetworknbOfEdges(){
	return networknbOfEdges;
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
	setModularity();
	return com_modularity;
}

int Community::getNumberOfNodes(){
	return community_nodes.size();
}

bool Community::isEmpty(){
	bool isEmpty;
	if (getNumberOfNodes() == 0){
		isEmpty = true;
	} else {
		isEmpty = false;
	}
	return isEmpty;
}

