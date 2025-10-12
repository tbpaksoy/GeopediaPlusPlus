#include "grid3d.h"

#include <vector>

Grid3D::Grid3D(){}
Grid3D::Grid3D(glm::vec4 xColor, glm::vec4 yColor, glm::vec4 zColor, float length, float division)
{
    this->xColor = xColor;
    this->yColor = yColor;
    this->zColor = zColor;

    this->length = glm::vec3(length);
    this->division = glm::vec3(division);
}
Grid3D::~Grid3D(){}

void Grid3D::SetXColor(const glm::vec4& color)
{
    xColor = color;
}
void Grid3D::SetYColor(const glm::vec4& color)
{
    yColor = color;
}
void Grid3D::SetZColor(const glm::vec4& color)
{
    zColor = color;
}
void Grid3D::SetAlpha(const float alpha)
{
    xColor.a = yColor.a = zColor.a = alpha;
}

void Grid3D::GenerateDrawData()
{
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    drawData.vao = vao;
    drawData.vbo = vbo;
    drawData.ebo = ebo;
    drawData.drawType = GL_LINES;

    int pointCount = 0;

    std::vector<float> points;
    for(float f = -length.x / 2.0f; f < length.x / 2.0f; f += division.x)
    {
        points.push_back(0.0);
        points.push_back(f);
        points.push_back(-length.x / 2.0f);
        points.push_back(xColor.r);
        points.push_back(xColor.g);
        points.push_back(xColor.b);
        pointCount++;

        points.push_back(0.0);
        points.push_back(f);
        points.push_back(length.x / 2.0f);
        points.push_back(xColor.r);
        points.push_back(xColor.g);
        points.push_back(xColor.b);
        pointCount++;
        
        points.push_back(0.0);
        points.push_back(-length.x / 2.0f);
        points.push_back(f);
        points.push_back(xColor.r);
        points.push_back(xColor.g);
        points.push_back(xColor.b);
        pointCount++;

        points.push_back(0.0);
        points.push_back(length.x / 2.0f);
        points.push_back(f);
        points.push_back(xColor.r);
        points.push_back(xColor.g);
        points.push_back(xColor.b);
        pointCount++;
    }

    for(float f = -length.y / 2.0f; f < length.y / 2.0f; f += division.y)
    {
        points.push_back(f);
        points.push_back(0.0);
        points.push_back(-length.y / 2.0f);
        points.push_back(yColor.r);
        points.push_back(yColor.g);
        points.push_back(yColor.b);
        pointCount++;

        points.push_back(f);
        points.push_back(0.0);
        points.push_back(length.y / 2.0f);
        points.push_back(yColor.r);
        points.push_back(yColor.g);
        points.push_back(yColor.b);
        pointCount++;

        points.push_back(-length.y / 2.0f);
        points.push_back(0.0);
        points.push_back(f);
        points.push_back(yColor.r);
        points.push_back(yColor.g);
        points.push_back(yColor.b);
        pointCount++;

        points.push_back(length.y / 2.0f);
        points.push_back(0.0);
        points.push_back(f);
        points.push_back(yColor.r);
        points.push_back(yColor.g);
        points.push_back(yColor.b);
        pointCount++;
    }

    for(float f = -length.z / 2.0f; f < length.z / 2.0f; f += division.z)
    {
        points.push_back(f);
        points.push_back(-length.z / 2.0f);
        points.push_back(0.0);
        points.push_back(zColor.r);
        points.push_back(zColor.g);
        points.push_back(zColor.b);
        pointCount++;

        points.push_back(f);
        points.push_back(length.z / 2.0f);
        points.push_back(0.0);
        points.push_back(zColor.r);
        points.push_back(zColor.g);
        points.push_back(zColor.b);
        pointCount++;

        points.push_back(-length.z / 2.0f);
        points.push_back(f);
        points.push_back(0.0);
        points.push_back(zColor.r);
        points.push_back(zColor.g);
        points.push_back(zColor.b);
        pointCount++;

        points.push_back(length.z / 2.0f);
        points.push_back(f);
        points.push_back(0.0);
        points.push_back(zColor.r);
        points.push_back(zColor.g);
        points.push_back(zColor.b);
        pointCount++;
    }

    drawData.element_count = pointCount;

    float *vertexData = new float[points.size()];
    std::copy(points.begin(), points.end(), vertexData);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), vertexData, GL_STATIC_DRAW);
    
    std::vector<unsigned int> indices;
    for(int i = 0; i < pointCount; i++)
        indices.push_back(i);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
}
void Grid3D::Draw()
{
    drawData.Bind();
    drawData.Draw();
    drawData.Unbind();
}