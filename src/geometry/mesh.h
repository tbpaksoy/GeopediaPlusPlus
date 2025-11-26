#ifndef MESH_H
#define MESH_H

#include "../object3d.h"
#include "../drawing/draw_data.h"

#include <vector>
#include <functional>
#include <variant>
#include <map>

#include <glm/glm.hpp>

typedef std::variant<float, glm::vec2, glm::vec3, glm::vec4> Vertex;

class Mesh : public Object3D 
{
private:
    DrawData drawData;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::function<float *(unsigned int &, const Vertex &)> vertexDataGenerator;
    size_t vertexSize = 3 * sizeof(float);

public:
    Mesh();
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
    ~Mesh();

    DrawData &GetDrawData();
    std::vector<Vertex> &Vertices();
    std::vector<unsigned int> &Indices();
    size_t VertexSize() const;

    void GenerateDrawData();
    void Draw();
    
    void SetVertices(const std::vector<Vertex> &vertices);
    void SetIndices(const std::vector<unsigned int> &indices);

    void SetVertexDataGenerator(const std::function<float *(unsigned int &, const Vertex &)> &generator);
    void SetVertexSize(size_t size);
};
#endif