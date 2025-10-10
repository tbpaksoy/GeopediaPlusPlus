#ifndef OBJECT2D_H
#define OBJECT2D_H
#include "object.h"

#include <glm/glm.hpp>

class Object2d : public Object
{
private:
    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
public:

    glm::vec2 Position() const;
    float Rotation() const;
    glm::vec2 Scale() const;

    void SetPosition(const glm::vec2& pos);
    void SetRotation(float rot);
    void SetScale(const glm::vec2& scl);

    void Translate(const glm::vec2& delta);
    void Rotate(float delta);
    void Rescale(const glm::vec2& factor);
};
#endif