#ifndef DRRAW_DATA_H
#define DRRAW_DATA_H

#include <GL/glew.h>

#include <vector>

struct DrawData
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLsizei element_count;
    GLenum drawType = GL_TRIANGLES;

    void Bind();
    void Unbind();
    void Draw();
};


#endif