#include <stdlib.h>
#include "network.h"

using namespace std;


// Debugging tools
// void memory_test(Network* net, Network* best_partition){
// 	vector<Node *> net_nodes = net->getNodes();
// 	vector<Node *> best_nodes = best_partition->getNodes();
// 	if (&(*best_nodes[0])==&(*net_nodes[0])){
// 		cout << endl;
// 		cout << "Same memory address for nodes elements" << endl;
// 		cout << endl;
// 	} else {
// 		cout << endl;
// 		cout << "OK!" << endl; 
// 		cout << endl;
// 	}
// }

// Main program
int main (int argc, char **argv) {
	if (argc > 2){
		printf("Too many arguments: %i given, 1 needed (input file).\n", argc-1);
	} else if (argc == 1) {
		printf("Not enough arguments: %i given, 1 needed (input file). \n", argc-1);
	} else {
		char* filename = argv[1];
		
		Network* net = new Network(filename);

		net -> initCommunities();
		// net -> communityDivision();
		net -> LPAm();
		// net -> displayCommunities();
		// net -> communityDivision();
		// net -> displayNodesNeighbors();
		// net -> displayCommunities();
		net -> savePartition();
		
		cout << "Modularite: " << net->getTotalModularity() << endl;
		double best_modularity = net->getTotalModularity();
		
		int compteur = 0;
		int kmax = 15;
		int k=1;
		double cur_modularity;
		int pertubation;
		 
		while(compteur < 500){

			net -> loadSavedPartition();
			pertubation = rand() % 5;
			switch (pertubation) {
				case 0:
					net -> softRandomPertubation(k);
				  	break;
				case 1:
					net -> createSingletons();
					break;
				case 2:
					net -> communityMerge();
					break;
				case 3:
					net -> communityRedistribution();
					break;
				case 4:
					net -> communityDivision();
				  	break;
				default:
				  	break;
			}
			net->LPAm();

			cur_modularity = net -> getTotalModularity();

			if(cur_modularity - EPS > best_modularity) {
            	best_modularity = cur_modularity;
            	compteur = 0;
            	k=1;
            	cout << "Modularite: " << net->getTotalModularity() << endl;
            	net -> savePartition();
            	cout << endl;
            	// net -> displayCommunities();
        	} else {
        		k = k+1; 
        	}
        	if(k > kmax){
            	k = 1;
            	compteur ++;
            	// cout << compteur << endl;
        	}
        }
		net -> loadSavedPartition();
		
		// vector<int> saved_partition = net->getSavedPartition();

		vector<Node*> net_nodes = net->getNodes();
		cout << "From network_nodes: " << endl;
		for (unsigned int i=0; i<net_nodes.size(); i++){
			cout << net_nodes[i]->getCommunityId() << ", ";
		}
		cout << endl;
		// cout << "From saved_partition: " << endl;
		// for (unsigned int i=0; i<saved_partition.size(); i++){
		// 	cout << saved_partition[i] << ", ";
		// }

		// cout << endl;
		// cout << endl;
		// net -> savePartition();
		// net -> displayCommunities();
		// net -> displayCommunities();
		cout << "Modularite finale: " << net -> getTotalModularity() << endl;
		// net->displayCommunities();
        net -> writeSolution();
	}
}

