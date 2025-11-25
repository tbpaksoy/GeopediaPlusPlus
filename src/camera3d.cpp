#include "camera3d.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera3D::Camera3D() {}
Camera3D::~Camera3D() {}

glm::mat4 Camera3D::GetViewMatrix() const
{
    return glm::lookAt(position, position + Front(), Up());
}
glm::mat4 Camera3D::GetPerspectiveMatrix() const
{
    return glm::perspective(glm::radians(fov), aspect, pNear, pFar);
}
glm::mat4 Camera3D::GetOrthographicMatrix() const
{
    return glm::ortho(left, right, bottom, top, oNear, oFar);
}
glm::mat4 Camera3D::GetModelMatrix() const
{
    return glm::mat4(1.0f);
}

void Camera3D::SetPerspective(float fov, float aspect, float near, float far)
{
    this->fov = fov;
    this->aspect = aspect;
    pNear = near;
    pFar = far;
}
void Camera3D::SetOrtographic(float left, float right, float bottom, float top, float near, float far)
{
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    oNear = near;
    oFar = far;
}
void Camera3D::SetFOV(float fov)
{
    this->fov = fov;
}
void Camera3D::SetNearPlane(float near)
{
    pNear = near;
}
void Camera3D::SetFarPlane(float far)
{
    pFar = far;
}

void Camera3D::SetPlanes(float near, float far)
{
    pNear = near;
    pFar = far;
}
void Camera3D::SetAspect(float aspect)
{
    this->aspect = aspect;
}
void Camera3D::SetLeft(float left)
{
    this->left = left;
}
void Camera3D::SetRight(float right)
{
    this->right = right;
}
void Camera3D::SetBottom(float bottom)
{
    this->bottom = bottom;
}
void Camera3D::SetTop(float top)
{
    this->top = top;
}
void Camera3D::SetNear(float near)
{
    oNear = near;
}
void Camera3D::SetFar(float far)
{
    oFar = far;
}

float Camera3D::FOV() const
{
    return fov;
}
float Camera3D::NearPlane() const
{
    return pNear;
}
float Camera3D::FarPlane() const
{
    return pFar;
}
float Camera3D::Aspect() const
{
    return aspect;
}
float Camera3D::LeftLimit() const
{
    return left;
}
float Camera3D::RightLimit() const
{
    return right;
}
float Camera3D::BottomLimit() const
{
    return bottom;
}
float Camera3D::TopLimit() const
{
    return top;
}
float Camera3D::Near() const
{
    return oNear;
}
float Camera3D::Far() const
{
    return oFar;
}