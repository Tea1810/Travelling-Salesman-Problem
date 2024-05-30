#include "BFS.h"
#include<queue>

int mainNode;
int numberOfNodes;
int connections;
vector<vector<nodeType>>nodes;
vector<pair<int, vector<int>>>goodPaths;
void bfs(int node, map<int, bool>visited, vector<pair<int, int>>path)
{
    queue<nodeType>q;
	for (auto i : nodes[node])              
		q.push(i);
	visited[node] = true;
	while (q.empty() == false)
	{
		if (q.front().neighbour == mainNode && path.size() == numberOfNodes - 1)
		{
			long long sum = 0;
			vector<int>actualPath;
			for (auto i : path) {
				sum += i.second;
				actualPath.push_back(i.first);
			}
			actualPath.push_back(node);
			actualPath.push_back(mainNode);
			sum += q.front().distance;
			goodPaths.push_back(make_pair(sum, actualPath));
			return;
		}
		if (visited.find(q.front().neighbour) == visited.end())
		{
			path.push_back({ node, q.front().distance });
			bfs(q.front().neighbour, visited, path);
			path.erase(path.begin() + path.size() - 1);
		}
		q.pop();
	}

}
void bfs_approach(vector<vector<nodeType>>nodesFromInput,int number)
{
	nodes = nodesFromInput;
	numberOfNodes = number;
	for (int i = 0; i < numberOfNodes; i++)
	{
		map<int, bool>visited;
		vector< pair<int, int>>emptyPath;
		mainNode = i;
		bfs(i, visited, emptyPath);
	}
	sort(goodPaths.begin(), goodPaths.end());
	cout << "Best distances " << goodPaths[0].first << '\n';
	for (auto i : goodPaths[0].second)
		cout << i << " ";
}