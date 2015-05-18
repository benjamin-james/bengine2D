#ifndef GEOMETRY_H
#define GEOMETRY_H

struct point {
	int x,y;
};
struct triangle {
	struct point a,b,c;
};
struct polygon {
	int num_pts;
	struct point *pts;
	struct point position, rect;
};

struct point point_create(int x, int y);
struct triangle triangle_create(struct point a, struct point b, struct point c);
struct polygon polygon_create(struct point a, ...);

bool point_equals(struct point a, struct point b);
bool point_triangle(struct triangle a, struct point b);
bool point_rect(SDL_Rect a, struct point b);
bool point_polygon(struct polygon a, struct point b);
bool rect_rect(SDL_Rect a, SDL_Rect b);
bool poly_rect(struct polygon a, SDL_Rect b);
bool polygon_polygon(struct polygon a, struct polygon b);

#endif
