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
	// ifstream input;
	fname = filename;
	ifstream file(filename);
	int line;
	file >> line;

	while (!file.eof()){
		nbOfEdges++;
		int origine, destination, weight;
		file >> origine >> destination >> weight;
		// cout << "origine: " << origine << ", destination: " << destination << ", weight: " << weight << endl; 
		if(find(visited_nodes.begin(), visited_nodes.end(), origine-1) != visited_nodes.end()) {
			;
		} else {
			visited_nodes.push_back(origine-1);
		}
		if(find(visited_nodes.begin(), visited_nodes.end(), destination-1) != visited_nodes.end()) {
			;
		} else {
			visited_nodes.push_back(destination-1);
		}
	}
	nbOfEdges -= 1;

	setNetworkNodes();
	file.close();
	setNetworkLinks();
	// doubleCheck();
	sort(visited_nodes.begin(),visited_nodes.end(),simpleSort);
}

// Network::Network(Network *net){
// 	network_nodes_copy = net -> getNodes();
// 	for(vector<int>::size_type i = 0; i != network_nodes_copy.size(); i++) {
// 		network_nodes.push_back(network_nodes_copy[i]->clone());
// 	}
// 	network_communities_copy = net -> getCommunities();
// 	for(vector<int>::size_type i = 0; i != network_communities_copy.size(); i++) {
// 		network_communities.push_back(network_communities_copy[i]->clone());
// 	}
// }

// void Network::copy(Network *net){
// 	network_nodes = net -> getNodes();
// 	network_communities = net -> getCommunities();
// }


void Network::setNetworkNodes(){
	for(std::vector<int>::size_type i = 0; i != visited_nodes.size(); i++) {
		stringstream node_id; 
		node_id << i;
		network_nodes.push_back(new Node(node_id.str(),i));
	}
}

void Network::setNetworkLinks(){
	ifstream file(fname);
	int temp = 9999;
	int temp2 = 9999;
	int line;
	file >> line;
	while (!file.eof()){
		int origine, destination, weight;
		file >> origine >> destination >> weight;
		// cout << "origine: " << origine << ", destination: " << destination << ", weight: " << weight << endl;
		if (origine == temp && destination == temp2){
			;
		} else {
			network_nodes[origine-1] -> addNeighbor(network_nodes[destination-1]);
			network_nodes[destination-1] -> addNeighbor(network_nodes[origine-1]);
			// cout << "origine: " << origine << ", destination: " << destination << endl;		
		}
		temp = origine;
		temp2 = destination;
	}
	file.close();
}

void Network::doubleCheck(){
	for(unsigned int i = 0; i<network_nodes.size();i++){
		vector<Node*> les_voisins = network_nodes[i]->getNeighbors();
		int vois_id = 999;
		for(unsigned int j = 0; j<les_voisins.size();j++){
			if(les_voisins[j]->getId() == vois_id){
				les_voisins.erase(remove(les_voisins.begin(), les_voisins.end(), les_voisins[j]), les_voisins.end());
			}
			vois_id = les_voisins[j]->getId();
		}
	}
}

void Network::dummyTransformation(){
	int com_idd = network_nodes[0]->getCommunityId();
	cout << "com_iddd: " << com_idd << endl;
	modifyNodeCommunity(network_nodes[0],20);
	// modifyNodeCommunity(network_nodes[0],com_idd);
}

void Network::initCommunities(){
	for(vector<int>::size_type i = 0; i != network_nodes.size(); i++) {
		int node_id = network_nodes[i]->getId();
	    network_communities.push_back(new Community(network_nodes[i],nbOfEdges));
	    network_communities[i] -> addNode(network_nodes[i]);
	}
	for(vector<int>::size_type i = 0; i != network_nodes.size(); i++) {
		network_communities[i] -> setnbOfEdgesIO();
	}
}

void Network::modifyNodeCommunity(Node* n, int com_id){
	int node_com_id = n->getCommunityId();
	if (node_com_id != com_id){
		for(vector<int>::size_type i = 0; i != network_communities.size(); i++){
			if ((network_communities[i]->getCommunityId())== node_com_id){
				network_communities[i]->removeNode(n);
			} else if ((network_communities[i]->getCommunityId())==com_id){
				network_communities[i] -> addNode(n);
				// vector<Node*> comm_nodes = network_communities[i]->get
				// for (unsigned int j =0; j<)
			}
		}
		for(unsigned int i = 0; i<network_communities.size();i++){
			network_communities[i]->setnbOfEdgesIO();
			network_communities[i]->setModularity();
		}
	}
}

