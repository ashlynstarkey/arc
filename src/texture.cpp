#include <glad/gl.h>
#include <sstream>
#include <stb_image.h>
#include <stdexcept>

#include "texture.h"

namespace arc {
    texture::texture(const std::string& path)
    {
        int width, height;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, nullptr, 4);

        if (!data) {
            std::stringstream ss;
            ss << "Failed to load image '" << path << "'";
            throw std::runtime_error(ss.str());
        }

        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    texture::~texture()
    {
        glDeleteTextures(1, &m_texture);
    }

    void texture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }
}
