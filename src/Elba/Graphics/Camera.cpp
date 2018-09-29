#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Elba/Graphics/Camera.hpp"


namespace Elba
{

Camera::Camera()
{
  mPosition = glm::vec3(0.0f, 0.0f, 10.0f);
  mTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  mDirection = glm::normalize(mTarget - mPosition);
  mWorldUp = glm::vec3(0.0f, 0.1f, 0.0f);
  mCameraRight = glm::normalize(glm::cross(mWorldUp, mDirection));
  mCameraUp = glm::cross(mDirection, mCameraRight);
  mProjectionMode = ProjectionMode::Perspective;
}

void Camera::UpdateVectors()
{
  mTarget = normalize(mTarget - mPosition);
  mCameraRight = normalize(cross(mTarget, mWorldUp));
  mCameraUp = cross(mCameraRight, mTarget);
}

glm::mat4 Camera::ConstructViewMatrix()
{
  UpdateVectors();
  
  /*
  glm::vec3 p = mPosition;

  glm::mat4 view;

  // column 0
  view[0][0] = mCameraRight.x;
  view[1][0] = mCameraRight.y;
  view[2][0] = mCameraRight.z;
  view[3][0] = -dot(mCameraRight, p);

  // column 1
  view[0][1] = mCameraUp.x;
  view[1][1] = mCameraUp.y;
  view[2][1] = mCameraUp.z;
  view[3][1] = -dot(mCameraUp, p);

  // column 2
  view[0][2] = -mTarget.x;
  view[1][2] = -mTarget.y;
  view[2][2] = -mTarget.z;
  view[3][2] = dot(mTarget, p);

  view[3][3] = 1.0f;

  return view;
  */
  return glm::lookAt(mPosition, mTarget, mCameraUp);
}

glm::mat4 Camera::ConstructProjMatrix(int aWidth, int aHeight)
{
  /*
  glm::mat4 proj;

  float rad = glm::radians(45.0f);
  float tanHalfFovy = tan(rad / 2.0f);
  float aspect = (float)aWidth / aHeight;
  float zNear = 0.1f;
  float zFar = 50.0f;

  proj[0][0] = 1.0f / (aspect * tanHalfFovy);
  proj[1][1] = 1.0f / (tanHalfFovy);
  proj[2][2] = -(zFar + zNear) / (zFar - zNear);
  proj[2][3] = -1.0f;
  proj[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);

  return proj;
  */

  switch (mProjectionMode)
  {
    case ProjectionMode::Perspective:
    {
      return glm::perspective<float>(90.0f, static_cast<float>(aWidth) / static_cast<float>(aHeight), 0.1f, 50.0f);
    }

    case ProjectionMode::Orthographic:
    {
      float w = static_cast<float>(aWidth) / 2.0f;
      float h = static_cast<float>(aHeight) / 2.0f;

      return glm::ortho(-w, w, -h, h, 0.01f, 100.0f);
    }
  }
}

void Camera::SetPosition(glm::vec3 aPos)
{
  mPosition = aPos;
  UpdateVectors();
}

void Camera::SetTargetPoint(glm::vec3 aPoint)
{
  mTarget = aPoint;
  UpdateVectors();
}

void Camera::SetProjectionMode(ProjectionMode mode)
{
  mProjectionMode = mode;
}

}

