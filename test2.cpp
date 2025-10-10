#include <GL/glew.h>

#include <vector>
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
 
    std::vector<Mesh *> meshes;
    std::vector<Shader *> shaders;
    
    srand((unsigned int)time(nullptr));

    for(size_t i=0; i < 3; i++)
    {
        Mesh *mesh = new Mesh({
            glm::vec3(-randf(), -randf(), 0.0f),
            glm::vec3( randf(), -randf(), 0.0f),
            glm::vec3( randf(),  randf(), 0.0f)
        }, {
            0, 1, 2
        });

        mesh->SetVertexSize(6);
        mesh->GenerateDrawData();
        meshes.push_back(mesh);
        
        Shader shader("shader/solid.vs", "shader/solid.fs");
        shader.ActivateAttributeAndPointer(0u, 3, 3, (void*)0);
        shader.Use();
        shader.Set("color", glm::vec4(randf(), randf(), randf(), 1.0f));
        shaders.push_back(&shader);
    }


    window.SetUpdateCallback([&](float deltaTime) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(size_t i=0; i < meshes.size(); i++)
        {
            shaders[i]->Use();
            meshes[i]->Draw();
        }
    });
    window.Run();
    return 0;
}