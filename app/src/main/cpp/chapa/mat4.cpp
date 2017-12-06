#include "Graphics/mat4.h"


mat4::mat4(void)
{
	this->x(0,0,0,0);
	this->y(0,0,0,0);
	this->z(0,0,0,0);
	this->w(0,0,0,0);
}


mat4::~mat4(void)
{
}


mat4::mat4(mat3 a){
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = vec4(0,0,0,1);
}

mat4::mat4(vec4 x, vec4 y, vec4 z, vec4 w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

mat4::mat4(const float xx, const float xy, const float xz, const float xw, const float yx, const float yy, const float yz, const float yw, const float zx, const float zy, const float zz, const float zw, const float wx, const float wy, const float wz, const float ww){
	this->x.x = xx;
	this->x.y = xy;
	this->x.z = xz;
	this->x.w = xw;
	this->y.x = yx;
	this->y.y = yy;
	this->y.z = yz;
	this->y.w = yw;
	this->z.x = zx;
	this->z.y = zy;
	this->z.z = zz;
	this->z.w = zw;
	this->w.x = wx;
	this->w.y = wy;
	this->w.z = wz;
	this->w.w = ww;
}

mat4::mat4(const float *a){
	this->x.x = *(a);
	this->x.y = *(a+1);
	this->x.z = *(a+2);
	this->x.w = *(a+3);
	this->y.x = *(a+4);
	this->y.y = *(a+5);
	this->y.z = *(a+6);
	this->y.w = *(a+7);
	this->z.x = *(a+8);
	this->z.y = *(a+9);
	this->z.z = *(a+10);
	this->z.w = *(a+11);
	this->w.x = *(a+12);
	this->w.y = *(a+13);
	this->w.z = *(a+14);
	this->w.w = *(a+15);
}

mat4 mat4::operator () (const mat4 a){
	return mat4(a);
}

mat4 mat4::operator () (const vec4 x, const vec4 y, const vec4 z, const vec4 w){
	return mat4(x, y, z, w);
}

mat4 mat4::operator () (const float *a){
	return mat4(*(a), *(a+1), *(a+2), *(a+3), *(a+4), *(a+5), *(a+6), *(a+7), *(a+8), *(a+9), *(a+10), *(a+11), *(a+12), *(a+13), *(a+14), *(a+15));
}

mat4 mat4::operator - (){
	return mat4(-x, -y, -z, -w);
}

vec4 const & mat4::operator [] (const unsigned int a)const{
	if(a == 0) return this->x;
	else if(a == 1) return this->y;
	else if(a == 2) return this->z;
	else if(a == 3) return this->w;
	else return this->w;
}

vec4 & mat4::operator [] (const unsigned int a){
	if(a == 0) return this->x;
	else if(a == 1) return this->y;
	else if(a == 2) return this->z;
	else if(a == 3) return this->w;
	else return this->w;
}

mat4 mat4::operator = (const mat4 a){
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = a.w;

	return *this;
}

mat4 mat4::operator + (const mat4 a){
	return mat4(this->x + a.x, this->y + a.y, this->z + a.z, this->w + a.w);
}

mat4 mat4::operator += (const mat4 a){
	this->x += a.x;
	this->y += a.y;
	this->z += a.z;
	this->w += a.w;

	return *this;
}

mat4 mat4::operator - (const mat4 a){
	return mat4(this->x - a.x, this->y - a.y, this->z - a.z, this->w - a.w);
}

mat4 mat4::operator -= (const mat4 a){
	this->x -= a.x;
	this->y -= a.y;
	this->z -= a.z;
	this->w -= a.w;

	return *this;
}

mat4 mat4::operator * (const mat4 a){
	vec4 f1(x.x, y.x, z.x, w.x), f2(x.y, y.y, z.y, w.y), f3(x.z, y.z, z.z, w.z), f4(x.w, y.w, z.w, w.w);
	return mat4(dot(f1,a.x), dot(f2,a.x), dot(f3,a.x), dot(f4,a.x), dot(f1,a.y), dot(f2,a.y), dot(f3,a.y), dot(f4,a.y), dot(f1,a.z), dot(f2,a.z), dot(f3,a.z), dot(f4,a.z), dot(f1,a.w), dot(f2,a.w), dot(f3,a.w), dot(f4,a.w));
}

mat4 mat4::operator *= (const mat4 a){
	vec4 f1(x.x, y.x, z.x, w.x), f2(x.y, y.y, z.y, w.y), f3(x.z, y.z, z.z, w.z), f4(x.w, y.w, z.w, w.w);
	this->x = vec4(dot(f1,a.x), dot(f2,a.x), dot(f3,a.x), dot(f4,a.x));
	this->y = vec4(dot(f1,a.y), dot(f2,a.y), dot(f3,a.y), dot(f4,a.y));
	this->z = vec4(dot(f1,a.z), dot(f2,a.z), dot(f3,a.z), dot(f4,a.z));
	this->w = vec4(dot(f1,a.w), dot(f2,a.w), dot(f3,a.w), dot(f4,a.w));

	return *this;
}

mat4 mat4::operator * (const float a){
	return mat4(this->x * a, this->y * a, this->z * a, this->w * a);
}

mat4 mat4::operator *= (const float a){
	this->x *= a;
	this->y *= a;
	this->z *= a;
	this->w *= a;

	return *this;
}

mat4 mat4::operator / (const float a){
	return mat4(this->x / a, this->y / a, this->z / a, this->w / a);
}

mat4 mat4::operator /= (const float a){
	this->x /= a;
	this->y /= a;
	this->z /= a;
	this->w /= a;

	return *this;
}

bool mat4::operator == (const mat4 a){
	return this->x == a.x && this->y == a.y && this->z == a.z && this->w == a.w;
}

bool mat4::operator != (const mat4 a){
	return !operator==(a);
}

mat4 mat4::transpose(){
	return mat4(x.x, y.x, z.x, w.x, x.y, y.y, z.y, w.y, x.z, y.z, z.z, w.z, x.w, y.w, z.w, w.w);
}

//////////

mat4 transpose(mat4 a){
	return mat4(a.x.x, a.y.x, a.z.x, a.w.x, a.x.y, a.y.y, a.z.y, a.w.y, a.x.z, a.y.z, a.z.z, a.w.z, a.x.w, a.y.w, a.z.w, a.w.w);
}

vec4 operator * (vec4 a, mat4 b){
	return vec4(dot(a,b.x), dot(a,b.y), dot(a,b.z), dot(a,b.w));
}

vec4 operator * (mat4 b, vec4 a)
{
	mat4 c(b.transpose());
	return a * c;
}

/////////

mat4 operator * (const float a, mat4 b){
	return b * a;
}

mat3::mat3(mat4 a){
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
}