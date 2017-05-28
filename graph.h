#ifndef GRAFY_GRAPH_H
#define GRAFY_GRAPH_H
 
#include <fstream>
#include <vector>
#include <algorithm>
 
class Graph
{
public: 
	std::vector<int> * vertexes;
    int e;
    int v;
    
    Graph(char *NameOfFile)
	{
		v = e = 0;
 
		file.open(NameOfFile, std::ios::in);
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
    ~Graph()
    {
		delete []vertexes;
	}
    
 
private:
    std::fstream file;
    char *NameOfFile;
};
#endif //GRAFY_GRAPH_H
