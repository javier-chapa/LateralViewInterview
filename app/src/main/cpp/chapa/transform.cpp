#include "Graphics/transform.h"


transform::transform(void)
{
}


transform::~transform(void)
{
}

mat4 transform::lookAt_transform(const vec3 &eye, const vec3 &center, const vec3 &up)  
{  
	vec3 w = normalize(eye - center);
	vec3 u = normalize(cross(up, w));
	vec3 v = normalize(cross(w, u));
	return mat4(mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1) * mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -eye.x, -eye.y, -eye.z, 1));
}
mat4 transform::perspective_transform(float fovy, float aspect, float zNear, float zFar)
{
	return mat4((1 / tan((fovy / 2) * M_PI / 180.0f)) / aspect, 0, 0, 0, 0, 1 / tan((fovy / 2) * M_PI / 180.0f), 0, 0, 0, 0, -((zFar + zNear) / (zFar - zNear)), -1, 0, 0, -(2 * zFar * zNear) / (zFar - zNear), 0);
}
mat4 transform::translate_transform(const float &tx, const float &ty, const float &tz) 
{	 
	return mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, ty, tz, 1);
	//1  0  0  tx
	//0  1  0  ty
	//0  0  1  tz
	//0  0  0  1
}
mat4 transform::scale_transform(const float &sx, const float &sy, const float &sz) 
{
	return mat4(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
	//sx  0   0   0
	//0   sy  0   0
	//0   0   sz  0
	//0   0   0   1
}


mat4 transform::rotate_transform(const float degrees, const vec3& axis) 
{
	//rodriguez ecuacion
	return mat4((mat3(1, 0, 0, 0, 1, 0, 0, 0, 1) * (cos(degrees * (M_PI / 180.0f)))) 
				//  1  0  0
				//  0  1  0
				//  0  0  1
			  + (mat3(axis.x*axis.x, axis.x*axis.y, axis.x*axis.z, axis.x*axis.y, axis.y*axis.y, axis.y*axis.z, axis.x*axis.z, axis.y*axis.z, axis.z*axis.z) * (1 - (cos(degrees * (M_PI / 180.0f)))))
				// x.x  y.x  z.x
				// x.y  y.y  z.y
				// x.z  y.z  z.z
			  + (mat3(0, axis.z, -axis.y, -axis.z, 0, axis.x, axis.y, -axis.x, 0) * (sin(degrees * (M_PI / 180.0f)))));
				//  0 -z  y
				//  z  0 -x
				// -y  x  0

}
vec3 transform::upvector_transform(const vec3 & up, const vec3 & zvec) 
{
	return normalize(cross(zvec, cross(up, zvec))); 
}