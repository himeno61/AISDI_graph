#include <iostream>
#include "graph.h"
#include <chrono>

 
int *permutationTab = nullptr;

void createPermutationTab(int v)
{
    permutationTab = new int[v];
    for(int i=0; i<v; i++)
        permutationTab[i]=i;
 
}
 
bool checkDegs(Graph &FirstGraph,Graph &SecondGraph)
{
    int degsFirstGraph[FirstGraph.v];
    int degsSecondGraph[SecondGraph.v];
 
    for(int i=0; i<FirstGraph.v; i++)
    {
        degsFirstGraph[i] = FirstGraph.vertexes[i].size();
        degsSecondGraph[i] = SecondGraph.vertexes[i].size();
    }
    std::sort(degsFirstGraph, degsFirstGraph+FirstGraph.v); /// Range of Tabs sort(first,last)
    std::sort(degsSecondGraph, degsSecondGraph+SecondGraph.v);
 
    for(int i=0; i<FirstGraph.v; i++)
        if(degsFirstGraph[i] != degsSecondGraph[i])  /// checking degrees of vertex
            return false;
 
    return true;
}
 
bool checkOrder(int a, int b)
{
    return permutationTab[a] < permutationTab[b];
}
 
bool checkPermutation(Graph &FirstGraph,Graph &SecondGraph)
{
 
    for(size_t i=0; i<FirstGraph.v; i++)
    {
        if(FirstGraph.vertexes[i].size() != SecondGraph.vertexes[permutationTab[i]].size())
            return false;
 
        std::sort(FirstGraph.vertexes[i].begin(), FirstGraph.vertexes[i].end(), checkOrder);
        /// Sorting each record of Graph by permutationTabOrder
 
        for(size_t j=0; j<FirstGraph.vertexes[i].size(); j++)
            if( permutationTab[ FirstGraph.vertexes[i][j] ] != SecondGraph.vertexes[permutationTab[i]][j] )
                return false; 
    }
    return true; 
}
 
bool Isomorphic(Graph &FirstGraph,Graph &SecondGraph)
{
    if (FirstGraph.v != SecondGraph.v || FirstGraph.e != SecondGraph.e)
        return false;
 
    createPermutationTab(FirstGraph.v);
 
    for(int i=0; i<SecondGraph.v; i++)
        std::sort(SecondGraph.vertexes[i].begin(), SecondGraph.vertexes[i].end());
 
    if(!checkDegs(FirstGraph,SecondGraph))
       return false;
 
    do
    {
		if(checkPermutation(FirstGraph,SecondGraph))
			return true; 
    }while(std::next_permutation(permutationTab,permutationTab+FirstGraph.v));
 
	return false; 
}

void test(char *File_1 , char *File_2)
{
	Graph First(File_1);
    Graph Second(File_2);
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
	
	if(Isomorphic(First, Second))
    {
        std::cout << "Izomorficzne\n";
        for(size_t i=0; i<First.v; i++)
            std::cout << i << " --> " << permutationTab[i] << "\n";
    } 
    else
        std::cout << "Nieizomorficzne\n"; 
    delete [] permutationTab;
	 
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> result = end-start;
    std::cout << "Czas: " << result.count() << "s\n";
}
 
int main(int argc, char **argv)
{ 
    if (argc != 3)
        return 0;
	test(argv[1],argv[2]);
    return 0;
}