void Network::localSearch(){
	double best_mod, cur_mod;
	cur_mod = getTotalModularity();
	best_mod = cur_mod;
	bool improved = true;
	int actual_com_id;
	int dummy;
	while(improved){
		improved = false;
		for(unsigned int i=0; i<network_nodes.size();i++){
			actual_com_id = network_nodes[i]->getCommunityId();
			// cout << "actual_com_id: " << actual_com_id << endl;
			vector<Node *> actual_neighbors = network_nodes[i]->getNeighbors();
			dummy = 0;
			// cout << "Node: " << network_nodes[i]->getId() << endl;
			for(unsigned int j=0; j<actual_neighbors.size();j++){
				// flagTransmission(actual_neighbors[j],network_nodes[i]);
				int tmp_id = actual_neighbors[j]->getCommunityId();
				if (actual_com_id != tmp_id){
					modifyNodeCommunity(actual_neighbors[j],actual_com_id);
					cur_mod = getTotalModularity();
					if (cur_mod - EPS > best_mod){
						improved = true;
						best_mod = cur_mod;
						// cout << dummy++ << endl;
						// cout << "neigh_com_id: " << tmp_id << ", node_com_id: " << actual_com_id << ", node i: " << i << ", neigh j: " << actual_neighbors[j]->getId() << endl;
						// cout << "Modularite: " << cur_mod << endl;
					} else {
						modifyNodeCommunity(actual_neighbors[j],tmp_id);
					}
				}

			}
		}	
	}
	// cout << getTotalModularity() << endl;
}

// void Network::LPA(){
// 	bool improved = true;
// 	int actual_com_id;
// 	int k = 0;
// 	int count;
// 	int limit;
// 	double cur_mod = getTotalModularity();
// 	double best_mod = cur_mod;
// 	while(k<10){
// 		// improved = false;
// 		int best_frequence;
// 		int more_frequent_comm_id;
// 		for(unsigned int i=0; i<network_nodes.size();i++){
// 			vector<Node *> actual_neighbors = network_nodes[i]->getNeighbors();
// 			more_frequent_comm_id = actual_neighbors[rand() % actual_neighbors.size()] -> getCommunityId();
// 			vector<int> com_ids;
// 			for(unsigned int j=0; j<actual_neighbors.size();j++){
// 				com_ids.push_back(actual_neighbors[j]->getCommunityId());
// 			}
// 			// cout << "Node " << network_nodes[i]->getId() << endl;
// 			int node_degre = network_nodes[i] -> getDegree();
// 			sort(com_ids.begin(),com_ids.end(),simpleSort);
// 			best_frequence = 1;
// 			// cout << endl;
// 			// cout << "Node id: " << network_nodes[i]->getId() << ", com id: " << network_nodes[i] -> getCommunityId() << endl;
// 			// for (unsigned int j=0; j<com_ids.size();j++){
// 			// 	cout << com_ids[j] << ", ";
// 			// }
// 			// cout << endl;
// 			for(int j = 0; j < com_ids.size(); j++){
// 				count = 1;
// 				limit = com_ids.size() - 1;
// 				int k = j;
// 			    while(j < limit  && com_ids[k] == com_ids[k+1]){
// 			    	count++;
// 			    	k++;
// 			    }
// 			    if (count > best_frequence){
// 			    	best_frequence = count;
// 			    	more_frequent_comm_id = com_ids[k];
// 			    }

// 			}
// 			// cout << "best freq: " << best_frequence << endl;
// 			// cout << "more frequent com id: " << more_frequent_comm_id << endl;
// 			// cout << endl;

// 			modifyNodeCommunity(network_nodes[i],more_frequent_comm_id);
// 			// cur_mod = getTotalModularity();
// 			// if (cur_mod > best_mod + EPS){
// 			// 	improved = true;
// 			// 	best_mod = cur_mod;
// 			// }
// 			k++;
// 		}	
// 	}
// }

