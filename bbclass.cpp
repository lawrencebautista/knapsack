#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "bbclass.h"
#include <string>

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
	this->bestvalue = 0;
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
	BBNode *root = new BBNode(get<0>(itemlist[0]), 0, capacity, estimate, false);

	branch(root, 0);
	//cout << "Result: " << bestvalue << endl;


	this->sortlistID();


	// Print the formatted output
	cout << bestvalue << " 1" << endl;
	for (int i = 0; i < items; i++) {
		if (bestnode->itemsadded[i])
			cout << "1 ";
		else
			cout << "0 ";
	}
	cout << endl;

}

void BBSolver::branch(BBNode *node, int height) {
	itemtuple tuple = itemlist[height];
	
	int next_item;
	if (height < items)
		next_item = get<0>(itemlist[height+1]);
	else
		next_item = -1;
	
//	cout << "Node: Item #" << height << " Value=" << node->value << " Room=" << node->room << " Estimate=" << node->estimate << endl;

	// If this is a leaf node and it has a better value than the best one, replace the bestvalue variable and point to this node
	if (height == items) {
		if (node->value > bestvalue) {
			bestvalue = node->value;
			BBNode *tempnode = bestnode;
			bestnode = node;
			delete tempnode;

			// Also record the path to this node.
			BBNode *cur_node = node;
			node->itemsadded.resize(items);
			for (int i = 0; i < items; i++) {
				itemtuple tuple = itemlist[items-1-i];
				if (cur_node->parent_added) 
					node->itemsadded[get<0>(tuple)] = true;
				else
					node->itemsadded[get<0>(tuple)] = false;
				cur_node = cur_node->parent;
			}
		}
		else
			delete node;
		return;
	}

	// If the estimate is worse than the best value, then don't do anything more with this branch.
	if (node->estimate < bestvalue) {
		delete node;
		return;
	}

	// If there is room for the item, add a branch
	if (node->room - get<2>(tuple) > 0) {
		node->added = new BBNode(next_item, node->value + get<1>(tuple), node->room - get<2>(tuple), node->estimate, true);
		node->added->parent = node;
		branch(node->added, height+1);
	}

	// Add another branch for the item not being added. Need to get a new estimate.
	int newestimate;
	newestimate = node->value + getEstimate(height+1,node->room);
	node->notadded = new BBNode(get<0>(tuple), node->value, node->room, newestimate, false);
	node->notadded->parent = node;
	branch(node->notadded, height+1);

	// Finally delete the node when we are done
	delete node;
}



// BBNode Class Functions
BBNode::BBNode(int itemid, int value, int room, int estimate, bool parent_added) {
	this->itemid = itemid;
	this->value = value;
	this->room = room;
	this->estimate = estimate;
	this->parent_added = parent_added;
}
