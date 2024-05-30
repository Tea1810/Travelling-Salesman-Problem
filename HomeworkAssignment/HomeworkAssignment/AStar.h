#pragma once
#include"BFS.h"
struct NodeType {
	int neighbour;
	int distance;
};
int kruskals_mst(vector<vector<int>> edgelist);
int smallestDistance(int nod, map<int, bool>& visited, int startNode);
int aStarSearch(int startNode, vector<vector<NodeType>>nodesFromInput, int number);

