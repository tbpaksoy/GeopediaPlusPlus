#include "mesh.h"

#include <GL/glew.h>


Mesh::Mesh() {}
Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices)
    : vertices(vertices), indices(indices) {}
Mesh::~Mesh() {}

DrawData& Mesh::GetDrawData() 
{
    return drawData;
}
std::vector<glm::vec3>& Mesh::Vertices() 
{
    return vertices;
}
std::vector<unsigned int>& Mesh::Indices()  
{
    return indices;
}
size_t Mesh::VertexSize() const
{
    return vertexSize;
}


void Mesh::GenerateDrawData() 
{
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    drawData.vao = vao;
    drawData.vbo = vbo;
    drawData.ebo = ebo;

    glBindVertexArray(vao);
    float* vertexData;
    std::vector<float> data;
    if(vertexDataGenerator)
    {
        for(glm::vec3& vertex : vertices)
        {
            unsigned int count = 0;
            float* generatedData = vertexDataGenerator(count, vertex);
            data.insert(data.end(), generatedData, generatedData + count);
            delete[] generatedData;
        }
    }
    else
    {
        for (const glm::vec3& v : vertices)
        {
            data.push_back(v.x);
            data.push_back(v.y);
            data.push_back(v.z);
        }
    }

    vertexData = new float[data.size()];
    std::copy(data.begin(), data.end(), vertexData);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    drawData.element_count = static_cast<GLsizei>(indices.size());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
}
void Mesh::Draw() 
{
    drawData.Bind();
    drawData.Draw();
    drawData.Unbind();
}

void Mesh::SetVertices(const std::vector<glm::vec3>& vertices) 
{
    this->vertices = vertices;
}
void Mesh::SetIndices(const std::vector<unsigned int>& indices)
{
    this->indices = indices;
}

void Mesh::SetVertexDataGenerator(const std::function<float*(unsigned int&, glm::vec3&)>& generator) 
{
    this->vertexDataGenerator = generator;
}
void Mesh::SetVertexSize(size_t size)
{
    this->vertexSize = size;
}