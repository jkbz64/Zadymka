#include <Graphics/VertexArray.hpp>
#include <Lua.hpp>
#include <Graphics/Sprite.hpp>

void VertexArray::registerClass()
{
    Lua::getState().new_usertype<Vertex>("Vertex",
                                         "position", &Vertex::m_position,
                                         "texCoords", &Vertex::m_texCoords
                                         //"color", &Vertex::m_color
                                         );

    Lua::getState().new_usertype<VertexArray>("VertexArray",
                                              sol::constructors<VertexArray(const PrimitiveType&)>(),
                                              "resize", &VertexArray::resize,
                                              "setTexture", &VertexArray::setTexture,
                                              "getVertexes", &VertexArray::getVertexes
    );
}

VertexArray::VertexArray(const PrimitiveType &type) :
    Drawable(),
    std::vector<Vertex>(),
    m_primitiveType(type),
    m_needUpdate(false),
    m_vao(0),
    m_vVBO(0),
    m_txVBO(0),
    m_cVBO(0)
{

}

std::vector<Vertex>& VertexArray::getVertexes()
{
    return static_cast<std::vector<Vertex>&>(*this);
}

void VertexArray::setTexture(const Texture& texture)
{
    m_texture = texture;
}

void VertexArray::resize(std::size_t newSize)
{
    if(newSize > 0)
        std::vector<Vertex>::resize(newSize);
    m_needUpdate = true;
}

void VertexArray::draw(const Shader& shader)
{
    if(m_needUpdate)
    {
        update();
        m_needUpdate = false;
    }

    if(!empty())
    {
        glActiveTexture(GL_TEXTURE0);
        m_texture.bind();
        shader.setMatrix4("model", getModel());
        static const GLenum modes[] = {GL_POINTS, GL_TRIANGLES, GL_TRIANGLES};
        GLenum mode = modes[static_cast<int>(m_primitiveType)];
        glBindVertexArray(m_vao);
        glDrawArrays(mode, 0, size());
        glBindVertexArray(0);
    }
}

GLuint VertexArray::update()
{
    if(m_vao != 0)
    {
        //glDeleteBuffers(1, &m_cVBO);
        glDeleteBuffers(1, &m_txVBO);
        glDeleteBuffers(1, &m_vVBO);
        glDeleteVertexArrays(1, &m_vao);
    }

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vVBO);
    glGenBuffers(1, &m_txVBO);
   // glGenBuffers(1, &m_cVBO);

    std::vector<float> vertices;
    std::vector<float> texCoords;
    //std::vector<float> colors;

    for(auto& vertex : *this)
    {
        vertices.emplace_back(vertex.m_position.x);
        vertices.emplace_back(vertex.m_position.y);
        texCoords.emplace_back(vertex.m_texCoords.x);
        texCoords.emplace_back(vertex.m_texCoords.y);
        //colors.emplace_back(vertex.m_color.);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_txVBO);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), &texCoords.front(), GL_STATIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, m_cVBO);
    //glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), &colors.front(), GL_STATIC_DRAW);

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_vVBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, m_txVBO);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
