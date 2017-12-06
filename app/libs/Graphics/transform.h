#pragma once

#include "mat4.h"

class transform
{
public:
	transform(void);
	~transform(void);
	static mat4 lookAt_transform(const vec3 &eye, const vec3 &center, const vec3 &up);
	static mat4 perspective_transform(float fovy, float aspect, float zNear, float zFar);
	static mat4 scale_transform(const float &sx, const float &sy, const float &sz);
	static mat4 translate_transform(const float &tx, const float &ty, const float &tz); 
	static mat4 rotate_transform(const float degrees, const vec3& axis);
	static vec3 upvector_transform(const vec3 & up, const vec3 & zvec);
};