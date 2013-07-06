#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "bbclass.h"


// These are used for sorting the lists
bool sortVPW (itemtuple a, itemtuple b) {
	return get<3>(a) > get<3>(b);
}
bool sortID (itemtuple a, itemtuple b) {
	return get<0>(a) < get<0>(b);
}


// BBSolver Class Functions
BBSolver::BBSolver(int capacity, int items) {
	this->capacity = capacity;
	this->items = items;
	this->itemlist.resize(items);
}


void BBSolver::displayItems() {
	cout << "Items: " << items << "  Capacity: " << capacity << endl;
	for (int i = 0; i < items; i++) {
		cout << "#" << get<0>(itemlist[i]) << ": Value=" << get<1>(itemlist[i]) << " Weight=" << get<2>(itemlist[i]) << " V/W=" << get<3>(itemlist[i]) << endl;
	}
}

void BBSolver::sortlistID() {
	sort(itemlist.begin(), itemlist.end(), sortID);
}

void BBSolver::sortlistVPW() {
	sort(itemlist.begin(), itemlist.end(), sortVPW);
}

int BBSolver::getEstimate(int item_num, int room) {
	int tempweight = 0;
	int estimate = 0;

	for (int i = item_num; i < items; i++) {
		if (tempweight+get<2>(itemlist[i]) < room) {
			estimate += get<1>(itemlist[i]);
			tempweight += get<2>(itemlist[i]);
		}
		else { //Get a fraction of the next item 
			double fraction = (double) (room - tempweight)/get<2>(itemlist[i]);
			estimate += fraction*get<1>(itemlist[i]);
			break;
		}
	}
	return estimate;

}

void BBSolver::run() {
	this->sortlistVPW();

	int estimate = getEstimate(0,capacity);

	//Construct root with item most V/W
	BBNode *root = new BBNode(get<0>(itemlist[0]), 0, capacity, estimate);
	cout << "First estimate: " << estimate << endl;

	branch(root, 0);

	// Now decide whether or not to take the item
	/* We need to use a separate function.. not a loop. It should create the whole tree 
	for (int i = 0; i < items; i++) {
		int cur_id, cur_value, cur_weight;
		cur_id = get<0>(itemlist[i]);
		cur_value = get<1>(itemlist[i]);
		cur_weight = get<2>(itemlist[i]);
		if (room-cur_weight < 0)
			;
	}
	*/
}

void BBSolver::branch(BBNode *node, int height) {
	itemtuple tuple = itemlist[height];

	// If there is room for the item, add a branch
	if (node->room - get<2>(tuple) > 0) {
		node->added = new BBNode(get<0>(tuple), node->value + get<1>(tuple), node->room - get<2>(tuple), node->estimate);
		branch(node->added, height+1);
	}

	// Add another branch for the item not being added. Need to get a new estimate.
	int newestimate;
	node->notadded = new BBNode(get<0>(tuple), node->value, node->room, newestimate);

}



// BBNode Class Functions
BBNode::BBNode(int itemid, int value, int room, int estimate) {
	this->itemid = itemid;
	this->value = value;
	this->room = room;
	this->estimate = estimate;
}
