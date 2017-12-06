#pragma once

#include <math.h>

class vec4;

class vec3
{
public:
	float x, y, z;
	vec3(void);
	~vec3(void);
	vec3(vec4 a);
	vec3(const float x, const float y, const float z);
	vec3(const float *a);
	vec3 operator () (const vec3 a);
	vec3 operator () (const float x, const float y, const float z);
	vec3 operator () (float *a);
	vec3 operator -();
	float const & operator [] (const unsigned int a)const;
	float & operator [] (const unsigned int a);
	vec3 operator = (const vec3 a);
	vec3 operator + (const vec3 a);
	vec3 operator += (const vec3 a);
	vec3 operator - (const vec3 a);
	vec3 operator - (const vec3 a)const;
	vec3 operator -= (const vec3 a);
	vec3 operator * (const vec3 a);
	vec3 operator *= (const vec3 a);
	vec3 operator * (const float a);
	vec3 operator *= (const float a);
	vec3 operator / (const float a);
	vec3 operator /= (const float a);
	bool operator == (const vec3 a);
	bool operator != (const vec3 a);
	float suma();
	vec3 cross(const vec3 a);
	float dot(vec3 a);
	float magnitude();
	vec3 normalize();
};
	
vec3 operator * (const float a, vec3 b);
float suma(vec3 a);
float dot(vec3 a, vec3 b);
float magnitude(vec3 a);
vec3 normalize(vec3 a);
vec3 cross(vec3 a, vec3 b);
vec3 genNormal(vec3 a, vec3 b, vec3 c);