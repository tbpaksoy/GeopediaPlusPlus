#include "mesh.h"

#include <GL/glew.h>

#include <numeric>

Mesh::Mesh() {}
Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
    : vertices(vertices), indices(indices) {}
Mesh::~Mesh() {}

DrawData &Mesh::GetDrawData()
{
    return drawData;
}
std::vector<Vertex> &Mesh::Vertices()
{
    return vertices;
}
std::vector<unsigned int> &Mesh::Indices()
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
    float *vertexData;
    std::vector<float> data;
    if (vertexDataGenerator)
    {
        for (const auto &vertex : vertices)
        {
            unsigned int count = 0;
            float *generatedData = vertexDataGenerator(count, vertex);
            data.insert(data.end(), generatedData, generatedData + count);
            delete[] generatedData;
        }
    }
    else
    {
        for (const auto &v : vertices)
        {
            if (std::holds_alternative<float>(v))
                data.push_back(std::get<float>(v));
            else if (std::holds_alternative<glm::vec2>(v))
            {
                glm::vec2 vec = std::get<glm::vec2>(v);
                data.push_back(vec.x);
                data.push_back(vec.y);
            }
            else if (std::holds_alternative<glm::vec3>(v))
            {
                glm::vec3 vec = std::get<glm::vec3>(v);
                data.push_back(vec.x);
                data.push_back(vec.y);
                data.push_back(vec.z);
            }
            else if (std::holds_alternative<glm::vec4>(v))
            {
                glm::vec4 vec = std::get<glm::vec4>(v);
                data.push_back(vec.x);
                data.push_back(vec.y);
                data.push_back(vec.z);
                data.push_back(vec.w);
            }
        }
    }

    vertexData = new float[data.size()];
    std::copy(data.begin(), data.end(), vertexData);

    drawData.element_count = static_cast<GLsizei>(indices.size());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
}
void Mesh::DeleteDrawData()
{
    glDeleteVertexArrays(1, &drawData.vao);
    glDeleteBuffers(1, &drawData.vbo);
    glDeleteBuffers(1, &drawData.ebo);
    if (vertexBufferArray)
    {
        delete[] vertexBufferArray;
        vertexBufferArray = nullptr;
    }
    if (indexBufferArray)
    {
        delete[] indexBufferArray;
        indexBufferArray = nullptr;
    }
}
void Mesh::Draw()
{
    drawData.Bind();
    drawData.Draw();
    drawData.Unbind();
}

void Mesh::SetVertices(const std::vector<Vertex> &vertices)
{
    this->vertices = vertices;
}
void Mesh::SetIndices(const std::vector<unsigned int> &indices)
{
    this->indices = indices;
}

void Mesh::SetVertexDataGenerator(const std::function<float *(unsigned int &, const Vertex &)> &generator)
{
    this->vertexDataGenerator = generator;
}
void Mesh::SetVertexSize(size_t size)
{
    this->vertexSize = size;
}
