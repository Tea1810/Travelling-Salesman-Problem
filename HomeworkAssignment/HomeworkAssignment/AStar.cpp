#include "AStar.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<map>
#include<queue>
using namespace std;
int NumberOfNodes;
vector<vector<NodeType>>AstarNodes;
class DSU {
	int* parent;
	int* rank;

public:
	DSU(int n)
	{
		parent = new int[n];
		rank = new int[n];

		for (int i = 0; i < n; i++) {
			parent[i] = -1;
			rank[i] = 1;
		}
	}
	int find(int i)
	{
		if (parent[i] == -1)
			return i;

		return parent[i] = find(parent[i]);
	}
	void unite(int x, int y)
	{
		int s1 = find(x);
		int s2 = find(y);

		if (s1 != s2) {
			if (rank[s1] < rank[s2]) {
				parent[s1] = s2;
			}
			else if (rank[s1] > rank[s2]) {
				parent[s2] = s1;
			}
			else {
				parent[s2] = s1;
				rank[s1] += 1;
			}
		}
	}
};
int kruskals_mst(vector<vector<int>> edgelist)            //find the minimum spanning tree between the unvisited cities
{
	sort(edgelist.begin(), edgelist.end());
	DSU s(NumberOfNodes);
	int ans = 0;
	for (auto edge : edgelist) {
		int w = edge[0];
		int x = edge[1];
		int y = edge[2];
		if (s.find(x) != s.find(y)) {
			s.unite(x, y);
			ans += w;
		}
	}
	return ans;
}

struct node {
	int nodeNumber;
	int parent;
	int g;
	int f;
	int h;
	vector<int>path;
	map<int, bool>visited;
	bool operator>(const node& other)const {
		return f > other.f;
	}
	int heuristic()                                               // find all the possible paths between the unvisited cities
	{
		map<pair<int, int>, bool> existingPair;
		vector<vector<int>> edgelist;
		for (auto i = 0; i < NumberOfNodes; i++)
			if (visited.find(i) == visited.end())
			{
				for (auto j : AstarNodes[i])
				{
					if (existingPair.find(make_pair(j.neighbour, i)) == existingPair.end() &&
						existingPair.find(make_pair(i, j.neighbour)) == existingPair.end() && visited.find(j.neighbour) == visited.end())
					{
						edgelist.push_back({ j.distance,j.neighbour,i });
						existingPair[{j.distance, i}] = true;
					}
				}
			}
		return kruskals_mst(edgelist);

	}
	bool search(int x)
	{
		return visited.find(x) == visited.end();
	}
};
void showPath(node nod)
{
	for (auto j : nod.path)
		cout << j << " ";
	cout << 0 << '\n';
}
int smallestDistance(int nod, map<int, bool>& visited, int startNode) {
	int minDistance1 = INT_MAX;
	int minDistance2 = INT_MAX;
	int minDistance3 = INT_MAX;
	int minDistance4 = INT_MAX;
	int node1;
	int node2;
	if (visited.size() == NumberOfNodes)           
	{
		for (auto j : AstarNodes[startNode])
			if (j.neighbour != nod)
				minDistance1 = min(minDistance1, j.distance);
		return minDistance1;
	}
	if (visited.size() == NumberOfNodes - 1)
	{
		for (auto j : AstarNodes[nod])
			if (visited.find(j.neighbour) == visited.end())
			{
				minDistance1 = j.distance;
				break;
			}
		for (auto j : AstarNodes[startNode])
			if (visited.find(j.neighbour) == visited.end())
			{
				minDistance2 = j.distance;
				break;
			}
		return minDistance1 + minDistance2;
	}

	for (auto j : AstarNodes[nod])
		if (visited.find(j.neighbour) == visited.end()) {
			if (j.distance < minDistance1)
			{
				minDistance2 = minDistance1;
				minDistance1 = j.distance;
				node1 = j.neighbour;
			}
			else
				if (j.distance < minDistance2)
				{
					minDistance2 = j.distance;
				}
		}

	for (auto j : AstarNodes[startNode])
		if (visited.find(j.neighbour) == visited.end()) {
			if (j.distance < minDistance3)
			{
				minDistance4 = minDistance3;
				minDistance3 = j.distance;
				node2 = j.neighbour;
			}
			else
				if (j.distance < minDistance4)
				{
					minDistance4 = j.distance;
				}
		}
	minDistance2 = (minDistance2 == INT_MAX) ? 0 : minDistance2;
	minDistance4 = (minDistance4 == INT_MAX) ? 0 : minDistance4;
	return (node1 == node2) ? min(minDistance1 + minDistance4, minDistance2 + minDistance3) : minDistance1 + minDistance3;
}     //find the distance from the MST to the current path
int aStarSearch(int startNode, vector<vector<NodeType>>nodesFromInput, int number)
{
	AstarNodes = nodesFromInput;
	NumberOfNodes = number;

	map<int, bool>visited;
	visited[startNode] = true;
	vector<int>path;
	path.push_back(startNode);
	priority_queue<node, vector<node>, greater<node>> pq;

	node firstNode = { startNode,-1,0,0,0,path,visited };

	pq.push(firstNode);

	while (!pq.empty())                                        //while no complete road was found, search all possible roads
	{
		firstNode = pq.top();
		pq.pop();
		for (auto i : AstarNodes[firstNode.nodeNumber])       //check all possible routesfrom the current city to another 
		{
			if (firstNode.search(i.neighbour)) {              //if the city hasn't been visited 
				node newNode;
				newNode.parent = firstNode.nodeNumber;        
				newNode.nodeNumber = i.neighbour;
				newNode.path = firstNode.path;                //update the current path wih the new city
				newNode.path.push_back(i.neighbour);
				newNode.g = firstNode.g + i.distance;         //add distance from the current city to the newCity
				newNode.visited = firstNode.visited;          //mark the new city as visited
				newNode.visited[i.neighbour] = true;
				newNode.h = newNode.heuristic() + smallestDistance(i.neighbour, newNode.visited, startNode);
				newNode.f = newNode.g + newNode.h;
				if (newNode.visited.size() == NumberOfNodes) {
					showPath(newNode);
					return newNode.f;
				}
				pq.push(newNode);
			}
		}
	}

}

