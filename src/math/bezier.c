#include "math/bezier.h"
#include "physics/types.h"

#include "math.h"

struct spline_shape *spline_from_polygon(struct polygon *p)
{
	struct spline_shape *ss = malloc(sizeof(struct spline_shape));
	double *t = malloc(sizeof(double) * p->num);
	double *x = malloc(sizeof(double) * p->num);
	double *y = malloc(sizeof(double) * p->num);
	int i;
	double lx, ly;
       	t[0] = 0.0;
	ss->length = 0.0;
	ss->centroid = p->centroid;
	x[0] = p->pts[0].x * cos(p->pts[0].y);
	y[0] = p->pts[0].x * sin(p->pts[0].y);
	for (i = 1; i < p->num; i++) {
		x[i] = p->pts[i].x * cos(p->pts[i].y);
		y[i] = p->pts[i].y * sin(p->pts[i].y);
		lx = x[i] - x[i-1];
		ly = y[i] - y[i-1];
		if (lx == 0.0)
			t[i] = abs(ly);
		else if (ly == 0.0)
			t[i] = abs(lx);
		else
			t[i] = sqrt(lx*lx+ly*ly);
		ss->length += t[i];
		t[i] += t[i-1];
	}
	for (i = 1; i < p->num - 1; i++)
		t[i] /= ss->length;
	t[p->num - 1] = 1;
	create_spline(&ss->x, t, x, p->num);
	create_spline(&ss->y, t, y, p->num);
	free(t);
	free(x);
	free(y);
	return ss;
}
static void solve(double *a, double *b, int n)
{
	int i;
	for (i = 1; i < n; i++) {
		a[i * n + i-1] /= a[(i-1) * n + i-1];
		a[i * n + i] = a[i * n + i] - a[(i-1) * n + i] * a[i * n + i-1];
		b[i] = b[i] - a[i * n + i - 1] * b[i - 1];
	}
	b[n-1] /= a[(n-1) * n + n - 1];
	for (i = n - 2; i >= 0; i--)
		b[i] = (b[i] - a[i * n + i + 1] * b[i + 1]) / a[i * n + i];
}
void create_spline(struct spline *s, double *pxx, double *pyy, int num)
{
	int i;
	double *h = malloc(sizeof(double) * (num-1));
	double *a = malloc(sizeof(double) * (num-2) * (num-2));
	double *y = malloc(sizeof(double) * (num-2));
	s->length = num;
	s->xx = pxx;
	s->yy = pyy;
	s->a = malloc(sizeof(double) * num);
	s->b = malloc(sizeof(double) * num);
	s->c = malloc(sizeof(double) * num);
	s->d = malloc(sizeof(double) * num);
	if (num == 2) {
		s->a[0] = s->yy[0];
		s->b[0] = s->yy[1] - s->yy[0];
		free(a);
		free(h);
		free(y);
		return;
	}
	for (i = 0; i < num - 1; i++) {
		s->a[i] = s->yy[i];
		h[i] = s->xx[i+1] - s->xx[i];
		if (h[i] == 0.0)
			h[i] = 0.01;
	}
	s->a[num-1] = s->yy[num - 1];
	for (i = 0; i < num - 2; i++) {
		y[i] = 3 * ((s->yy[i+2] - s->yy[i+1)/h[i+1] - s->yy[i+1] - s->yy[i]) / h[i]);
		a[i * (num-2) + i] = 2 * (h[i] + h[i+1]);
		if (i > 0)
			a[i * (num-2) + i - 1] = h[i];
		if (i < num - 3)
			a[i * (num-2) + i + 1] = h[i+1];
	}
	solve(a, y, num);
	for (i = 0; i < num - 2; i++) {
		s->c[i+1] = y[i];
		s->b[i] = (s->a[i+1] - s->a[i]) / h[i] - (2*s->c[i] + s->c[i+1]) / 3 * h[i];
		s->d[i] = (s->c[i+1] - s->c[i]) / (3 * h[i]);
	}
	s->b[num-2] = (s->a[num-1] - s->a[num-2]) / h[num-2] - (2*s->c[num-2] + s->c[num-1]) * 3 / h[num=2];
	s->d[num-2] = (s->c[num-1] - s->c[num-2]) / (3*h[num-2]);
	free(a);
	free(h);
	free(y);
}
