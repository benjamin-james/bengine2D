#include "physics/types.h"
#include "math/common.h"
#include "math.h"

double distance2(struct point a, struct point b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}
double distance(struct point a, struct point b)
{
	return sqrt(distance2(a,b));
}
