#include <Graphics/Texture.hpp>
#include <Lua.hpp>
#include <iostream>

#include <stb_image.h>

struct TextureDeleter
{
    void operator()(GLuint* id)
    {
        std::cerr << "deleting texture" << std::endl;
        glDeleteTextures(1, id);
    }
};

void Texture::registerClass()
{
    Lua::getState().new_usertype<Texture>("Texture",
                                          sol::constructors<Texture()>(),
                                          "create", &Texture::create,
                                          "loadFromFile", &Texture::loadFromFile,
                                          "getSize", [](Texture& texture) { return std::make_tuple(texture.m_size.x, texture.m_size.y); }
    );
}

Texture::Texture() :
    m_ID(nullptr),
    m_size(0, 0),
    m_internalFormat(GL_RGBA),
    m_imageFormat(GL_RGBA),
    m_wrapS(GL_REPEAT),
    m_wrapT(GL_REPEAT),
    m_filterMin(GL_LINEAR),
    m_filterMax(GL_LINEAR),
    m_fboAttachment(false)
{

}

const glm::uvec2& Texture::getSize() const
{
    return m_size;
}

bool Texture::isAttachment()
{
    return m_fboAttachment;
}

void Texture::create(unsigned int width, unsigned int height)
{
    m_ID = std::shared_ptr<GLuint>(new GLuint(0), TextureDeleter());
    m_size = glm::uvec2(width, height);
    glGenTextures(1, m_ID.get());
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::loadFromFile(const std::string &filename)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if(data)
    {
        m_ID = std::shared_ptr<GLuint>(new GLuint(0), TextureDeleter());
        glGenTextures(1, m_ID.get());
        m_size = glm::uvec2(width, height);
        //Bind texture
        bind();
        //Wrapping/ filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);
        //Choose appropriate format
        GLenum format = GL_RGB;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, (int)m_size.x, (int)m_size.y, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return true;
    }
    else
    {
        std::cerr << "Failed to load texture\n";
        stbi_image_free(data);
        m_size = glm::vec2(0, 0);
        return false;
    }
}
