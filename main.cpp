#include <stdlib.h>
#include "network.h"

using namespace std;

void partitionProposition(){

}

bool partitionEvaluation(double temperature){
	srand (time(NULL));
	double Q = getTotalModularity();
	double transProb;
	if (newQ > Q){
		return 1;
	}
	if (temperature == 0.0) {
		return 0;
	}
	transProb = exp(-(Q-newQ)/temperature);
	return ((rand()%100 + 1)/100.0) < transProb;
}

void partitionAcception(){
	;
}

void optimizeModularity(Network copy, Network original){
	double T = 1.0;
	while(T>0.01){
		partitionProposition();
		if(partitionEvaluation(T)){
			partitionAcception();
		}
		T = T - 0.0001;
	}
}

int main (int argc, char **argv) {
	if (argc > 2){
		printf("Too many arguments: %i given, 1 needed (input file).\n", argc-1);
	} else if (argc == 1) {
		printf("Not enough arguments: %i given, 1 needed (input file). \n", argc-1);
	} else {
		char* filename = argv[1];
		Network net(filename);
		// net.displayVisitedNodes();
		net.displayNodesNeighbors();
		net.initCommunities();
		cout << net.getTotalModularity() << endl;
		// copy!
		// Network net_copy(net);
		// net_copy.displayNodesNeighbors();
		net.optimizeModularity();
	}
}