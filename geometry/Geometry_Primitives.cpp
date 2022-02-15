#include <bits/stdc++.h>
using namespace std;

const double EPS = (int)1e-9;
struct point {
    double x, y; 
    point() { x = y = 0.0; } 
    point(double _x, double _y) : x(_x), y(_y) {} 
    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); 
    }
    bool operator < (point other) const { // override less than operator
        if (fabs(x - other.x) > EPS) // useful for sorting
        return x < other.x; // first criteria , by x-coordinate
        return y < other.y; }
};
double dist(point p1, point p2) { 
    return hypot(p1.x - p2.x, p1.y - p2.y); 
}
double DEG_to_RAD(double theta){
    return theta*M_PI/180.0;
}
// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double theta) {
    double rad = DEG_to_RAD(theta); // multiply theta with PI / 180.0
    return point(p.x * cos(rad) - p.y * sin(rad),
    p.x * sin(rad) + p.y * cos(rad)); 
}
struct line { double a, b, c; }; // a way to represent a line
bool areParallel(line l1, line l2) { // check coefficients a & b
return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }
bool areSame(line l1, line l2) { // also check coefficient c
return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS); }
// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
if (areParallel(l1, l2)) return false; // no intersection
// solve system of 2 linear algebraic equations with 2 unknowns
p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
// special case: test for vertical line to avoid division by zero
if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
else p.y = -(l2.a * p.x + l2.c);
return true; 
}
struct vec { double x, y; // name: ‘vec’ is different from STL vector
vec(double _x, double _y) : x(_x), y(_y) {} };
vec toVec(point a, point b) { // convert 2 points to vector a->b
return vec(b.x - a.x, b.y - a.y); }
vec scale(vec v, double s) { // nonnegative s = [<1 .. 1 .. >1]
return vec(v.x * s, v.y * s); } // shorter.same.longer
point translate(point p, vec v) { // translate p according to v
return point(p.x + v.x , p.y + v.y); }

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }
double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }
// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b, point &c) {
// formula: c = a + u * ab
vec ap = toVec(a, p), ab = toVec(a, b);
double u = dot(ap, ab) / norm_sq(ab);
c = translate(a, scale(ab, u)); // translate a to c
return dist(p, c); }
// returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point a, point b, point &c) {
vec ap = toVec(a, p), ab = toVec(a, b);
double u = dot(ap, ab) / norm_sq(ab);
if (u < 0.0) { c = point(a.x, a.y); // closer to a
return dist(p, a); } // Euclidean distance between p and a
if (u > 1.0) { c = point(b.x, b.y); // closer to b
return dist(p, b); } // Euclidean distance between p and b
return distToLine(p, a, b, c); }

double angle(point a, point o, point b) { // returns angle aob in rad
vec oa = toVec(o, a), ob = toVec(o, b);
return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }
double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }
// note: to accept collinear points, we have to change the ‘> 0’
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
return cross(toVec(p, q), toVec(p, r)) > 0; }
// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }


double perimeter(const vector<point> &P) {
double result = 0.0;
for (int i = 0; i < (int)P.size()-1; i++) // remember that P[0] = P[n-1]
result += dist(P[i], P[i+1]);
return result; }


double area(const vector<point> &P) {
double result = 0.0, x1, y1, x2, y2;
for (int i = 0; i < (int)P.size()-1; i++) {
x1 = P[i].x; x2 = P[i+1].x;
y1 = P[i].y; y2 = P[i+1].y;
result += (x1 * y2 - x2 * y1);
}
return fabs(result) / 2.0; }


bool isConvex(const vector<point> &P) { // returns true if all three
int sz = (int)P.size(); // consecutive vertices of P form the same turns
if (sz <= 3) return false; // a point/sz=2 or a line/sz=3 is not convex
bool isLeft = ccw(P[0], P[1], P[2]); // remember one result
for (int i = 1; i < sz-1; i++) // then compare with the others
if (ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft)
return false; // different sign -> this polygon is concave
return true; }


// returns true if point p is in either convex/concave polygon P
bool inPolygon(point pt, const vector<point> &P) {
if ((int)P.size() == 0) return false;
double sum = 0; // assume the first vertex is equal to the last vertex
for (int i = 0; i < (int)P.size()-1; i++) {
if (ccw(pt, P[i], P[i+1]))
sum += angle(P[i], pt, P[i+1]); // left turn/ccw
else sum -= angle(P[i], pt, P[i+1]); } // right turn/cw
return fabs(fabs(sum) - 2*M_PI) < EPS; }


// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q, point A, point B) {
double a = B.y - A.y;
double b = A.x - B.x;
double c = B.x * A.y - A.x * B.y;
double u = fabs(a * p.x + b * p.y + c);
double v = fabs(a * q.x + b * q.y + c);
return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v)); }
// cuts polygon Q along the line formed by point a -> point b
// (note: the last point must be the same as the first point)
vector<point> cutPolygon(point a, point b, const vector<point> &Q) {
    vector<point> P;
    for (int i = 0; i < (int)Q.size(); i++) {
        double left1 = cross(toVec(a, b), toVec(a, Q[i])), left2 = 0;
        if (i != (int)Q.size()-1) left2 = cross(toVec(a, b), toVec(a, Q[i+1]));
        if (left1 > -EPS) P.push_back(Q[i]); // Q[i] is on the left of ab
        if (left1 * left2 < -EPS) // edge (Q[i], Q[i+1]) crosses line ab
        P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
    }
    if (!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front()); // make P’s first point = P’s last point
return P; 
}



int main()
{
    point P1(0, 0), P2(0, 0), P3(0, 1);
    printf("%d\n", P1 == P2); // true
    printf("%d\n", P1 == P3);
    return 0;
}

