#include "object3d.h"

#include <stdexcept>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

glm::vec3 Object3D::Position() const
{
    return position;
}
glm::vec3 Object3D::Scale() const
{
    return scale;
}
glm::vec3 Object3D::Rotation() const
{
    return rotation;
}

glm::vec3 Object3D::Up() const
{
    return glm::normalize(glm::quat(rotation) * glm::vec3(0, 1, 0));
}
glm::vec3 Object3D::Front() const
{
    return glm::normalize(glm::quat(rotation) * glm::vec3(0, 0, -1));
}
glm::vec3 Object3D::Right() const
{
    return glm::normalize(glm::quat(rotation) * glm::vec3(1, 0, 0));
}

void Object3D::SetPosition(const glm::vec3 &position)
{
    this->position = position;
}
void Object3D::SetRotation(const glm::quat &rotation)
{
    this->rotation = glm::eulerAngles(rotation);
}
void Object3D::SetRotation(const glm::vec3 &rotation)
{
    this->rotation = rotation;
}
void Object3D::SetScale(const glm::vec3 &scale)
{
    this->scale = scale;
}

void Object3D::Translate(const glm::vec3 &delta)
{
    position += delta;
}
void Object3D::Rotate(const glm::vec3 &delta)
{
    rotation += delta;
}
void Object3D::Rotate(const glm::quat &delta)
{
    rotation += glm::eulerAngles(delta);
}
void Object3D::Rescale(const glm::vec3 &factor)
{
    scale *= factor;
}
void Object3D::LookAt(const glm::vec3 &point)
{
    rotation = glm::eulerAngles(
        glm::quat_cast(
            glm::inverse(
                glm::lookAt(position, point, glm::vec3(0, 1, 0)))));
}