#ifndef MESH_H
#define MESH_H

#include "../object3d.h"
#include "../drawing/draw_data.h"

#include <vector>
#include <functional>

#include <glm/glm.hpp>

class Mesh : public Object3D 
{
private:
    DrawData drawData;
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    std::function<float*(unsigned int&, glm::vec3&)> vertexDataGenerator;
    size_t vertexSize = 3 * sizeof(float);

public:
    Mesh();
    Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    DrawData& GetDrawData();
    std::vector<glm::vec3>& Vertices();
    std::vector<unsigned int>& Indices();
    size_t VertexSize() const;

    void GenerateDrawData();
    void Draw();
    
    void SetVertices(const std::vector<glm::vec3>& vertices);
    void SetIndices(const std::vector<unsigned int>& indices);

    void SetVertexDataGenerator(const std::function<float*(unsigned int&, glm::vec3&)>& generator);
    void SetVertexSize(size_t size);
};
#endif