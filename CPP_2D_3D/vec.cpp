#include "vec.h"

vec3 vec3::operator-(vec3 &obj){
    return vec3{this->x - obj.x,this->y - obj.y,this->z - obj.z};
}

vec3 vec3::operator+(vec3 &obj){
    return vec3{this->x + obj.x,this->y + obj.y,this->z + obj.z};
}

vec3 vec3::operator*(GLfloat &obj){
    return vec3{obj*this->x, obj*this->y, obj*this->z};
}

float vec3::dot(vec3 obj){
    return obj.x*this->x + obj.y*this->y + obj.z*this->z;
}

float vec3::length() {
    return sqrt(pow(this->x,2) + pow(this->y,2) + pow(this->z,2));
}

vec3 vec3::normalized(){
    float l = this->length();
    return vec3{this->x/l, this->y/l, this->z/l};
}