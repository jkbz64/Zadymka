#include <Graphics/Texture.hpp>
#include <Lua.hpp>
#include <iostream>

#ifdef _WIN32
    #include <winsock.h>
#elif __linux__
    #include <arpa/inet.h>
#endif

#include <stb_image.h>

void Texture::registerClass()
{
    Lua::getState().new_usertype<Texture>("Texture",
                                          sol::constructors<Texture()>(),
                                          "loadFromFile", &Texture::loadFromFile,
                                          "getSize", [](Texture& texture) { return std::make_tuple(texture.m_size.x, texture.m_size.y); }
    );
}

Texture::Texture() :
    m_ID(0),
    m_size(0, 0),
    m_internalFormat(GL_RGBA),
    m_imageFormat(GL_RGBA),
    m_wrapS(GL_REPEAT),
    m_wrapT(GL_REPEAT),
    m_filterMin(GL_LINEAR),
    m_filterMax(GL_LINEAR)
{

}

Texture::~Texture()
{
    if(m_ID != 0)
        glDeleteTextures(1, &m_ID);
}

const glm::vec2& Texture::getSize() const
{
    return m_size;
}

bool Texture::loadFromFile(const std::string &filename)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if(data)
    {
        if(m_ID != 0)
            glDeleteTextures(1, &m_ID);
        glGenTextures(1, &m_ID);
        m_size.x = width;
        m_size.y = height;
        //Bind texture
        bind();
        //Wrapping/ filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);

        //Choose appropriate format
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, (int)m_size.x, (int)m_size.y, 0, format, GL_UNSIGNED_BYTE, data);
        glad_glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return true;
    }
    else
    {
        std::cerr << "Failed to load texture\n";
        stbi_image_free(data);
        if(m_ID != 0)
            glDeleteTextures(1, &m_ID);
        m_ID = 0;
        m_size = glm::vec2(0, 0);
        return false;
    }
}
