#ifndef TYPES_H
#define TYPES_H

struct point {
	double x,y;
};
struct line {
	struct point a,b;
};
struct circle {
	struct point center;
	float radius;
};
struct polygon {
	int num;
	struct point centroid;
	struct point *pts;
	struct point *normals;
	float radius;
};
#endif
