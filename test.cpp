#include <GL/glew.h>

#include <math.h>
#include <time.h>

#include "src/window.h"
#include "src/shader.h"
#include "src/geometry/mesh.h"

float randf()
{
    return (float)rand() / (float)RAND_MAX;
}

int main()
{
    Window window(glm::ivec2(800, 600), "Test Window");

    Mesh *mesh = new Mesh({glm::vec3(-0.5f, -0.5f, 0.0f),
                           glm::vec3(0.5f, -0.5f, 0.0f),
                           glm::vec3(0.0f, 0.5f, 0.0f)},
                          {0, 1, 2});
    mesh->SetVertexSize(6);
    srand((unsigned int)time(nullptr));
    mesh->SetVertexDataGenerator([](unsigned int &vertexSize, const Vertex &vertex) -> float *
                                 {
        vertexSize = 6;
        glm::vec3 v = std::get<glm::vec3>(vertex);
        return new float[6] {
            v.x, v.y, v.z,
            randf(), randf(), randf()
        }; });
    mesh->GenerateDrawData();
    Shader shader("shader/core.vs", "shader/core.fs");
    shader.ActivateAttributeAndPointer(0u, 3, 6, (void *)0);
    shader.ActivateAttributeAndPointer(1u, 3, 6, (void *)(3 * sizeof(float)));

    window.SetUpdateCallback([&](float deltaTime)
                             {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        mesh->Draw(); });

    window.Run();
    return 0;
}