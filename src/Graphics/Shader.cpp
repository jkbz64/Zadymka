#include <Graphics/Shader.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader() :
        m_isLoaded(false),
        m_ID(0)
{

}

Shader::~Shader()
{
    if(m_ID != 0)
        glDeleteProgram(m_ID);
}

Shader::Shader(const std::string& sV, const std::string& sF, const std::string& sG)
{
    m_isLoaded = loadFromMemory(sV, sF, sG);
}

const Shader& Shader::use() const
{
    glUseProgram(m_ID);
    return *this;
}

GLuint Shader::getID() const
{
    return m_ID;
}

bool Shader::isLoaded() const
{
    return m_isLoaded;
}

bool Shader::loadFromFile(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
    if(m_isLoaded)
    {
        glDeleteProgram(m_ID);
        m_isLoaded = false;
    }
    std::string vSource, fSource, gSource = std::string();
    std::ifstream fin(vertexPath);
    std::stringstream contentStream;
    if(fin.is_open())
    {
        contentStream << fin.rdbuf();
        vSource = contentStream.str();
    }
    else
        return false;
    contentStream = std::stringstream();
    fin.close();
    fin.open(fragmentPath);
    if(fin.is_open())
    {
        contentStream << fin.rdbuf();
        fSource = contentStream.str();
    }
    else
        return false;
    fin.close();
    if(!geometryPath.empty())
    {
        //TODO
    }
    return loadFromMemory(vSource, fSource, gSource);
}

bool Shader::loadFromMemory(const std::string& vSource, const std::string& sSource, const std::string& gSource)
{
    GLuint sVertex, sFragment, gShader;

    //Vertex
    const char* source = vSource.c_str();
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &source, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    //Fragment
    source = sSource.c_str();
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &source, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    //Geo
    if(!gSource.empty())
    {
        source = gSource.c_str();
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &source, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    m_ID = glCreateProgram();
    glAttachShader(m_ID, sVertex);
    glAttachShader(m_ID, sFragment);
    if(!gSource.empty())
        glAttachShader(m_ID, gShader);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAM");

    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if(!gSource.empty())
        glDeleteShader(gShader);
    m_isLoaded = true;
    return true;
}

void Shader::checkCompileErrors(GLuint object, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            throw std::runtime_error(type + " SHADER ERROR:\n" + infoLog + "\n");
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            throw std::runtime_error(type + " SHADER ERROR:\n" + infoLog + "\n");
        }
    }
}

//SETTERS

void Shader::setFloat(const GLchar* name, GLfloat value, GLboolean useShader) const
{
    if(useShader)
        use();
    glUniform1f(glGetUniformLocation(m_ID, name), value);
}

void Shader::setInteger(const GLchar *name, GLint value, GLboolean useShader) const
{
    if (useShader)
        use();
    glUniform1i(glGetUniformLocation(m_ID, name), value);
}
void Shader::setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader) const
{
    if (useShader)
        use();
    glUniform2f(glGetUniformLocation(m_ID, name), value.x, value.y);
}
void Shader::setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader) const
{
    if (useShader)
        use();
    glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader) const
{
    if (useShader)
        use();
    glUniform4f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z, value.w);
}
void Shader::setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader) const
{
    if (useShader)
        use();
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
