#ifndef OBJECT3D_H
#define OBJECT3D_H
#include "object.h"

#include <glm/glm.hpp>

#include <variant>

class Object3D : public Object
{
protected:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.00001f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

public:
    glm::vec3 Position() const;
    glm::vec3 Rotation() const;
    glm::vec3 Scale() const;

    glm::vec3 Up() const;
    glm::vec3 Front() const;
    glm::vec3 Right() const;

    void SetPosition(const glm::vec3 &position);
    void SetRotation(const glm::quat &rotation);
    void SetRotation(const glm::vec3 &rotation);
    void SetScale(const glm::vec3 &scale);

    void Translate(const glm::vec3 &delta);
    void Rotate(const glm::vec3 &delta);
    void Rotate(const glm::quat &delta);
    void Rescale(const glm::vec3 &factor);
    void LookAt(const glm::vec3 &point);
#ifdef IMGUI
    bool DrawGUI() override;
#endif
};
#endif