void Network::LPA(){
	int k=0;
	bool improved = true;
	double cur_mod;
	double best_mod = cur_mod;
	while(improved){
		improved = false;
		cur_mod = getTotalModularity();
		int new_com_id;
		for(unsigned int i=0; i<network_nodes.size();i++){
			vector<Node *> actual_neighbors = network_nodes[i] -> getNeighbors();
			vector<double> AijDelta;
			vector<int> mostPopularCom;
			// cout << "node: " << network_nodes[i]->getId() << endl;
			for(unsigned int j=0; j<network_communities.size(); j++){
				AijDelta.push_back(0);
			}
			for(unsigned int j=0; j<actual_neighbors.size(); j++){
				AijDelta[actual_neighbors[j]->getCommunityId()] += 1;
			}
			for(unsigned int j=0; j<AijDelta.size(); j++){
				// cout << AijDelta[j] << ", ";
				if (!mostPopularCom.empty()) {
					if (AijDelta[j] > AijDelta[mostPopularCom[0]]){
						mostPopularCom.erase(mostPopularCom.begin(),mostPopularCom.end());
						mostPopularCom.push_back(j);
					} else if (AijDelta[j] == AijDelta[mostPopularCom[0]] ) {
						mostPopularCom.push_back(j);
					} 
				} else {
					mostPopularCom.push_back(j);
				}
			}	
			new_com_id = mostPopularCom[rand() % mostPopularCom.size()];
			modifyNodeCommunity(network_nodes[i],new_com_id);
			cur_mod = getTotalModularity();
			if (cur_mod > best_mod + EPS){
				improved = true;
				best_mod = cur_mod;
			} else {
				modifyNodeCommunity(network_nodes[i],new_com_id);
			}
			// k++;
			// cout << "itteratoa: " << k << endl;
		}	
	}
}

void Network::LPAm(){
	int k=0;
	bool improved = true;
	double cur_mod;
	double best_mod = cur_mod;
	while(improved){
		improved = false;
		cur_mod = getTotalModularity();
		int new_com_id;
		int com_frequence_among_neighbors;
		for(unsigned int i=0; i<network_nodes.size();i++){
			vector<Node *> actual_neighbors = network_nodes[i] -> getNeighbors();
			vector<double> PijDelta;
			vector<int> mostPopularCom;
			vector<Node *> comm_nodes;
			int actual_node_degree = network_nodes[i]->getDegree();
			int neigh_node_degree;
			// cout << "node: " << network_nodes[i]->getId() << endl;
			for(unsigned int j=0; j<network_communities.size(); j++){
				PijDelta.push_back(0);
			}
			for(unsigned int j=0; j<actual_neighbors.size(); j++){
				PijDelta[actual_neighbors[j]->getCommunityId()] += 1;
			}
			for(unsigned int j=0; j<PijDelta.size();j++){
				com_frequence_among_neighbors = PijDelta[j];
				comm_nodes = network_communities[j]->getCommunityNodes();
				for(unsigned int k=0; k<comm_nodes.size(); k++){
					neigh_node_degree = comm_nodes[k]-> getDegree();
					PijDelta[j] -= (actual_node_degree*neigh_node_degree)/(2*nbOfEdges);
				}
			}

			for(unsigned int j=0; j<PijDelta.size(); j++){
				// cout << AijDelta[j] << ", ";
				if (!mostPopularCom.empty()) {
					if (PijDelta[j] > PijDelta[mostPopularCom[0]]){
						mostPopularCom.erase(mostPopularCom.begin(),mostPopularCom.end());
						mostPopularCom.push_back(j);
					} else if (PijDelta[j] == PijDelta[mostPopularCom[0]] ) {
						mostPopularCom.push_back(j);
					} 
				} else {
					mostPopularCom.push_back(j);
				}
			}	
			new_com_id = mostPopularCom[rand() % mostPopularCom.size()];
			modifyNodeCommunity(network_nodes[i],new_com_id);
			cur_mod = getTotalModularity();
			if (cur_mod > best_mod + EPS){
				improved = true;
				best_mod = cur_mod;
			} else {
				modifyNodeCommunity(network_nodes[i],new_com_id);
			}
			k++;
			// cout << "itteratoa: " << k << endl;
		}	
	}
}

void Network::hardRandomPertubation(int k){
	int random_com_id;
	for (unsigned int i=0; i<k; i++){
		random_com_id = randomNodeId();
		random_node = network_nodes[randomNodeId()];
		if (random_com_id != random_node->getCommunityId() & network_communities[random_com_id]->getNumberOfNodes() != 0){
			modifyNodeCommunity(random_node,random_com_id);
		}
	}
}

