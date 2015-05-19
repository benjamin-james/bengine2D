#ifndef MATRIX_H
#define MATRIX_H

#include "physics/types.h"

struct mat3 {
	double m[3][3];
};
struct mat2 {
	double m[2][2];
};

struct mat3 mat3_translate(double len);
struct mat3 mat3_rotate(double angle);
struct mat3 mat3_multiply(struct mat3 a, struct mat3 b);
struct point mat3_get_position(struct mat3 m);
struct mat3 mat3_identity(void);
double mat3_det(struct mat3 m);
struct mat3 mat3_inverse(struct mat3 m);

double mat2_det_mat3(struct mat3 m, int r, int c);
double mat2_det(struct mat2 m);

#endif
