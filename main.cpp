#include <iostream>
#include <chrono>

#include "graph.h"
#include " isomorphism.h"

void test(char *File_1 , char *File_2)
{
	Graph First(File_1);
	Graph Second(File_2);
	bool test;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	
	test = First.Isomorphic(Second);
	
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> result = end - start;
	
	if(test)
	{
		std::cout << "Izomorficzne\n";
		for(size_t i=0; i<First.v; i++)
			std::cout << i << " --> " << permutationTab[i] << "\n";
	} 
	else
		std::cout << "Nieizomorficzne\n"; 	
	 
	std::cout << "Czas: " << result.count() << "s\n";
}
 
int main(int argc, char **argv)
{ 
	if (argc == 3)
	{
		try {test(argv[1],argv[2]);}
		catch (...) {std::cout<<"Error of opening files\n";}
	}
	return 0;
}
