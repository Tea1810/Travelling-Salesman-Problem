#pragma once
#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
struct nodeTypee {
	int neighbour;
	int distance;
};
bool comp(const nodeTypee& a, const nodeTypee& b);
void dfs(int node, map<int, bool>visited, vector<pair<int, int>>path);
void leastCostSearch_approach(vector<vector<nodeTypee>>nodesFromInput, int number);