void Network::softRandomPertubation(int k){
	int random_com_id;
	for (unsigned int i=0; i<k; i++){
		random_com_id = randomNodeId();
		random_node = network_nodes[randomNodeId()];
		if (random_com_id != random_node->getCommunityId()){
			modifyNodeCommunity(random_node,random_com_id);
		}
	}
}

void Network::communityMerge(){
	bool different = true;
	int random_com_id_1;
	int random_com_id_2;
	vector<Community *> nonempty_communities = getNonEmptyCommunities();
	while(different){
		random_com_id_1 = rand() % nonempty_communities.size();
		random_com_id_2 = rand() % nonempty_communities.size();
		if(random_com_id_1 != random_com_id_2){
			different = false;
		}
	}
	vector<Node *> com_nodes = nonempty_communities[random_com_id_1]->getCommunityNodes();
	for(unsigned int i = 0; i<com_nodes.size(); i++){
		modifyNodeCommunity(com_nodes[i], nonempty_communities[random_com_id_2]->getCommunityId());
	}
}

void Network::communityDivision(){
	bool different = true;
	int random_com_id_1;
	int random_com_id_2;
	int reassigned;
	vector<Community *> nonempty_communities = getNonEmptyCommunities();
	Community* community_to_divide = nonempty_communities[rand() % nonempty_communities.size()];
	vector<Community *> empty_communities = getEmptyCommunities();
	// cout << "empty comm size: " << empty_communities.size() << endl;
	if(empty_communities.size()>0 && empty_communities.size()<network_communities.size()){
		while(different){
			random_com_id_1 = rand() % nonempty_communities.size();
			random_com_id_2 = rand() % empty_communities.size();
			if(random_com_id_1 != random_com_id_2){
				different = false;
			}
		}
		// cout << "rand 1: " << nonempty_communities[random_com_id_1]->getCommunityId() << endl;
		// cout << "rand 2: " << empty_communities[random_com_id_2]->getCommunityId() << endl;
		vector<Node *> com_nodes = nonempty_communities[random_com_id_1]->getCommunityNodes();
		for(unsigned int i = 0; i<com_nodes.size(); i++){
			reassigned = rand() % 2;
			if(reassigned){
				modifyNodeCommunity(com_nodes[i], empty_communities[random_com_id_2]->getCommunityId());
			}
		}
	} else {
		;
	}
}

void Network::communityRedistribution(){
	vector<Community *> nonempty_communities = getNonEmptyCommunities();
	vector<Node *> com_nodes = nonempty_communities[rand() % nonempty_communities.size()]->getCommunityNodes();
	for (unsigned int i = 0; i<com_nodes.size();i++){
		vector<Node *> com_nodes_neigh = com_nodes[i]->getNeighbors();
		modifyNodeCommunity(com_nodes[i],com_nodes_neigh[rand() % com_nodes_neigh.size()]->getCommunityId());
	}
}

void Network::createSingletons(){
	vector<Community *> nonempty_communities = getNonEmptyCommunities();
	vector<Node*> random_community_nodes = nonempty_communities[rand() % nonempty_communities.size()]->getCommunityNodes();
	vector<Community *> empty_communities = getEmptyCommunities();
	for(unsigned int i = 0; i<random_community_nodes.size();i++){
		modifyNodeCommunity(random_community_nodes[i],empty_communities[i]->getCommunityId());
	}
}

void Network::savePartition(){
	int com_id;
	if (saved_partition.size() != 0){
		// saved_partition.erase(saved_partition.begin(),saved_partition.end());
		saved_partition.clear();
	}
	// cout << saved_partition.size() << endl;
	cout << "From network_nodes: " << endl;
	for(unsigned int i = 0; i<network_nodes.size(); i++){
		com_id = network_nodes[i] -> getCommunityId();
		saved_partition.push_back(com_id);
		cout << com_id << ", ";
	}
	cout << endl;

	// cout << "From saved_partition: " << endl;
	// for(unsigned int i = 0; i<saved_partition.size(); i++){
	// 	cout << saved_partition[i] << ", ";
	// }
	// cout << endl;
	// cout << "From communites: " << endl;
	// for (unsigned int i = 0; i<network_nodes.size();i++){
	// 	bool ended = false;
	// 	while(!ended){
	// 		for(unsigned j = 0; j<network_communities.size();j++){
	// 			if (network_communities[j]-> getCommunityId() == network_nodes[i]->getCommunityId()){
	// 				ended = true;
	// 				cout << network_communities[j]-> getCommunityId() << ", ";
	// 			}
	// 		}
	// 	}
	// }
	// cout << endl;
	// cout << endl;
	// cout << saved_partition.size() << endl;
	// cout << "taille de saved_partition: " << saved_partition.size() << cout; 
}

