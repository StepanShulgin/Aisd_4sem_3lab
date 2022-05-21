#include "List.h"
#include "the_Floyd-Warshell_algorithm.h"
#include <iostream>

using namespace std;

int main() 
{
	
	Floyd_Warshell test;
	test.read();
	test.mainAlgorithm();
	cout << "The way from St. Petersburg to Khabarovsk: " << endl;
	cout << "The lowest price: " << test.getBestCost("St. Petersburg", "Khabarovsk") << endl;
	cout << "Path: " << test.getBestPath("St. Petersburg", "Khabarovsk") << endl;
	cout << "The way from St. Petersburg to Astrakhan: " << endl;
	cout << "Path: " << test.getBestPath("St. Petersburg", "Astrakhan") << endl;

	cout << "Adjacency matrix: " << endl;
	test.getMatrix();
	
	return 0;
}
