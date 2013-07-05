using namespace std;

/* DPSolver: Class that uses a dynamic programming algorithm to solve the knapsack problem.
   It needs: capacity, item number, value of all items, weight of all items,
   It stores these as: int, int, int[], int[]
   It creates a dynamic programming matrix using dynamic memory and is handled using an int** 
*/

class DPSolver {
	int **matrix;
	int capacity, items;
	int *value, *weight;
	public:
		DPSolver(int, int, int*, int*);
		~DPSolver();
		void displayItems();
		void printMatrix();
		int fillMatrix(); // Returns the final value
		int* traceback(int *); // returns an array of 0's and 1's which are interpreted as the item in the bag or not.
};