void Network::loadSavedPartition(){
	for (unsigned int i=0; i<saved_partition.size(); i++){
		// cout << saved_partition[i] << ", ";
		modifyNodeCommunity(network_nodes[i],saved_partition[i]);
	}
	// cout << endl;	
}

vector<int> Network::getSavedPartition(){
	return saved_partition;
}

void Network::displayVisitedNodes(){
	for(vector<int>::size_type i = 0; i != visited_nodes.size(); i++) {
	    cout << visited_nodes[i] << endl;
	}
}

void Network::writeSolution(){
	ofstream myfile;
	myfile.open ("partition.txt");
	myfile << "{";
	// cout << "{";
	for(unsigned int i = 0; i<network_nodes.size(); i++){
		myfile << network_nodes[i]->getId() + 1 << ":" << network_nodes[i]->getCommunityId();
		// cout << network_nodes[i]->getId() + 1 << ":" << network_nodes[i]->getCommunityId();
		if (i == network_nodes.size()-1) {
			myfile << "}";
			// cout << "}";
		} else {
			myfile << ",";
			// cout << ",";
		}
	}
	myfile.close();
	system("python test_display.py");
}

void Network::displayNodesNeighbors(){
	for(std::vector<int>::size_type i = 0; i != visited_nodes.size(); i++) {
		network_nodes[i]->displayNeighbors();
	}
}

vector<Node*> Network::getNodes(){
	return network_nodes;
}

int Network::getNumberOfCommunties(){
	int nb_of_comm = 0;
	for (unsigned int i = 0; i<network_communities.size(); i++){
		if(!network_communities[i]->isEmpty()){
			nb_of_comm += 1;
		}
	}
	return nb_of_comm;
}

void Network::displayCommunities(){
	for (unsigned int i = 0; i<network_communities.size();i++){
		cout << "Community: " << network_communities[i] -> getCommunityId() << endl;
		vector<Node *> sup = network_communities[i]->getCommunityNodes();
		for (unsigned int j = 0; j< sup.size();j++){
			cout << sup[j] -> getId() << ", ";
		}
		cout << endl;
		// cout << "Comm. modularity: " << network_communities[i]->getModularity() << endl;
		// cout << "Edges IN: " << network_communities[i] -> getnbOfEdgesIn() << endl;
		// cout << "Edges OUT: " << network_communities[i] -> getnbOfEdgesOut() << endl;
		// cout << endl;
	}	
}

double Network::getTotalModularity(){
	totalModularity = 0;
	for(vector<int>::size_type i = 0; i != network_communities.size(); i++) {
		totalModularity += (network_communities[i] -> getModularity());
	}
	return totalModularity;
}

int Network::getnbOfEdges(){
	return nbOfEdges;
}

vector<Community *> Network::getCommunities(){
	return network_communities;
}

vector<Community*> Network::getEmptyCommunities(){
	vector<Community*> empty_communities;
	for(unsigned int i = 0; i<network_communities.size();i++){
		if (network_communities[i]->isEmpty()){
			empty_communities.push_back(network_communities[i]);
			// cout << network_communities[i] -> getCommunityId() << endl;
		}
	}
	return empty_communities;
}

vector<Community*> Network::getNonEmptyCommunities(){
	vector<Community*> nonempty_communities;
	for(unsigned int i = 0; i<network_communities.size();i++){
		if (!(network_communities[i]->isEmpty())){
			nonempty_communities.push_back(network_communities[i]);
		}
	}	
	return nonempty_communities;
}

void Network::flagTransmission(Node* transmitter,Node* receiver){
	int trans_com_id = transmitter->getCommunityId();
	modifyNodeCommunity(receiver, trans_com_id);
}

int Network::randomNodeId()
{
    return rand() % network_nodes.size();
}

int Network::randomCommunityId()
{
    return rand() % network_communities.size();
}

