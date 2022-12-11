#include <glad/gl.h>

#include "mesh.h"

namespace arc {
    mesh::mesh(const std::vector<vertex>& vertices, const std::vector<unsigned>& elements) : m_count{static_cast<unsigned>(elements.size())}
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned), elements.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertex), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex), (void*)(offsetof(vertex, normal)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vertex), (void*)(offsetof(vertex, texcoord)));
    }

    mesh::~mesh()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

    void mesh::draw()
    {
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, (void*)0);
    }
}
