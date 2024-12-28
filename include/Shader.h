#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    GLuint ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, const glm::vec2& value);

private:
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif