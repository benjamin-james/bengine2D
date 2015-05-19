#ifndef POLYGON_H
#define POLYGON_H

#include "physics/types.h"
#include "stdbool.h"

struct polygon *polygon_create(int num_pts, struct point *pts);
void polygon_destroy(struct polygon *p);
bool poly_poly_guess(struct polygon *a, struct polygon *b);
bool poly_poly(struct polygon *a, struct polygon *b);

void pt_convert_to_polar(struct point pole, struct point *pt);

#endif
