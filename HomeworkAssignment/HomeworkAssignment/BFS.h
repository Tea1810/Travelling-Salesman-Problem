#pragma once
#include <iostream>
#include<map>
#include<vector>
using namespace std;
struct nodeType {
	int neighbour;
	int distance;
};
void bfs(int node, map<int, bool>visited, vector<pair<int, int>>path);
void bfs_approach(vector<vector<nodeType>>nodesFromInput, int number);
