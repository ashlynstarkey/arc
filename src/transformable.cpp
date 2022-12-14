#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "transformable.h"

namespace arc {
    transformable::transformable() :
    m_transform{1.0f},
    m_recalculate{false},
    m_origin{0.0f, 0.0f, 0.0f},
    m_position{0.0f, 0.0f, 0.0f},
    m_scale{1.0f, 1.0f, 1.0f},
    m_rotation{1.0f, 0.0f, 0.0f, 0.0f}
    {
    }

    void transformable::reset()
    {
        m_origin = glm::vec3(0.0f);
        m_position = glm::vec3(0.0f);
        m_scale = glm::vec3(1.0f);
        m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

        m_transform = glm::mat4(1.0f);
        m_recalculate = false;
    }

    void transformable::set_origin(glm::vec3 origin)
    {
        m_origin = origin;
    }

    void transformable::set_position(glm::vec3 position)
    {
        m_position = position;
        m_recalculate = true;
    }

    void transformable::set_scale(glm::vec3 scale)
    {
        m_scale = scale;
        m_recalculate = true;
    }

    void transformable::set_rotation(glm::vec3 rotation)
    {
        m_rotation = glm::quat(rotation);
        m_recalculate = true;
    }

    void transformable::translate(glm::vec3 delta)
    {
        m_position += delta;
        m_recalculate = true;
    }

    void transformable::scale(glm::vec3 delta)
    {
        m_scale *= delta;
        m_recalculate = true;
    }

    void transformable::rotate(float delta, glm::vec3 axis)
    {
        m_rotation = glm::rotate(m_rotation, delta, axis);
    }

    const float* transformable::get_transform()
    {
        if (m_recalculate) {
            m_transform = glm::mat4(1.0f);
            m_transform = glm::translate(m_transform, m_position);
            m_transform = m_transform * glm::mat4_cast(m_rotation);
            m_transform = glm::scale(m_transform, m_scale);
            m_transform = glm::translate(m_transform, -m_origin);

            m_recalculate = false;
        }

        return glm::value_ptr(m_transform);
    }
}
