#include <Graphics/VertexArray.hpp>
#include <Lua.hpp>
#include <Graphics/Sprite.hpp>

void VertexArray::registerClass(sol::table module)
{
    module.new_usertype<Vertex>("Vertex",
                                         "position", &Vertex::m_position,
                                         "texCoords", &Vertex::m_texCoords
                                         //"color", &Vertex::m_color
                                         );

    module.new_usertype<VertexArray>("VertexArray",
                                              sol::constructors<VertexArray(const PrimitiveType&)>(),
                                              "resize", &VertexArray::resize,
                                              "setTexture", &VertexArray::setTexture,
                                              "getVertexes", &VertexArray::getVertexes,
                                              sol::base_classes, sol::bases<Drawable>()
    );
}

VertexArray::VertexArray(const PrimitiveType &type) :
    Drawable(),
    std::vector<Vertex>(),
    m_primitiveType(type),
    m_needUpdate(false)
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

const Texture& VertexArray::getTexture() const
{
    return m_texture;
}

void VertexArray::draw(Renderer* renderer)
{
    renderer->render(*this);
}

const PrimitiveType& VertexArray::getPrimitiveType() const
{
    return m_primitiveType;
}

GLuint VertexArray::update() const
{
    static GLuint vao = 0;
    static GLuint vVBO = 0;
    static GLuint txVBO = 0;
    if(m_needUpdate)
    {
        if(vao != 0)
        {
            //glDeleteBuffers(1, &m_cVBO);
            glDeleteBuffers(1, &txVBO);
            glDeleteBuffers(1, &vVBO);
            glDeleteVertexArrays(1, &vao);
        }

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vVBO);
        glGenBuffers(1, &txVBO);
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

        glBindBuffer(GL_ARRAY_BUFFER, vVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, txVBO);
        glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), &texCoords.front(), GL_STATIC_DRAW);
        //glBindBuffer(GL_ARRAY_BUFFER, m_cVBO);
        //glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), &colors.front(), GL_STATIC_DRAW);

        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vVBO);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, txVBO);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_needUpdate = false;
    }
    return vao;
}