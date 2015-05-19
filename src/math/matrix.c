#include "math/matrix.h"
#include "physics/types.h"

#include "math.h"

struct mat3 mat3_translate(double len)
{
	struct mat3 m = mat3_identity();
	m.m[0][2] = len;
	return m;
}
struct mat3 mat3_rotate(double angle)
{
	struct mat3 m = mat3_identity();
	m.m[0][0] = cos(angle);
	m.m[1][0] = sin(angle);
	m.m[0][1] = -m.m[1][0];
	m.m[1][1] = m.m[0][0];
	return m;
}
struct mat3 mat3_multiply(struct mat3 a, struct mat3 b)
{
	struct mat3 c = mat3_identity();
	int i, j, k;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (c.m[i][j] = k = 0; k < 3; k++)
				c.m[i][j] += a.m[i][k] * b.m[k][j];
	return c;
}
struct point mat3_get_position(struct mat3 m)
{
	struct point v;
	v.x = m.m[0][2];
	v.y = m.m[1][2];
	return v;
}
struct mat3 mat3_identity(void)
{
	struct mat3 m;
	m.m[0][0] = 1;
	m.m[0][1] = 0;
	m.m[0][2] = 0;
	m.m[1][0] = 0;
	m.m[1][1] = 1;
	m.m[1][2] = 0;
	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = 1;
	return m;
}
double mat3_det(struct mat3 m)
{
	struct mat2 ret;
	double total = 0;
	int sign = 1;
	int a, b, i, j, k;
	for (i = 0; i < 3; i++) {
		a = b = 0;
		for (j = 1; j < 3; j++) { /*Does not start from 0th row*/
			for (k = 0; k < 3; k++) {
				if (k == i)
					continue;
				ret.m[a][b++] = m.m[j][k];
			}
			a++;
			b = 0;
		}
		total += sign * m.m[0][i] * mat2_det(ret);
		sign *= -1;
	}
	return total;
}
static int powerInt(int a, int b)
{
	if (b < 1)
		return 1;
	return a * powerInt(a, b-1);
}
struct mat3 mat3_inverse(struct mat3 m)
{
	int i,j;
	double det = mat3_det(m);
	struct mat3 a = mat3_identity();
	if (det == 0)
		det = 0.001;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			a.m[j][i] = powerInt(-1, i+j) * mat2_det_mat3(m, i, j) / det;
	return a;
}
double mat2_det_mat3(struct mat3 m, int r, int c)
{
	int a, b, i, j;
	struct mat2 minor;
	for (a = 0, i = 0; i < 2; a++, i++) {
		if (i == r)
			a++;
		for (b = 0, j = 0; j < 2; b++, j++) {
			if (j == c)
				b++;
			minor.m[i][j] = m.m[a][b];
		}
	}
	return mat2_det(minor);
}
double mat2_det(struct mat2 m)
{
	return m.m[0][0]*m.m[1][1]-m.m[0][1]*m.m[1][0];
}
