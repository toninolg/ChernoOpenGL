#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>

class Shader
{
    struct ShaderProgramSource {
        std::string vertexSource;
        std::string fragmentSource;
    };

private:
    unsigned int m_rendererID;
    std::string m_filePath;
    // caching for uniforms
    std::unordered_map<std::string, int> m_uniformLocationCache;


public:

    Shader(const std::string& filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform1i(const std::string& name, int value);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:

    ShaderProgramSource parseShader(const std::string& filepath);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int compileShader(unsigned int type, const std::string &source);

    int getUniformLocation(const std::string& name);

};

#endif // SHADER_H
