#include "physics/types.h"
#include "physics/polygon.h"
#include "math/common.h"

#include "stdbool.h"
#include "float.h" /* FLT_EPSILON */

static void get_centroid(struct polygon *p)
{
	struct point c = {0.0, 0.0};
	float area = 0.0;
	struct point tot = {0.0, 0.0};
	int i;
	const float inv3 = 1.f/3;
	if (p->num < 3)
		return;
	for (i = 0; i < p->num; i++) {
		tot.x += p->pts[i].x;
		tot.y += p->pts[i].y;
	}
	tot.x /= p->num;
	tot.y /= p->num;
	for (i = 0; i < p->num; i++) {
		struct point tmp[3];
		struct point e1,e2;
		float tmp_area = 0.F;
		tmp[0] = tot;
		tmp[1] = p->pts[i];
		tmp[2] = i + 1 < p->num ? p->pts[i+1] : p->pts[0];
		e1 = {tmp[2].x - tmp[1].x, tmp[2].y - tmp[1].y};
		e2 = {tmp[3].x - tmp[1].x, tmp[3].y - tmp[1].y};
		tmp_area = 0.5F * e1.x * e2.y - e1.y * e2.x;
		area += tmp_area;
		c.x += tmp_area * inv3 * (tmp[0].x + tmp[1].x + tmp[2].x);
		c.y += tmp_area * inv3 * (tmp[0].y + tmp[1].y + tmp[2].y);
	}
	if (area <= FLT_EPSILON)
		return;
	c.x /= area;
	c.y /= area;
	p->centroid = c;
}
struct polygon polygon_create(int num_pts, struct point *pts)
{
	struct polygon p;
	int i;
	double d;
	p.num = num_pts;
	p.pts = malloc(num_pts * sizeof(struct point));
	memcpy(p.pts, pts, num_pts * sizof(struct point));
	p.normals = malloc(num_pts * sizeof(struct point));
	get_centroid(&p);
	for (i = 0, d = DOUBLE_MAX; i < num_pts; i++) {
		if (distance2(p->pts[i], p->centroid) < d) {
			d = distance(p->pts[i], p->centroid);
			p->radius = (float)d;
		}
	}
}
void polygon_destroy(struct polygon *p)
{
	free(p.pts);
	free(p.normals);
}
bool poly_poly_guess(struct polygon *a, struct polygon *b)
{
	if (!a || !b)
		return 0;
	return distance2(a->centroid, b->centroid) <= (a->radius + b->radius) * (a->radius + b->radius);
}
bool poly_poly(struct polygon *a, struct polygon *b)
{
	return poly_poly_guess(a,b);
}
