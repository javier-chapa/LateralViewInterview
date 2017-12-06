#pragma once

#include "vec3.h"
#include <math.h>

class vec4
{
public:
	float x, y, z, w;
	vec4(void);
	~vec4(void);
	vec4(vec3 a);
	vec4(const float x, const float y, const float z, float w);
	vec4(const float *a);
	vec4 operator () (const vec4 a);
	vec4 operator () (const float x, const float y, const float z, const float w);
	vec4 operator () (float *a);
	vec4 operator - ();
	float const & operator [] (const unsigned int a) const;
	float & operator [] (const unsigned int a);
	vec4 operator = (const vec4 a);
	vec4 operator + (const vec4 a);
	vec4 operator += (const vec4 a);
	vec4 operator - (const vec4 a);
	vec4 operator -= (const vec4 a);
	vec4 operator * (const vec4 a);
	vec4 operator *= (vec4 a);
	vec4 operator * (const float a);
	vec4 operator *= (const float a);
	vec4 operator / (const float a);
	vec4 operator /= (const float a);
	bool operator == (const vec4 a);
	bool operator != (const vec4 a);
	float suma();
	vec4 cross(const vec4 V1, const vec4 V2, const vec4 V3);
	float dot(vec4 a);
	float magnitude();
	vec4 normalize();
};


vec4 operator * (const float a, vec4 b);
float suma(vec4 a);
float dot(vec4 a, vec4 b);
float magnitude(vec4 a);
vec4 normalize(vec4 a);
vec4 cross(const vec4 V1, const vec4 V2, const vec4 V3);