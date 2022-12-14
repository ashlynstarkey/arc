#ifndef ARC_TEXTURE_H
#define ARC_TEXTURE_H

#include <string>

namespace arc {
    class texture {
    public:
        texture(const std::string& path);
        ~texture();

        texture(const texture&) = delete;
        texture& operator=(const texture&) = delete;

        void bind();
    private:
        unsigned m_texture;
    };
}

#endif
