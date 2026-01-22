#ifndef CAMERA_H
#define CAMERA_H

#include "object3d.h"

#include <glm/glm.hpp>

class Camera3D : public Object3D
{
private:
    float fov, pNear, pFar, aspect = 1.0f;
    float left, right, bottom, top, oNear, oFar;

public:
    Camera3D();
    ~Camera3D();

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetPerspectiveMatrix() const;
    glm::mat4 GetOrthographicMatrix() const;
    glm::mat4 GetModelMatrix() const;

    void SetPerspective(float fov, float aspect, float near, float far);
    void SetOrtographic(float left, float right, float bottom, float top, float near, float far);
    void SetFOV(float fov);
    void SetNearPlane(float plane);
    void SetFarPlane(float plane);
    void SetPlanes(float near, float far);
    void SetAspect(float aspect);
    void SetLeft(float value);
    void SetRight(float value);
    void SetBottom(float value);
    void SetTop(float value);
    void SetNear(float value);
    void SetFar(float value);

    float FOV() const;
    float NearPlane() const;
    float FarPlane() const;
    float Aspect() const;
    float LeftLimit() const;
    float RightLimit() const;
    float BottomLimit() const;
    float TopLimit() const;
    float Near() const;
    float Far() const;

#ifdef IMGUI
    bool DrawGUI() override;
#endif
};
#endif