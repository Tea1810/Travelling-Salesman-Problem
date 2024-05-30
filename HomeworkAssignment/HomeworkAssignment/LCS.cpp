#include "LCS.h"
#include<algorithm>
int currentNode;
int nrNode;
vector<vector<nodeTypee>>newNodes;
vector<pair<int, vector<int>>>LCSgoodPaths;
bool comp(const nodeTypee& a, const nodeTypee& b)
{
	return a.distance < b.distance;
}
void dfs(int node, map<int, bool>visited, vector<pair<int, int>>path)
{
	visited[node] = true;
	for (auto i : newNodes[node])
	{
		if (i.neighbour == currentNode && path.size() == nrNode - 1)
		{
			long long sum = 0;
			vector<int>actualPath;
			for (auto i : path) {
				sum += i.second;
				actualPath.push_back(i.first);
			}
			actualPath.push_back(node);
			actualPath.push_back(currentNode);
			sum += i.distance;
			LCSgoodPaths.push_back(make_pair(sum, actualPath));
			return;
		}
		if (visited.find(i.neighbour) == visited.end())
		{
			path.push_back({ node, i.distance });
			dfs(i.neighbour, visited, path);
			path.erase(path.begin() + path.size() - 1);
		}
	}
}
void leastCostSearch_approach(vector<vector<nodeTypee>>nodesFromInput, int number) {
	newNodes = nodesFromInput;
	nrNode = number;
	for (auto& i : newNodes)
	{
		sort(i.begin(), i.end(), comp);
	}
	for (int i = 0; i < nrNode; i++)
	{
		map<int, bool>visited;
		vector< pair<int, int>>emptyPath;
		currentNode = i;
		dfs(i, visited, emptyPath);
	}
	sort(LCSgoodPaths.begin(), LCSgoodPaths.end());
	cout << "Best distances " << LCSgoodPaths[0].first << '\n';
	for (auto i : LCSgoodPaths[0].second)
		cout << i << " ";
}