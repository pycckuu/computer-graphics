// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>


//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE

  // You will change this return call
  return mat3();
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
 // mat4 myIdentityMatrix = mat4(1.0);
 // vec3 cosTetta=vec3(cos(degrees/180*pi),cos(degrees/180*pi),cos(degrees/180*pi));

//roration surround axis Y:
mat3 rotationMatrix = mat3(cos(degrees/180*pi),0,-sin(degrees/180*pi),0,1,0,sin(degrees/180*pi),1,cos(degrees/180*pi));
//roration surround axis X:
// mat3 rotationMatrix = mat3(1,0,0,0,cos(degrees/180*pi),sin(degrees/180*pi),0,-sin(degrees/180*pi),cos(degrees/180*pi));
//roration surround axis Z:
// mat3 rotationMatrix = mat3(cos(degrees/180*pi),sin(degrees/180*pi),0,-sin(degrees/180*pi),cos(degrees/180*pi),0,0,0,1);
eye=eye*rotationMatrix;
// eye=myIdentityMatrix

// printf("%f",myIdentityMatrix);
// extern int amount;
// amount+=5;



// printf("\n%.2f\n", z);

// eye.x+=eye.y*cos(degrees/180*pi)+eye.z*sin(degrees/180*pi);
// eye.z+=-eye.x*sin(degrees/180*pi)+eye.z*cos(degrees/180*pi);
// eye.y+=sin(degrees/180*pi)+cos(degrees/180*pi);
// printf("\n%i\n", amount);



printf("\n%.2f\n", degrees);
printf("Coordinates eye: x: %.2f, y: %.2f, z: %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
printf("Coordinates up: x: %.2f, y: %.2f, z: %.2f;",up.x,up.y,up.z);
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE

  // You will change this return call
  return mat4();
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
