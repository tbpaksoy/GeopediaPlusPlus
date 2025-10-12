#ifndef GRID3D_H
#define GRID3D_H
#include "../object3d.h"
#include "../drawing/draw_data.h"

#include <glm/glm.hpp>

class Grid3D : Object3D
{
private:
    DrawData drawData;
    glm::vec4 xColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 
              yColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 
              zColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    glm::vec3 length, division;
public:
    Grid3D();
    Grid3D(glm::vec4 xColor, glm::vec4 yColor, glm::vec4 zColor, float length, float division);
    ~Grid3D();

    void SetXColor(const glm::vec4& color);
    void SetYColor(const glm::vec4& color);
    void SetZColor(const glm::vec4& color);
    void SetAlpha(const float alpha);

    void GenerateDrawData();
    void Draw();
};
#endif