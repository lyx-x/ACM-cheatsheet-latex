/* Compute the 2D convex hull of a set of points using the monotone chain
 * algorithm. Eliminate redundant points from the hull if REMOVE_REDUNDANT 
 * is #defined.
 *
 * Running time: O(n log n)
 *
 * INPUT: a vector of input points, unordered.
 * OUTPUT: a vector of points in the convex hull, counterclockwise, 
 *			starting with bottommost/leftmost point */

#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define REMOVE_REDUNDANT

const double EPS = 1e-7;

struct point_t { 
	double x, y; 
	point_t() {} 
	point_t(double x, double y) : x(x), y(y) {}
	bool operator< (const point_t &rhs) const { 
		return make_pair(y, x) < make_pair(rhs.y, rhs.x); 
	}
	bool operator== (const point_t &rhs) const { 
		return make_pair(y, x) == make_pair(rhs.y, rhs.x); 
	}
};

double cross(point_t p, point_t q) { return p.x * q.y - p.y * q.x; }
double area2(point_t a, point_t b, point_t c) { 
	return cross(a, b) + cross(b, c) + cross(c, a); 
}

#ifdef REMOVE_REDUNDANT
bool between(const point_t &a, const point_t &b, const point_t &c) {
	return (fabs(area2(a, b, c)) < EPS && (a.x - b.x) * (c.x - b.x) <= 0 
			&& (a.y - b.y) * (c.y - b.y) <= 0);
}
#endif

void convex_hull(vector<point_t> &pts) {
	sort(pts.begin(), pts.end());
	pts.erase(unique(pts.begin(), pts.end()), pts.end());
	vector<point_t> up, dn;
	for (int i = 0; i < pts.size(); i++) {
		while (up.size() > 1 && 
				area2(up[up.size() - 2], up.back(), pts[i]) >= 0) 
			up.pop_back();
		while (dn.size() > 1 && 
				area2(dn[dn.size() - 2], dn.back(), pts[i]) <= 0) 
			dn.pop_back();
		up.push_back(pts[i]);
		dn.push_back(pts[i]);
	}
	pts = dn;
	for (int i = (int)up.size() - 2; i >= 1; i--) 
		pts.push_back(up[i]);
	
#ifdef REMOVE_REDUNDANT
	if (pts.size() <= 2) return;
	dn.clear();
	dn.push_back(pts[0]);
	dn.push_back(pts[1]);
	for (int i = 2; i < pts.size(); i++) {
		if (between(dn[dn.size() - 2], dn[dn.size()-1], pts[i])) 
			dn.pop_back();
		dn.push_back(pts[i]);
	}
	if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
		dn[0] = dn.back();
		dn.pop_back();
	}
	pts = dn;
#endif
}