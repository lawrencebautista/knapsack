/*	This program carries out the dynamic programming algorithm to solve the knapsack problem.
*/

#include <iostream>
#include <fstream>
#include "dpclass.h"

using namespace std;



/* MAIN PROGRAM START 123 */
int main(int argc, char *argv[]) {
	
	// Get the data file and store the capacity and number of items
	ifstream data;
	if (argc >= 2) {
		data.open(argv[1]);
	}
	else {
		cout << "Error: needs an argument" << endl;
		return 1;
	}
	
	int items, capacity;
	data >> items >> capacity;

	// Read the items weights and values into an array.
	// Make the array size n+1 because we want weight[1] = first item
	int *weight = new int[items+1];
	int *value = new int[items+1];
	weight[0] = 0;
	value[0] = 0;
	int i = 1;
	while (data >> value[i] >> weight[i]) {
	//	cout << "Writing from file:   Value=" << value[i] << "  Weight=" << weight[i] << endl;
		i++;
	}
	data.close();


	DPSolver *solver = new DPSolver(capacity, items, value, weight);

	int totalValue = solver->fillMatrix();
	
	if (totalValue == -1) {
		cout << "Program terminating" << endl;
		return 0;
	}

	int *itemlist = new int[items+1];
	itemlist = solver->traceback(itemlist);
	cout << totalValue << " 1" << endl;

	// Print the item list
	for (int j = 1; j < items+1; j++) {
		cout << itemlist[j] << " ";
	}
	cout << endl;


	delete [] itemlist;
	delete [] weight;
	delete [] value;
	delete solver;
	return 0;
}

