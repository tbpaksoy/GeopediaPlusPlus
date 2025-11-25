#ifndef POLYGON_H
#define POLYGON_H
#include <vector>

#include <glm/glm.hpp>

#include "../object2d.h"

class Polygon : public Object2d
{
private:
    std::vector<glm::vec2> vertices;
    std::vector<unsigned int> indices;

public:
    Polygon();
    Polygon(std::vector<glm::vec2> vertices);

    void AddVertex(const glm::vec2 &vertex);
    void RemoveVertex(const glm::vec2 &vertex);
    void RemoveVertex(unsigned int index);

    std::vector<glm::vec2> Vertices() const;
    std::vector<unsigned int> Indices() const;
    void Triangulate();
};
#endif