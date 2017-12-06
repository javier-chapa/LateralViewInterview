#include "Graphics/vec3.h"


vec3::vec3(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}


vec3::~vec3(void)
{
}

vec3::vec3(const float x, const float y, const float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3::vec3(const float *a){
	this->x = *(a);
	this->y = *(a+1);
	this->z = *(a+2);
}

vec3 vec3::operator () (const vec3 a){
	return vec3(a);
}

vec3 vec3::operator () (const float x, const float y, const float z){
	return vec3(x, y, z);
}

vec3 vec3::operator () (float *a){
	return vec3(*(a), *(a+1), *(a+2));
}

vec3 vec3::operator -(){
	return vec3(-x, -y, -z);
}

float const & vec3::operator [] (const unsigned int a)const{
	if(a == 0) return this->x;
	else if(a == 1)	return this->y;
	else if(a == 2)	return this->z;
	else return this->z;
}

float & vec3::operator [] (const unsigned int a){
	if(a == 0) return this->x;
	else if(a == 1)	return this->y;
	else if(a == 2)	return this->z;
	else return this->z;
}

vec3 vec3::operator = (const vec3 a){
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;

	return *this;
}

vec3 vec3::operator + (const vec3 a){
	return vec3(this->x + a.x, this->y + a.y, this->z + a.z);
}

vec3 vec3::operator += (const vec3 a){
	this->x += a.x;
	this->y += a.y;
	this->z += a.z;

	return *this;
}

vec3 vec3::operator - (const vec3 a){
	return vec3(this->x - a.x, this->y - a.y, this->z - a.z);
}

vec3 vec3::operator - (const vec3 a)const{
	return vec3(this->x - a.x, this->y - a.y, this->z - a.z);
}

vec3 vec3::operator -= (const vec3 a){
	this->x -= a.x;
	this->y -= a.y;
	this->z -= a.z;

	return *this;
}

vec3 vec3::operator * (const vec3 a){
	return vec3(this->x * a.x, this->y * a.y, this->z * a.z);
}

vec3 vec3::operator *= (const vec3 a){
	this->x *= a.x;
	this->y *= a.y;
	this->z *= a.z;

	return *this;
}

vec3 vec3::operator * (const float a){
	return vec3(this->x * a, this->y * a, this->z * a);
}

vec3 vec3::operator *= (const float a){
	this->x *= a;
	this->y *= a;
	this->z *= a;

	return *this;
}

vec3 vec3::operator / (const float a){
	return vec3(this->x / a, this->y / a, this->z / a);
}

vec3 vec3::operator /= (const float a){
	this->x /= a;
	this->y /= a;
	this->z /= a;

	return *this;
}

bool vec3::operator == (const vec3 a){
	return this->x == a.x && this->y == a.y && this->z == a.z;
}

bool vec3::operator != (const vec3 a){
	return !operator==(a);
}

float vec3::suma(){
	return this->x + this->y + this->z;
}

vec3 vec3::cross(const vec3 a){
	return vec3(((this->y)*(a.z)) - ((this->z)*(a.y)), ((this->z)*(a.x)) - ((this->x)*(a.z)), ((this->x)*(a.y)) - ((this->y)*(a.x)));
}

float vec3::dot(vec3 a){
	return ((this->x)*(a.x)) + ((this->y)*(a.y)) + ((this->z)*(a.z));
}

float vec3::magnitude(){
	return sqrt(dot(*this));
}

vec3 vec3::normalize()
{
	return *this / magnitude();
}

////////////

vec3 operator * (const float a, vec3 b){
	return b * a;
}

float suma(vec3 a){
	return a.x + a.y + a.z;
}

float dot(vec3 a, vec3 b){
	return ((a.x)*(b.x)) + ((a.y)*(b.y)) + ((a.z)*(b.z));
}

float magnitude(vec3 a){
	return sqrt(dot(a,a));
}

vec3 normalize(vec3 a){		
	return a / magnitude(a);
}

vec3 cross(vec3 a, vec3 b){
	float x = ((a.y)*(b.z)) - ((a.z)*(b.y));
	float y = ((a.z)*(b.x)) - ((a.x)*(b.z));
	float z = ((a.x)*(b.y)) - ((a.y)*(b.x));
	return vec3(x, y, z);
}

vec3 genNormal(vec3 a, vec3 b, vec3 c){
	return cross(vec3(b.x - a.x, b.y - a.y, b.z - a.z), vec3(c.x - a.x, c.y - a.y, c.z - a.z));
}

