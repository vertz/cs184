// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
/**
	R(axis,degrees) := I(3x3)*cos(angle) + axis * axis^t * (1 - cos(angle)) + A* sin(angle) 
*/
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
  float angle = glm::radians(degrees);	

  float x = axis.x;
  float y = axis.y;
  float z = axis.z;

  // I(3x3)*cos(angle)
  mat3 m1 = mat3(1.0) * cos(angle);

  // axis * axis^t * (1 - cos(angle))
  mat3 m2 = mat3(x*x, x*y, x*z,
		 x*y, y*y, y*z,
		 x*z, y*z, z*z);
  m2 = glm::transpose(m2) * (1 - cos(angle));

  // A* sin(angle) 
  mat3 m3 = mat3( 0, -z,  y,
		  z,  0, -x,
		 -y,  x,  0);
  m3 = glm::transpose(m3) * sin(angle);

  return (m1 + m2 + m3);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) 
{
  vec3 axis = glm::normalize(up);
  mat3 R = rotate(degrees, axis);

  eye = R * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) 
{
  vec3 axis = glm::normalize(glm::cross(eye, up));
  mat3 R = rotate(degrees, axis);

  eye = R * eye;
  up  = R * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) 
{
  vec3 w = glm::normalize(eye);
  vec3 u = glm::normalize(glm::cross(up, w));
  vec3 v = glm::cross(w, u);

  mat4 R = mat4(u.x, u.y, u.z, 0.0,
		v.x, v.y, v.z, 0.0,
		w.x, w.y, w.z, 0.0,
		0.0, 0.0, 0.0, 1.0);
  R = glm::transpose(R);

  mat4 T = mat4(1.0, 0.0, 0.0, -eye.x,
		0.0, 1.0, 0.0, -eye.y,
		0.0, 0.0, 1.0, -eye.z,
		0.0, 0.0, 0.0,   1.0 );
  T = glm::transpose(T);

  return (R * T);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
