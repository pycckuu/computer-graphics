// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"


//Takes as input current eye position, and current up vector.
//up is always normalized to a length of 1.
//eye length indicates distance from viewer to origin

// Helper rotation function.  Please implement this.  
// Please ignore "degrees" below; it's actually in radians, 
// since "rotate" is always called with an angle in radians
// Axis is already normalized when passed in by left or up.

mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
      mat3 R ; 

  //Identity Matrix
  mat3 I(1.0);

  // Cross Product Matrix for axis
  mat3 A_star(0,  -axis[2],  axis[1],
          axis[2], 0,       -axis[0],
         -axis[1], axis[0],  0);

  // Outer Product of axis with itself
  mat3 AA_T(axis[0]*axis[0], axis[0]*axis[1], axis[0]*axis[2], 
            axis[1]*axis[0], axis[1]*axis[1], axis[1]*axis[2], 
            axis[2]*axis[0], axis[2]*axis[1], axis[2]*axis[2]);

  //Apply Rodrigues' Formula
  R = cos(degrees)*I+(1-cos(degrees))*AA_T+sin(degrees)*A_star;
  return R ;
}
// Convert to radians (mult by pi/180) before calling rotate
// Rotate up and eye by degrees about the up direction
void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    mat3 R = rotate(degrees * pi / 180.0, up);
    eye = eye * R;
    up = up * R; 
}
// Convert to radians (mult by pi/180) before calling rotate
// Rotate eye and up by degrees about the third direction
// Third direction is obtained by cross producting eye and up.  
void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    mat3 R = rotate(degrees * pi / 180.0, 
                    glm::normalize(glm::cross(eye, up)));
    eye = eye * R;
    up = up * R; 
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    mat4 M ;

   //Coordinate vectors relative to camera
    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(glm::cross(up, w));
    vec3 v = glm::cross(w, u);

   //Compute translation matrix
 M=mat4(u[0],u[1],u[2],-(u[0]*eye[0]+u[1]*eye[1]+u[2]*eye[2]),
        v[0],v[1],v[2],-(v[0]*eye[0]+v[1]*eye[1]+v[2]*eye[2]),
        w[0],w[1],w[2],-(w[0]*eye[0]+w[1]*eye[1]+w[2]*eye[2]),
        0.0 , 0.0, 0.0, 1.0);

    return M ; 
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 ret;
    


    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret;
    ret = mat4(sx,0,0,0,
               0,sy,0,0,
               0,0,sz,0,
               0,0,0,1);
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret;
    ret=  mat4(1,0,0,0,
               0,1,0,0,
               0,0,1,0,
               tx,ty,tz,1);
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
