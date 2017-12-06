#pragma once

#include "vec3.h"

class mat4;

class mat3
{
public:
	vec3 x, y, z;
	mat3(void);
	~mat3(void);
	mat3(mat4 a);
	mat3(vec3 x, vec3 y, vec3 z);
	mat3(const float xx, const float xy, const float xz, const float yx, const float yy, const float yz, const float zx, const float zy, const float zz);
	mat3(const float *a);
	mat3 operator () (const mat3 a);
	mat3 operator () (const vec3 x, const vec3 y, const vec3 z);
	mat3 operator () (const float *a);
	mat3 operator - ();
	vec3 const & operator [] (const unsigned int a) const;
	vec3 & operator [] (const unsigned int a);
	mat3 operator = (const mat3 a);
	mat3 operator + (const mat3 a);
	mat3 operator += (const mat3 a);
	mat3 operator - (const mat3 a);
	mat3 operator -= (const mat3 a);
	mat3 operator * (const mat3 a);
	mat3 operator *= (const mat3 a);
	mat3 operator * (const float a);
	mat3 operator *= (const float a);
	mat3 operator / (const float a);
	mat3 operator /= (const float a);
	bool operator == (const mat3 a);
	bool operator != (const mat3 a);
	mat3 transpose();
};

mat3 operator * (const float a, mat3 b);
mat3 transpose(mat3 a);
vec3 operator * (vec3 a, mat3 b);



	