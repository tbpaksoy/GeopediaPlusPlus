#include "shape3d.h"

#include <math.h>

Mesh *GenerateMesh(const Box &box)
{
        glm::vec3 halfSize = box.size * 0.5f;
        Vertex vertices[8] = {
            halfSize,
            glm::vec3(halfSize.x, -halfSize.y, halfSize.z),
            glm::vec3(halfSize.x, halfSize.y, -halfSize.z),
            glm::vec3(halfSize.x, -halfSize.y, -halfSize.z),
            -halfSize,
            glm::vec3(-halfSize.x, halfSize.y, halfSize.z),
            glm::vec3(-halfSize.x, -halfSize.y, halfSize.z),
            glm::vec3(-halfSize.x, halfSize.y, -halfSize.z)

        };
        unsigned int indices[] = {
            0, 1, 2, 2, 1, 3,
            4, 5, 6, 6, 5, 7,
            0, 2, 5, 5, 2, 7,
            1, 6, 3, 3, 6, 4,
            0, 5, 1, 1, 5, 6,
            2, 3, 7, 7, 3, 4};

        return new Mesh(std::vector<Vertex>(vertices, vertices + 8),
                        std::vector<unsigned int>(indices, indices + 36));
}
Mesh *GenerateMesh(const Sphere &sphere)
{
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < sphere.segments; i++)
        {
                float azimuth = (float)i / (float)(sphere.segments - 1) * 2.0f * 22.0f / 7.0f;
                for (unsigned int j = 0; j < sphere.rings; j++)
                {
                        float zenith = (float)j / (float)(sphere.rings - 1) * 3.14f;
                        vertices.push_back(glm::vec3(
                            sphere.radius * sinf(zenith) * cosf(azimuth),
                            sphere.radius * cosf(zenith),
                            sphere.radius * sinf(zenith) * sinf(azimuth)));
                }
        }
        for (unsigned int i = 0; i < sphere.segments - 1; i++)
        {
                for (unsigned int j = 0; j < sphere.rings - 1; j++)
                {
                        unsigned int first = i * sphere.rings + j;
                        unsigned int second = first + sphere.rings;

                        indices.push_back(first);
                        indices.push_back(second);
                        indices.push_back(first + 1);

                        indices.push_back(second);
                        indices.push_back(second + 1);
                        indices.push_back(first + 1);
                }
        }

        return new Mesh(vertices, indices);
}
Mesh *GenerateMesh(const Cylinder &cylinder)
{
        // Placeholder implementation
        return new Mesh();
}
Mesh *GenerateMesh(const Cone &cone)
{
        // Placeholder implementation
        return new Mesh();
}