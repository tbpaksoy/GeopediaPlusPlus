#include "polygon.h"
#include <poly2tri/poly2tri.h>

Polygon::Polygon(std::vector<glm::vec2> vertices)
{
    this->vertices = vertices;
}

std::vector<glm::vec2> Polygon::Vertices() const
{
    return vertices;
}

std::vector<unsigned int> Polygon::Indices() const
{
    if(indices.size())
        return indices;
    else throw std::runtime_error("Polygon not triangulated yet.");
}

void Polygon::Triangulate()
{
    std::vector<p2t::Point*> polyline;
    for (const glm::vec2& v : vertices)
        polyline.push_back(new p2t::Point(v.x, v.y));
    
    p2t::CDT cdt(polyline);
    cdt.Triangulate();

    std::vector<p2t::Triangle*> triangles = cdt.GetTriangles();
    indices.clear();
    for (p2t::Triangle* t : triangles)
    {
        for (int i = 0; i < 3; i++)
        {
            p2t::Point* p = t->GetPoint(i);
            for (size_t j = 0; j < vertices.size(); j++)
            {
                if (vertices[j].x == p->x && vertices[j].y == p->y)
                {
                    indices.push_back(j);
                    break;
                }
            }
        }
    }
    while(polyline.size())
    {
        delete polyline.back();
        polyline.pop_back();
    }
}
