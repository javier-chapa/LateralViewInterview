#include "Graphics/vec4.h"

vec4::vec4(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

vec4::~vec4(void)
{
}

vec4::vec4(vec3 a){
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = 0;
}

vec4::vec4(const float x, const float y, const float z, float w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vec4::vec4(const float *a){
	this->x = *(a);
	this->y = *(a+1);
	this->z = *(a+2);
	this->w = *(a+3);
}

vec4 vec4::operator () (const vec4 a){
	return vec4(a);
}

vec4 vec4::operator () (const float x, const float y, const float z, const float w){
	return vec4(x, y, z, w);
}

vec4 vec4::operator () (float *a){
	return vec4(*(a), *(a+1), *(a+2), *(a+3));
}

vec4 vec4::operator - (){
	return vec4(-x, -y, -z, -w);
}

float const & vec4::operator [] (const unsigned int a) const{
	if(a == 0) return this->x;
	else if(a == 1) return this->y;
	else if(a == 2) return this->z;
	else if(a == 3) return this->w;
	else return this->w;
}

float & vec4::operator [] (const unsigned int a) {
	if(a == 0) return this->x;
	else if(a == 1) return this->y;
	else if(a == 2) return this->z;
	else if(a == 3) return this->w;
	else return this->w;
}

vec4 vec4::operator = (const vec4 a){
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = a.w;

	return *this;
}

vec4 vec4::operator + (const vec4 a){
	return vec4(this->x + a.x, this->y + a.y, this->z + a.z, this->w + a.w);
}

vec4 vec4::operator += (const vec4 a){
	this->x += a.x;
	this->y += a.y;
	this->z += a.z;
	this->w += a.w;

	return *this;
}

vec4 vec4::operator - (const vec4 a){
	return vec4(this->x - a.x, this->y - a.y, this->z - a.z, this->w - a.w);
}

vec4 vec4::operator -= (const vec4 a){
	this->x -= a.x;
	this->y -= a.y;
	this->z -= a.z;
	this->w -= a.w;

	return *this;
}

vec4 vec4::operator * (const vec4 a){
	return vec4(this->x * a.x, this->y * a.y, this->z * a.z, this->w * a.w);
}

vec4 vec4::operator *= (vec4 a){
	this->x *= a.x;
	this->y *= a.y;
	this->z *= a.z;
	this->w *= a.w;

	return *this;
}

vec4 vec4::operator * (const float a){
	return vec4(this->x * a, this->y * a, this->z * a, this->w * a);
}

vec4 vec4::operator *= (const float a){
	this->x *= a;
	this->y *= a;
	this->z *= a;
	this->w *= a;

	return *this;
}

vec4 vec4::operator / (const float a){
	return vec4(this->x / a, this->y / a, this->z / a, this->w / a);
}

vec4 vec4::operator /= (const float a){
	this->x /= a;
	this->y /= a;
	this->z /= a;
	this->w /= a;

	return *this;
}

bool vec4::operator == (const vec4 a){
	return this->x == a.x && this->y == a.y && this->z == a.z && this->w == a.w;
}

bool vec4::operator != (const vec4 a){
	return !operator==(a);
}

float vec4::suma(){
	return this->x + this->y + this->z + this->w;
}

vec4 vec4::cross(const vec4 V1, const vec4 V2, const vec4 V3){
	float x = V1.y * (V2.z * V3.w - V3.z * V2.w) -  V1.z * (V2.y * V3.w - V3.y * V2.w ) +  V1.w * (V2.y * V3.z - V3.y * V2.z);
	float y = V1.x * (V3.z * V2.w - V2.z * V3.w) - V1.z * (V3.x * V2.w - V2.x * V3.w) + V1.w * (V3.x * V2.z - V2.x * V3.z);
	float z = V1.x * (V2.y * V3.w - V3.y * V2.w) - V1.y * (V2.x * V3.w - V3.x * V2.w) + V1.w * (V2.x * V3.y - V3.x * V2.y);
	float w = V1.x * (V3.y * V2.z - V2.y * V3.z) - V1.y * (V3.x * V2.z - V2.x * V3.z) + V1.z * (V3.x * V2.y - V2.x * V3.y);
	return vec4(x,y,z,w);
}

float vec4::dot(vec4 a){
	return ((this->x)*(a.x)) + ((this->y)*(a.y)) + ((this->z)*(a.z)) + ((this->w)*(a.w));
}

float vec4::magnitude(){
	return sqrt(dot(*this));
}

vec4 vec4::normalize()
{
	return *this / magnitude();
}

/////////////

vec4 operator * (const float a, vec4 b){
	return b * a;
}

float suma(vec4 a){
	return a.x + a.y + a.z + a.w;
}

float dot(vec4 a, vec4 b){
	return ((a.x)*(b.x)) + ((a.y)*(b.y)) + ((a.z)*(b.z)) + ((a.w)*(b.w));
}

float magnitude(vec4 a){
	return sqrt(dot(a,a));
}

vec4 normalize(vec4 a){		
	 return a / magnitude(a);
}

vec4 cross(const vec4 V1, const vec4 V2, const vec4 V3){
	float x = V1.y * (V2.z * V3.w - V3.z * V2.w) - V1.z * (V2.y * V3.w - V3.y * V2.w) + V1.w * (V2.y * V3.z - V3.y * V2.z);
	float y = V1.x * (V3.z * V2.w - V2.z * V3.w) - V1.z * (V3.x * V2.w - V2.x * V3.w) + V1.w * (V3.x * V2.z - V2.x * V3.z);
	float z = V1.x * (V2.y * V3.w - V3.y * V2.w) - V1.y * (V2.x * V3.w - V3.x * V2.w) + V1.w * (V2.x * V3.y - V3.x * V2.y);
	float w = V1.x * (V3.y * V2.z - V2.y * V3.z) - V1.y * (V3.x * V2.z - V2.x * V3.z) + V1.z * (V3.x * V2.y - V2.x * V3.y);
	return vec4(x,y,z,w);
}

////////////

vec3::vec3(vec4 a){
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
}