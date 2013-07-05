#include <iostream>
#include <ctime>
#include "dpclass.h"
#define TIME_LIMIT 10

using namespace std;

DPSolver::DPSolver(int capacity, int items, int* value, int *weight) {
	this->capacity = capacity;
	this->items = items;
	this->value = value;
	this->weight = weight;

	// Initialize the matrix
	// Remember we want it a (capacity+1) x (items+1) matrix
	matrix = new int*[capacity+1];
	
	for (int i = 0; i < capacity+1; i++ ) {
		matrix[i] = new int[items+1];
	}

	// Edit: NOT NECESSARY. Should be removed to save runtime later on.
	//Fill it with 0's
	for (int i = 0; i < capacity+1; i++ ) {
		for (int j = 0; j < items+1; j++ ) {
			matrix[i][j] = 0;
		}
	}
}

// Deallocate the matrix
DPSolver::~DPSolver() {
	for (int i = 0; i < capacity+1; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

void DPSolver::displayItems() {
	cout << "Items: " << items << "  Capacity: " << capacity << endl;
	for (int i = 0; i <= items; i++) {
		cout << "#" << i << ": Value=" << value[i] << " Weight=" << weight[i] << endl;
	}
}

void DPSolver::printMatrix() {
	for (int i = 0; i < capacity+1; i++) {
		for (int j = 0; j < items+1; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int DPSolver::fillMatrix() {
	/* Carry out the following algorithm:
	int O(int k, int j) {
		if (j = 0)
			return 0;
		else if (wj <= k )
			return max(O(k,j-1),vj + O(k-wj,j-1);
		else
			return O(k,j-1)
	}*/

	// We want to set a time limit for this too.
	time_t start, end, timer;

	time(&start);
	time(&end);
	timer = difftime(end,start);
	int last_time = timer;
	
	int currentitem = 0;
	while (currentitem < items+1) {
		for (int i = 0; i < capacity+1; i++) {
			// Check every 1000 iterations if we've passed the timer
			if (i !=0 && 10000%i == 0) {
				time(&end);
				timer = difftime(end,start);
				if (timer > last_time) {
					cout << "Timer: " << timer << endl;
					last_time = timer;
				}

				if (timer > TIME_LIMIT) {
					return -1;
					cout << "Error: Could not finish in time!" << endl;
				}
			}

			if (currentitem == 0)
				matrix[i][currentitem] = 0;
			else if (weight[currentitem] <= i) {
				int first = matrix[i][currentitem-1];
				int second = value[currentitem] + matrix[i-weight[currentitem]][currentitem-1];
			
				if (first > second)
					matrix[i][currentitem] = first;
				else
					matrix[i][currentitem] = second;
			}
			else
				matrix[i][currentitem] = matrix[i][currentitem-1];	
		}
	currentitem++;
	}
	return matrix[capacity][items];
}

int * DPSolver::traceback(int *itemlist) {
	int currentvalue = matrix[capacity][items];
	int currentitem = items; // The current item is the last one
	int currentweight = capacity;
	while (currentitem != 0) {
		if (currentvalue == matrix[currentweight][currentitem-1]) {
			itemlist[currentitem] = 0; // This item wasn't added
			currentitem--;
			// No need to update currentvalue since it's the same.
		}
		else if (currentvalue == value[currentitem] + matrix[currentweight - weight[currentitem]][currentitem-1]) {
			itemlist[currentitem] = 1; // This item was added
			currentweight -= weight[currentitem];
			currentitem--;
			currentvalue = matrix[currentweight][currentitem]; // Update the currentvalue
		}
		else if (currentvalue == 0) {
			itemlist[currentitem] = 0;
			currentitem--;;
		}
		else {
			cout << "Error: The DP matrix does not make sense!" << " Value=" << currentvalue << " Item=" << currentitem << " Weight=" << currentweight << endl;
			break;
		}
	}
	return itemlist;
}
