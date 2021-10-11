#include "shader.h"
#include "renderer.h"
#include <iostream>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string &filepath) : m_filePath(filepath), m_rendererID(0)
{
    // Create shaders
    ShaderProgramSource source = parseShader(filepath);

    GLCall(m_rendererID = createShader(source.vertexSource, source.fragmentSource));
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_rendererID));
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_rendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v3, v3));
}

Shader::ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            if (type != -1){
                ss[type] << line << "\n";
            }
        }
    }

    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program));

    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // Query if something went wrong
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE){
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        char* message = (char*)alloca(length * sizeof (char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}
int Shader::getUniformLocation(const std::string &name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()){
        return m_uniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
    if (location == -1){
        std::cout << "Warning:: uniform '" << name << "' doesn't exist!" << std::endl;
    }
    else {
        m_uniformLocationCache[name] = location;
    }
    return location;
}
