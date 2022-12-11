#ifndef ARC_SHADER_PROGRAM_H
#define ARC_SHADER_PROGRAM_H

#include <string>

namespace arc {
    class shader_program {
    public:
        shader_program(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
        ~shader_program();

        shader_program(const shader_program&) = delete;
        shader_program& operator=(const shader_program&) = delete;

        unsigned get_uniform_location(const std::string& name);
    private:
        unsigned m_program;
    };
}

#endif
