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

    Polygon(std::vector<glm::vec2> vertices);

    std::vector<glm::vec2> Vertices() const;
    std::vector<unsigned int> Indices() const;
    void Triangulate();
};
#endif