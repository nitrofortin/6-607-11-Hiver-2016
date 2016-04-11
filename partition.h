#ifndef PARTITION_H
#define PARTITION_H

// #include "node.h"
#include "community.h"

using namespace std;

class Partition {
public:
	void setPartitionNodes();
	void setPartitionModularity();
	void getPartitionNodes();
	void getPartitionModularity();
	
private:
	vector<Node *> partitionNodes;
	double partitionModularity;
};

#endif // PARTITION_H