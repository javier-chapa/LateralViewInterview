#pragma once

#include "vec4.h"
#include "mat3.h"

class mat4
{
public:
	vec4 x, y, z, w;
	mat4(void);
	~mat4(void);
	mat4(mat3 a);
	mat4(vec4 x, vec4 y, vec4 z, vec4 w);
	mat4(const float xx, const float xy, const float xz, const float xw, const float yx, const float yy, const float yz, const float yw, const float zx, const float zy, const float zz, const float zw, const float wx, const float wy, const float wz, const float ww);
	mat4(const float *a);
	mat4 operator () (const mat4 a);
	mat4 operator () (const vec4 x, const vec4 y, const vec4 z, const vec4 w);
	mat4 operator () (const float *a);
	mat4 operator - ();
	vec4 const & operator [] (const unsigned int a)const;
	vec4 & operator [] (const unsigned int a);
	mat4 operator = (const mat4 a);
	mat4 operator + (const mat4 a);
	mat4 operator += (const mat4 a);
	mat4 operator - (const mat4 a);
	mat4 operator -= (const mat4 a);
	mat4 operator * (const mat4 a);
	mat4 operator *= (const mat4 a);
	mat4 operator * (const float a);
	mat4 operator *= (const float a);
	mat4 operator / (const float a);
	mat4 operator /= (const float a);
	bool operator == (const mat4 a);
	bool operator != (const mat4 a);
	mat4 transpose();
};

mat4 operator * (const float a, mat4 b);
mat4 transpose(mat4 a);
vec4 operator * (vec4 a, mat4 b);
vec4 operator * (mat4 b, vec4 a);