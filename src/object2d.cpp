#include "object2d.h"

glm::vec2 Object2d::Position() const
{
    return position;
}
float Object2d::Rotation() const
{
    return rotation;
}
glm::vec2 Object2d::Scale() const
{
    return scale;
}

void Object2d::SetPosition(const glm::vec2& pos)
{
    position = pos;
}
void Object2d::SetRotation(float rot)
{
    rotation = rot;
}
void Object2d::SetScale(const glm::vec2& scl)
{
    scale = scl;
}

void Object2d::Translate(const glm::vec2& delta)
{
    position += delta;
}
void Object2d::Rotate(float delta)
{
    rotation += delta;
}
void Object2d::Rescale(const glm::vec2& factor)
{
    scale *= factor;
}