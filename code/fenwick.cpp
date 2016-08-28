#include <iostream>
using namespace std;

#define LOGSZ 17

int tree[(1 << LOGSZ) + 1]; // BIT array
int N = (1 << LOGSZ);
//tree start with index 1
// add v to value at x, update BIT array
void set(int x, int v) {
	while(x <= N) {
		tree[x] += v;
		x += (x & -x); // rightmost bit of 1
	}
}

// get cumulative sum up to and including x
int get(int x) {
	int res = 0;
	while(x) {
		res += tree[x];
		x -= (x & -x);
	}
	return res;
}

// get largest value with cumulative sum less than or equal to x;
// for smallest, pass x - 1 and add 1 to result
int getind(int x) {
	int idx = 0, mask = N;
	while(mask && idx < N) {
		int t = idx + mask;
		if(x >= tree[t]) {
			idx = t;
			x -= tree[t];
		}
		mask >>= 1;
	}
	return idx;
}
