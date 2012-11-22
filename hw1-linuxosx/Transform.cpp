// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>


//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
	//  Выражение матрицы поворота через угол поворота  и единичный вектор оси вращения 
	 // В декартовых координатах матрица поворота имеет вид:
// 
//                         |cos(a)-[1-cos(a)]*x^2     [1-cos(a)]*x*y-sin(a)*z    [1-cos(a)]*x*z+sin(a)*y |
// M(alpha(a),vec(x,y,z))= |[1-cos(a)]*y*x+sin(a)*z   cos(a)+[1-cos(a)]*y^2      [1-cos(a)]*y*z-sin(a)*x |
//                         |[1-cos(a)]*z*x-sin(a)*y   [1-cos(a)]*z*y+sin(a)*x    cos(a)+[1-cos(a)]*z^2   |
float alpha=degrees*pi/180;
// mat3 rza=mat3(cos(a),sin(a),0,-sin(a),cos(a),0,0,0,1);
// mat3 rxa=mat3(1,0,0,0,cos(a),sin(a),0,-sin(a),cos(a));
// mat3 rya=mat3(cos(a),0,-sin(a),0,1,0,sin(a),0,cos(a));
// mat3 rz=rza*axis;
// mat3 ry=rya*axis;
// mat3 rx=rxa*axis;
// mat3 rorataionMatrixForAllAxis=rx+ry+rz;
mat3 rorataionMatrixForAllAxis=mat3(cos(alpha)+(1-cos(alpha))*axis.x*axis.x,
									(1-cos(alpha))*axis.y*axis.x+sin(alpha)*axis.z,
									(1-cos(alpha))*axis.z*axis.x-sin(alpha)*axis.y,
									(1-cos(alpha))*axis.x*axis.y-sin(alpha)*axis.z,
									cos(alpha)+(1-cos(alpha))*axis.y*axis.y,
									(1-cos(alpha))*axis.z*axis.y+sin(alpha)*axis.x,
									(1-cos(alpha))*axis.x*axis.z+sin(alpha)*axis.y,
									(1-cos(alpha))*axis.y*axis.z-sin(alpha)*axis.x,
									cos(alpha)+(1-cos(alpha))*axis.z*axis.z );
	// printf("%f, %f, %f,\n",axis.x, axis.y, axis.z);
  // You will change this return call
  return rorataionMatrixForAllAxis;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
 // mat4 myIdentityMatrix = mat4(1.0);
 // vec3 cosTetta=vec3(cos(degrees/180*pi),cos(degrees/180*pi),cos(degrees/180*pi));

//roration surround axis Y: bingo! vector up looks at Y direction.
// mat3 rotationMatrix = mat3(cos(degrees/180*pi),0,-sin(degrees/180*pi),0,1,0,sin(degrees/180*pi),0,cos(degrees/180*pi));

// calling function rotate for rotating surround axis Y
vec3 xAxisCross=glm::normalize(glm::cross(glm::normalize(eye),up));
vec3 yAxisCross=glm::normalize(glm::cross(glm::normalize(eye), xAxisCross));
printf("\nCoordinates cross left: x: %.2f, y: %.2f, z: %.2f", yAxisCross.x, yAxisCross.y, yAxisCross.z);

mat3 rotationMatrix=rotate(degrees,yAxisCross);
eye=eye*rotationMatrix;

printf("\nCoordinates eye: x: %.2f, y: %.2f, z: %.2f; distance: %.2f\n", 
	eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
// printf("Coordinates up: x: %.2f, y: %.2f, z: %.2f;",up.x,up.y,up.z);
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
vec3 xAxisCross=glm::normalize(glm::cross(eye,up));
printf("\nCoordinates cross up: x: %.2f, y: %.2f, z: %.2f", xAxisCross.x, xAxisCross.y, xAxisCross.z);

mat3 rotationMatrix=rotate(degrees,xAxisCross);
eye=rotationMatrix*eye;

// if (eye.z<0)
// {
// 	eye.z=-eye.z;
// }
up=glm::normalize(glm::cross(glm::normalize(eye),xAxisCross));

if (eye.z<0)
{
	up=-up;
}
else if (eye.z>=0)
{
	up=-up;
}

printf("\nCoordinates up: x: %.2f, y: %.2f, z: %.2f;",up.x,up.y,up.z);
// printf("%.2f\n",degrees );
printf("\nCoordinates eye: x: %.2f, y: %.2f, z: %.2f; distance: %.2f\n", 
	eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
  vec3 w=glm::normalize(eye);
  vec3 u=glm::normalize(glm::cross(up,w));
  vec3 v=glm::cross(w,u);

  float wx=w.x;float wy=w.y;float wz=w.z;
  float ux=u.x;float uy=u.y;float uz=u.z;
  float vx=v.x;float vy=v.y;float vz=v.z;

  vec3 neye=glm::normalize(eye);
  float eyex=eye.x;float eyey=eye.y;float eyez=eye.z;
 // printf("\nCoordinates eye: x: %.2f, y: %.2f, z: %.2f; distance: %.2f\n", 
	// neye.x, neye.y, neye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));

  // mat4 lookAtMatrix=mat4(ux,vx,wx,0,uy,vy,wy,0,uz,vz,wz,0,-ux*eyex-uy*eyey-uz*eyez,-vx*eyex-vy*eyey-vz*eyez,wx*eyex-wy*eyey-wz*eyez,1);
  // mat4 lookAtMatrix=mat4(ux,vx,wx,0,uy,vy,wy,0,uz,vz,wz,0,
  // 	-ux*eyex-uy*eyey-uz*eyez,
  // 	-vx*eyex-vy*eyey-vz*eyez,
  // 	wx*eyex-wy*eyey-wz*eyez,1);


mat4 wuv=mat4(ux,vx,wx,0,  uy,vy,wy,0,  uz,vz,wz,0,  0,0,0,1);
mat4 trMat=mat4(1,0,0,0,  0,1,0,0,  0,0,1,0, -eyex,-eyey,-eyez,1);
mat4 lookAtMatrix=glm::transpose(wuv*trMat);
  // mat4 lookAtMatrix=mat4(ux,uy,uz,-ux*eyex-uy*eyey-uz*eyez,vx,vy,vz,
  	// -vx*eyex-vy*eyey-vz*eyez,wx,wy,wz,wx*eyex-wy*eyey-wz*eyez,0,0,0,1);
 printf("\n\n\nCoordinates w: x: %.2f, y: %.2f, z: %.2f;",w.x,w.y,w.z);
 printf("\nCoordinates u: x: %.2f, y: %.2f, z: %.2f;",u.x,u.y,u.z);
 printf("\nCoordinates v: x: %.2f, y: %.2f, z: %.2f;",v.x,v.y,v.z);

  // You will change this return call
  return lookAtMatrix;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
