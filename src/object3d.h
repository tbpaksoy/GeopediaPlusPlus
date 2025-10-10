#ifndef OBJECT3D_H
#define OBJECT3D_H
#include "object.h"

#include <glm/glm.hpp>

#include <variant>

class Object3D : public Object
{
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
public:
    glm::vec3 Position() const;
    glm::vec3 Rotation() const;
    glm::vec3 Scale() const;

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::quat& rotation);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);

    void Translate(const glm::vec3& delta);
    void Rotate(const glm::vec3& delta);
    void Rotate(const glm::quat& delta);
    void Rescale(const glm::vec3& factor);
};
#endif