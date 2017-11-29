#include <Graphics/Shader.hpp>
#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <Lua.hpp>

void Shader::registerClass()
{
    Lua::getState().new_usertype<Shader>("Shader",
                                         sol::constructors<Shader(), Shader(const std::string&, const std::string&)>(),
                                         "use", &Shader::use,
                                         "getID", &Shader::getID,
                                         "isLoaded", &Shader::isLoaded,
                                         "loadFromFile", &Shader::loadFromFile,
                                         "loadFromMemory", &Shader::loadFromMemory,
                                         "setFloat", &Shader::setFloat,
                                         "setInteger", &Shader::setInteger,
                                         "setVector2f", &Shader::setVector2f,
                                         "setVector3f", &Shader::setVector3f,
                                         "setMatrix4", &Shader::setMatrix4
    );
}

Shader::Shader() :
      m_isLoaded(false)
{

}

Shader::Shader(const std::string& sV, const std::string& sF, const std::string& sG)
{
    m_isLoaded = loadFromMemory(sV, sF, sG);
}

bool Shader::loadFromFile(std::string vertexPath, std::string fragmentPath, std::string geometryPath)
{
    if(m_isLoaded)
    {
        glDeleteProgram(m_ID);
        m_isLoaded = false;
    }
    std::string vSource, fSource, gSource = "";
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
    if(geometryPath != "")
    {
        //TODO
    }
    if(loadFromMemory(vSource, fSource, gSource))
        return true;
    else
        return false;
}

bool Shader::loadFromMemory(std::string vSource, std::string sSource, std::string gSource)
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
    if(gSource != "")
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
    if(gSource != "")
        glAttachShader(m_ID, gShader);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAM");

    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if(gSource != "")
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
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- \n";
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- \n";
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
