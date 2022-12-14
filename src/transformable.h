#ifndef ARC_TRANSFORMABLE_H
#define ARC_TRANSFORMABLE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace arc {
    class transformable {
    public:
        transformable();

        void reset();

        void set_origin(glm::vec3 origin);
        void set_position(glm::vec3 position);
        void set_scale(glm::vec3 scale);
        void set_rotation(glm::vec3 rotation);

        void translate(glm::vec3 delta);
        void scale(glm::vec3 delta);
        void rotate(float delta, glm::vec3 axis);

        const float* get_transform();
    private:
        glm::mat4 m_transform;
        bool m_recalculate;

        glm::vec3 m_origin;
        glm::vec3 m_position;
        glm::vec3 m_scale;
        glm::quat m_rotation;
    };
}

#endif
