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

void Object3D::SetPosition(const glm::vec3& position)
{
    this->position = position;
}
void Object3D::SetRotation(const glm::quat& rotation)
{
    this->rotation = glm::eulerAngles(rotation);
}
void Object3D::SetRotation(const glm::vec3& rotation)
{
    this->rotation = rotation;
}
void Object3D::SetScale(const glm::vec3& scale)
{
    this->scale = scale;
}

void Object3D::Translate(const glm::vec3& delta)
{
    position += delta;
}
void Object3D::Rotate(const glm::vec3& delta)
{
    rotation += delta;
}
void Object3D::Rotate(const glm::quat& delta)
{
    rotation += glm::eulerAngles(delta);
}
void Object3D::Rescale(const glm::vec3& factor)
{
    scale *= factor;
}