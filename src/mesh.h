#ifndef ARC_MESH_H
#define ARC_MESH_H

#include <glm/glm.hpp>
#include <vector>

namespace arc {
    struct vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texcoord;
    };

    class mesh {
    public:
        mesh(const std::vector<vertex>& vertices, const std::vector<unsigned>& elements);
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
