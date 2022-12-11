#include <fstream>
#include <glad/gl.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "shader_program.h"

namespace arc {
    std::string read_file(const std::string& path)
    {
        std::ifstream file;
        std::string result;

        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        try {
            std::stringstream ss;

            file.open(path);
            ss << file.rdbuf();
            file.close();

            result = ss.str();
        } catch (std::ifstream::failure ex) {
            std::stringstream ss;
            ss << "Failed to open file '" << path << "'";
            throw std::runtime_error(ss.str());
        }

        return result;
    }

    unsigned create_shader(unsigned type, const std::string& source)
    {
        unsigned shader = glCreateShader(type);
        const char* c_str = source.c_str();
        glShaderSource(shader, 1, &c_str, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetShaderInfoLog(shader, 512, nullptr, info_log);

            std::stringstream ss;
            ss << "Failed to compile ";
            ss << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader");
            ss << ":\n" << info_log;

            glDeleteShader(shader);
            throw std::runtime_error(ss.str());
        }

        return shader;
    }

    shader_program::shader_program(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
    {
        std::string vs_source = read_file(vertex_shader_path);
        std::string fs_source = read_file(fragment_shader_path);
        unsigned vs, fs;

        vs = create_shader(GL_VERTEX_SHADER, vs_source);

        try {
            fs = create_shader(GL_FRAGMENT_SHADER, fs_source);
        } catch (...) {
            glDeleteShader(vs);
            throw;
        }

        m_program = glCreateProgram();

        glAttachShader(m_program, vs);
        glAttachShader(m_program, fs);
        glLinkProgram(m_program);
        glDetachShader(m_program, vs);
        glDetachShader(m_program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);

        int success;
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);
        if (!success) {
            char info_log[512];
            glGetProgramInfoLog(m_program, 512, nullptr, info_log);

            std::stringstream ss;
            ss << "Failed to link shader program:\n" << info_log;

            glDeleteProgram(m_program);
            throw std::runtime_error(ss.str());
        }
    }

    shader_program::~shader_program()
    {
        glDeleteProgram(m_program);
    }

    unsigned shader_program::get_uniform_location(const std::string& name)
    {
        return glGetUniformLocation(m_program, name.c_str());
    }

    void shader_program::use()
    {
        glUseProgram(m_program);
    }
}
