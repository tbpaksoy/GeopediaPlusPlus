#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <GL/glew.h>

class Texture
{
private:
        GLuint pointer;
        int width, height, numberOfChannels;

public:
        Texture(const std::string &path);
        ~Texture();

        GLuint GetPointer() const;
        int GetWidth() const;
        int GetHeight() const;

        void Bind();
};
#endif