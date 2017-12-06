#include "Graphics/mat3.h"


mat3::mat3(void)
{
	this->x(0,0,0);
	this->y(0,0,0);
	this->z(0,0,0);
}


mat3::~mat3(void)
{
}

mat3::mat3(vec3 x, vec3 y, vec3 z){
	this->x = x;
	this->y = y;
	this->z = z;
}

mat3::mat3(const float xx, const float xy, const float xz, const float yx, const float yy, const float yz, const float zx, const float zy, const float zz){
	this->x.x = xx;
	this->x.y = xy;
	this->x.z = xz;
	this->y.x = yx;
	this->y.y = yy;
	this->y.z = yz;
	this->z.x = zx;
	this->z.y = zy;
	this->z.z = zz;
}

mat3::mat3(const float *a){
	this->x.x = *(a);
	this->x.y = *(a+1);
	this->x.z = *(a+2);
	this->y.x = *(a+3);
	this->y.y = *(a+4);
	this->y.z = *(a+5);
	this->z.x = *(a+6);
	this->z.y = *(a+7);
	this->z.z = *(a+8);
}

mat3 mat3::operator () (const mat3 a){
	return mat3(a);
}

mat3 mat3::operator () (const vec3 x, const vec3 y, const vec3 z){
	return mat3(x, y, z);
}

mat3 mat3::operator () (const float *a){
	return mat3(*(a), *(a+1), *(a+2), *(a+3), *(a+4), *(a+5), *(a+6), *(a+7), *(a+8));
}

mat3 mat3::operator - (){
	return mat3(-x, -y, -z);
}

vec3 const & mat3::operator [] (const unsigned int a) const{
	if(a == 0) return this->x;
	else if(a == 1) return this->y;
	else if(a == 2) return this->z;
	else return this->z;
}

vec3 & mat3::operator [] (const unsigned int a){
	if(a == 0) return this->x;
	else if(a == 1) return this->y;
	else if(a == 2) return this->z;
	else return this->z;
}

mat3 mat3::operator = (const mat3 a){
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;

	return *this;
}

mat3 mat3::operator + (const mat3 a){
	return mat3(this->x + a.x, this->y + a.y, this->z + a.z);
}

mat3 mat3::operator += (const mat3 a){
	this->x += a.x;
	this->y += a.y;
	this->z += a.z;

	return *this;
}

mat3 mat3::operator - (const mat3 a){
	return mat3(this->x - a.x, this->y - a.y, this->z - a.z);
}

mat3 mat3::operator -= (const mat3 a){
	this->x -= a.x;
	this->y -= a.y;
	this->z -= a.z;

	return *this;
}

mat3 mat3::operator * (const mat3 a){
	vec3 f1(x.x, y.x, z.x), f2(x.y, y.y, z.y), f3(x.z, y.z, z.z);
	return mat3(dot(f1,a.x), dot(f2,a.x), dot(f3,a.x), dot(f1,a.y), dot(f2,a.y), dot(f3,a.y), dot(f1,a.z), dot(f2,a.z), dot(f3,a.z));
}

mat3 mat3::operator *= (const mat3 a){
	vec3 f1(x.x, y.x, z.x), f2(x.y, y.y, z.y), f3(x.z, y.z, z.z);
	this->x = vec3(dot(f1,a.x), dot(f2,a.x), dot(f3,a.x));
	this->y = vec3(dot(f1,a.y), dot(f2,a.y), dot(f3,a.y));
	this->z = vec3(dot(f1,a.z), dot(f2,a.z), dot(f3,a.z));

	return *this;
}

mat3 mat3::operator * (const float a){
	return mat3(this->x * a, this->y * a, this->z * a);
}

mat3 mat3::operator *= (const float a){
	this->x *= a;
	this->y *= a;
	this->z *= a;

	return *this;
}

mat3 mat3::operator / (const float a){
	return mat3(this->x / a, this->y / a, this->z / a);
}

mat3 mat3::operator /= (const float a){
	this->x /= a;
	this->y /= a;
	this->z /= a;

	return *this;
}

bool mat3::operator == (const mat3 a){
	return this->x == a.x && this->y == a.y && this->z == a.z;
}

bool mat3::operator != (const mat3 a){
	return !operator==(a);
}

mat3 mat3::transpose(){
	return mat3(x.x, y.x, z.x, x.y, y.y, z.y, x.z, y.z, z.z);
}

//////

mat3 operator * (const float a, mat3 b){
	return b * a;
}

mat3 transpose(mat3 a){
	return mat3(a.x.x, a.y.x, a.z.x, a.x.y, a.y.y, a.z.y, a.x.z, a.y.z, a.z.z);
}

////

vec3 operator * (vec3 a, mat3 b)
{
	return vec3(dot(a,b.x), dot(a,b.y), dot(a,b.z));
}