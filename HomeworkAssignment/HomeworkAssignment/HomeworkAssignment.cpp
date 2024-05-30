#pragma once
#include <iostream>
#include<fstream>
#include<vector>
#include"BFS.h"
#include"LCS.h"
#include"AStar.h"
using namespace std;
ifstream in("input.txt");
ofstream out("generatedInput.txt");
int noNodes;
vector<vector<nodeType>>nodesFromInput;
vector<vector<nodeTypee>>nodesFromInputLCS;
vector<vector<NodeType>>nodesFromInputA;
void generateInput()
{
	int numberOfWantedNodes, maxDistance;
	cout << "Input the number of wanted nodes: ";
	cin >> numberOfWantedNodes;
	cout << "Input the maximum distance possible between 2 cities: ";
	cin >> maxDistance;
	noNodes = numberOfWantedNodes;

	srand(time(0));
	nodesFromInput.resize(numberOfWantedNodes);
	nodesFromInputLCS.resize(numberOfWantedNodes);
	nodesFromInputA.resize(numberOfWantedNodes);
	for (int i = 0; i < numberOfWantedNodes - 1; i++)
		for (int j = i + 1; j < numberOfWantedNodes; j++)
		{

			int randomDistance = rand() % maxDistance + 1;
			nodesFromInput[i].push_back({ j,randomDistance });
			nodesFromInput[j].push_back({ i,randomDistance });

			nodesFromInputLCS[i].push_back({ j,randomDistance });
			nodesFromInputLCS[j].push_back({ i,randomDistance });

			nodesFromInputA[i].push_back({ j,randomDistance });
			nodesFromInputA[j].push_back({ i,randomDistance });
			out << i << " " << j << " " << randomDistance << '\n';

		}
}
void readInput()
{
	in >> noNodes;
	nodesFromInput.resize(noNodes);
    int node1, node2, distance;
	while(in >> node1 >> node2 >> distance)
	{
		nodesFromInput[node1].push_back({ node2,distance });
		nodesFromInput[node2].push_back({ node1,distance });

	}
}
int main()
{
	generateInput();
	bfs_approach(nodesFromInput, noNodes);
	cout << '\n';
	leastCostSearch_approach(nodesFromInputLCS, noNodes);
	cout << '\n';
	cout << aStarSearch(0, nodesFromInputA, noNodes);
//	bfs_approach(nodesFromInput,noNodes);

}

