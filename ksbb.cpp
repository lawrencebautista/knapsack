/*	This program carries out the branch and bound algorithm to solve the knapsack problem.
*/

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include "bbclass.h"

using namespace std;

typedef tuple<int,int,int,double> itemtuple; //id, value, Weight, V/W


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

	BBSolver *solver = new BBSolver(capacity, items);

	// Read the items weights and values into an array. Use a vector of itemtuples
	for (int i = 0; i < items; i++) {
		int value, weight;
		if (data >> value >> weight)
			solver->itemlist[i] = make_tuple(i,value,weight, (double) value / (double) weight);
		else {
			cerr << "Error: not enough items in data file!" << endl;
			return -1;
		}
	}

	data.close();



	solver->sortlistVPW();
//	solver->displayItems();
	solver->run();


	delete solver;
	return 0;
}

