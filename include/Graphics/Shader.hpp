#ifndef SHADER_HPP
#define SHADER_HPP
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include <Graphics/glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    static void registerClass();
    Shader();
    Shader(const std::string&, const std::string&, const std::string& = std::string(""));
    Shader& use();
    GLuint getID() const;
    bool loadFromFile(std::string, std::string, std::string = "");
    bool loadFromMemory(std::string, std::string, std::string = "");
    void setFloat(const GLchar*, GLfloat, GLboolean = false);
    void setInteger(const GLchar*, GLint, GLboolean = false);
    void setVector2f(const GLchar*, const glm::vec2&, GLboolean = false);
    void setVector3f(const GLchar*, const glm::vec3&, GLboolean = false);
    void setVector4f(const GLchar*, const glm::vec4&, GLboolean = false);
    void setMatrix4(const GLchar*, const glm::mat4&, GLboolean = false);
    bool isLoaded() const;
private:
    bool m_isLoaded;
    GLuint m_ID;
    void checkCompileErrors(GLuint, const std::string&);
};

inline GLuint Shader::getID() const
{
    return m_ID;
}

inline bool Shader::isLoaded() const
{
    return m_isLoaded;
}

inline Shader& Shader::use()
{
    glUseProgram(m_ID);
    return *this;
}

#endif
