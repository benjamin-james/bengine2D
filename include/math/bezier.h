#ifndef BEZIER_H
#define BEZIER_H

#include "physics/types.h"
/* Defines bezier spline, for rounding polygons */

struct spline {
	double *xx, *yy, *a, *b, *c, *d;
	int last, length;
};

struct spline_shape {
	struct spline x, y;
	struct point centroid;
	float radius;
	double length;
};

struct spline_shape *spline_from_polygon(struct polygon *p);
void create_spline(struct spline *s, double *x, double *y, int len);
#endif
