#ifndef DISJOINT_SET_H_
#define DISJOINT_SET_H_

#include <iostream>
#include <vector>

using namespace std;


//Disjoint Set class using Array
class DisjointSet {
public:

	// Constructor
	DisjointSet(int size) : arr(size, -1) {}
	int size() {return arr.size();}
	void print() {
		for(int i = 0; i < arr.size(); i++) {
			cout << i << ": " << arr[i] << endl;
		}
	}

	// Find using path compression
	int find(int x) {
		if (arr[x] < 0) return x;
		else return arr[x] = find(arr[x]);
	}

	// Union by size
	void unionSet(int root1, int root2) {
		int x = find(root1);
		int y = find(root2);
		if(x != y) {
			if(arr[x] < arr[y]) {
				arr[x] += arr[y];
				arr[y] = x;
			}
			else {
				arr[y] += arr[x];
				arr[x] = y;
			}
		}
	}
private:
	vector <int> arr;
};



#endif