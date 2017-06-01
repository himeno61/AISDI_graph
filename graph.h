#ifndef GRAFY_GRAPH_H
#define GRAFY_GRAPH_H
 
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
 
int *permutationTab = nullptr;
 
bool checkOrder(int a, int b)
{
	return permutationTab[a] < permutationTab[b];
}
class Graph
{

public: 
	std::vector<int> * vertexes;
	int e,v;
	

	Graph(char *File_in):e(0),v(0)
	{
		std::ifstream file (File_in);
		if (file.is_open())
		{
			file >> v;
			vertexes = new std::vector<int>[v];
			int a,b;
			while (file >> a >> b)
			{
				vertexes[a].push_back(b);
				if( a != b )
					vertexes[b].push_back(a);
				++e;
			}
				file.close();
		}
		else
			throw "unable to open a file";
	}
	
	~Graph()
	{
		delete []vertexes;
		delete [] permutationTab;
	}

private:
bool checkPermutation(Graph &Second)
{

	for(size_t i=0; i<v; i++)
	{
		if(vertexes[i].size() != Second.vertexes[permutationTab[i]].size())
			return false;

	std::sort(vertexes[i].begin(), vertexes[i].end(), checkOrder);

	for(size_t j=0; j<vertexes[i].size(); j++)
		if( permutationTab[ vertexes[i][j] ] != Second.vertexes[permutationTab[i]][j] )
			return false; 
	}
	return true; 
}

	bool checkDegs(Graph &Second)
	{
		int degsFirst[v];
		int degsSecond[Second.v];

		for(size_t i=0; i<v; i++)
		{
			degsFirst[i] = vertexes[i].size();
			degsSecond[i] = Second.vertexes[i].size();
		}
		std::sort(degsFirst, degsFirst+v);
		std::sort(degsSecond, degsSecond+Second.v);

		for(size_t i=0; i<v; i++)
			if(degsFirst[i] != degsSecond[i])
				return false;
		return true;
	}
	
public:
	bool Isomorphic(Graph &Second)
	{
		if (v != Second.v || e != Second.e)
			return false;

		permutationTab = new int[v];
		for(size_t i=0; i<v; i++)
			permutationTab[i] = i; 

		for(size_t i=0; i<Second.v; i++)
			std::sort(Second.vertexes[i].begin(), Second.vertexes[i].end());

		if(!checkDegs(Second))
			return false;

		do
		{
			if(checkPermutation(Second))
				return true; 
		}while(std::next_permutation(permutationTab, permutationTab+v));

		return false; 
	}



};
#endif //GRAFY_GRAPH_H
