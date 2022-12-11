#ifndef ARC_MESH_H
#define ARC_MESH_H

#include <vector>

namespace arc {
    class mesh {
    public:
        mesh(const std::vector<float>& vertices, const std::vector<unsigned>& elements);
        ~mesh();

        mesh(const mesh&) = delete;
        mesh& operator=(const mesh&) = delete;

        void draw();
    private:
        unsigned m_vao;
        unsigned m_vbo;
        unsigned m_ebo;
        unsigned m_count;
    };
}

#endif
