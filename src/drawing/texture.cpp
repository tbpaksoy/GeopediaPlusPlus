#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const std::string &path)
{
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &numberOfChannels, 0);

        if (!data) {
                throw std::runtime_error("Failed to load texture: " + path);
        }

        glGenTextures(1, &pointer);
        glBindTexture(GL_TEXTURE_2D, pointer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum format = (numberOfChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
}
Texture::~Texture() {}

GLuint Texture::GetPointer() const
{
        return pointer;
}
int Texture::GetWidth() const
{
        return width;
}
int Texture::GetHeight() const
{
        return height;
}

void Texture::Bind()
{
        glBindTexture(GL_TEXTURE_2D, pointer);
}