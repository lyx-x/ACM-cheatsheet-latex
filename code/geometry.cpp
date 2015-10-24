// C++ routines for computational geometry.

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

double INF = 1e100;
double EPS = 1e-12;

struct point_t { 
	double x, y; 
	point_t() {}
	point_t(double x, double y) : x(x), y(y) {}
	point_t(const point_t &p) : x(p.x), y(p.y) {}
	point_t operator + (const point_t &p) const { 
		return point_t(x + p.x, y + p.y); 
	}
	point_t operator - (const point_t &p) const { 
		return point_t(x - p.x, y - p.y); }
	point_t operator * (double c) const { return point_t(x * c, y * c); }
	point_t operator / (double c) const { return point_t(x / c, y / c); }
};

double dot(point_t p, point_t q) { return p.x * q.x + p.y * q.y; }
double dist2(point_t p, point_t q) { return dot(p - q, p - q); }
double cross(point_t p, point_t q) { return p.x * q.y - p.y * q.x; }
ostream &operator<< (ostream &os, const point_t &p) {
	os << "(" << p.x << "," << p.y << ")"; 
}

// rotate a point CCW or CW around the origin, t in radians
point_t RotateCCW90(point_t p { return point_t(-p.y, p.x); }
point_t RotateCW90(point_t p) { return point_t(p.y, -p.x); }
point_t RotateCCW(point_t p, double t) { 
	return point_t(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)); 
}

// project point c onto line through a and b
// assuming a != b
point_t ProjectPointLine(point_t a, point_t b, point_t c) {
	return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a);
}

// project point c onto line segment through a and b
point_t ProjectPointSegment(point_t a, point_t b, point_t c) {
	double r = dot(b - a, b - a);
	if (fabs(r) < EPS) return a;
	r = dot(c - a, b - a) / r;
	if (r < 0) return a;
	if (r > 1) return b;
	return a + (b - a) * r;
}

// compute distance from c to segment between a and b
double DistancePointSegment(point_t a, point_t b, point_t c) {
	return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// compute distance between point (x, y, z) and plane ax + by + cz = d
double DistancePointPlane(double x, double y, double z,
		double a, double b, double c, double d) {
	return fabs(a * x + b * y + c * z - d) / sqrt(a * a + b * b + c * c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(point_t a, point_t b, point_t c, point_t d) { 
	return fabs(cross(b - a, c - d)) < EPS; 
}

bool LinesCollinear(point_t a, point_t b, point_t c, point_t d) { 
	return LinesParallel(a, b, c, d)
			&& fabs(cross(a - b, a - c)) < EPS
			&& fabs(cross(c - d, c - a)) < EPS; 
}

// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(point_t a, point_t b, point_t c, point_t d) {
	if (LinesCollinear(a, b, c, d)) {
		if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
			dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
		if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
			return false;
		return true;
	}
	if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
	if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
	return true;
}

// compute intersection of line passing through a and b with line passing
// through c and d, assuming that unique intersection exists; for segment 
// ntersection, check if segments intersect first
point_t ComputeLineIntersection(point_t a, point_t b, point_t c, point_t d) {
	b = b - a; d = c - d; c = c - a;
	assert(dot(b, b) > EPS && dot(d, d) > EPS);
	return a + b * cross(c, d) / cross(b, d);
}

// compute center of circle given three points
point_t ComputeCircleCenter(point_t a, point_t b, point_t c) {
	b = (a + b) / 2;
	c = (a + c) / 2;
	return ComputeLineIntersection(b, b + RotateCW90(a - b), c, 
		c + RotateCW90(a - c));
}

// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<point_t> &p, point_t q) {
	bool c = 0;
	for (int i = 0; i < p.size(); i++){
		int j = (i+1)%p.size();
		if ((p[i].y <= q.y && q.y < p[j].y || 
				p[j].y <= q.y && q.y < p[i].y) &&
				q.x < p[i].x + (p[j].x - p[i].x) 
				* (q.y - p[i].y) / (p[j].y - p[i].y)) 
			c = !c;
	}
	return c;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<point_t> &p, point_t q) {
	for (int i = 0; i < p.size(); i++)
		if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
			return true;
		return false;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<point_t> CircleLineIntersection(point_t a, point_t b, point_t c, 
		double r) {
	vector<point_t> ret;
	b = b - a;
	a = a - c;
	double A = dot(b, b);
	double B = dot(a, b);
	double C = dot(a, a) - r * r;
	double D = B * B - A * C;
	if (D < -EPS) return ret;
	ret.push_back(c + a + b * (-B + sqrt(D + EPS)) / A);
	if (D > EPS)
		ret.push_back(c + a + b * (-B - sqrt(D)) / A);
	return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<point_t> CircleCircleIntersection(point_t a, point_t b, 
		double r, double R) {
	vector<point_t> ret;
	double d = sqrt(dist2(a, b));
	if (d > r + R || d + min(r, R) < max(r, R)) return ret;
	double x = (d * d - R * R + r * r) / (2 * d);
	double y = sqrt(r * r - x * x);
	point_t v = (b - a) / d;
	ret.push_back(a + v * x + RotateCCW90(v) * y);
	if (y > 0)
		ret.push_back(a + v * x - RotateCCW90(v) * y);
	return ret;
}

// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion. Note that the centroid is often known as
// the "center of gravity" or "center of mass".
double ComputeSignedArea(const vector<point_t> &p) {
	double area = 0;
	for(int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		area += p[i].x * p[j].y - p[j].x * p[i].y;
	}
	return area / 2.0;
}

double ComputeArea(const vector<point_t> &p) {
	return fabs(ComputeSignedArea(p));
}

point_t ComputeCentroid(const vector<point_t> &p) {
	point_t c(0, 0);
	double scale = 6.0 * ComputeSignedArea(p);
	for (int i = 0; i < p.size(); i++){
		int j = (i + 1) % p.size();
		c = c + (p[i] + p[j]) * (p[i].x * p[j].y - p[j].x * p[i].y);
	}
	return c / scale;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<point_t> &p) {
	for (int i = 0; i < p.size(); i++) {
		for (int k = i+1; k < p.size(); k++) {
			int j = (i+1) % p.size();
			int l = (k+1) % p.size();
			if (i == l || j == k) continue;
			if (SegmentsIntersect(p[i], p[j], p[k], p[l])) 
				return false;
		}
	}
	return true;
}