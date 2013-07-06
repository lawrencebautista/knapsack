#include <vector>
#include <tuple>

using namespace std;

typedef tuple<int,int,int,double> itemtuple;


class BBNode {
public:
	int itemid;
	int value;
	int room;
	int estimate;
	BBNode *added, *notadded; 
	BBNode *parent;
	BBNode(int, int, int, int); // Item ID, Value, Room, Estimate
};


class BBSolver {
	int capacity;
	int items;
	int bestvalue;
	BBNode *bestnode;

public:
	vector<itemtuple> itemlist;

	BBSolver(int, int);
	void displayItems();
	void sortlistID();
	void sortlistVPW();
	int getEstimate(int, int);
	void run();
	void branch(BBNode *, int);
	
};


