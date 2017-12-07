#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>
#include <glm/fwd.hpp>

using GLuint = unsigned int;
using GLchar = char;
using GLfloat = float;
using GLboolean = unsigned char;
using GLint = int;

class Shader
{
public:
    Shader();
    Shader(const std::string&, const std::string&, const std::string& = std::string(""));
    ~Shader();
    const Shader& use() const;
    GLuint getID() const;
    bool loadFromFile(const std::string&, const std::string&, const std::string& = std::string());
    bool loadFromMemory(const std::string&, const std::string&, const std::string& = std::string());
    void setFloat(const GLchar*, GLfloat, GLboolean = false) const;
    void setInteger(const GLchar*, GLint, GLboolean = false) const;
    void setVector2f(const GLchar*, const glm::vec2&, GLboolean = false) const;
    void setVector3f(const GLchar*, const glm::vec3&, GLboolean = false) const;
    void setVector4f(const GLchar*, const glm::vec4&, GLboolean = false) const;
    void setMatrix4(const GLchar*, const glm::mat4&, GLboolean = false) const;
    bool isLoaded() const;
private:
    bool m_isLoaded;
    GLuint m_ID;
    void checkCompileErrors(GLuint, const std::string&);
};

#endif
