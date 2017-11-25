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
    Drawable<VertexArray>(),
    std::vector<Vertex>(),
    m_primitiveType(type),
    m_needUpdate(false),
    m_vao(0),
    m_vVBO(0),
    m_txVBO(0),
    m_cVBO(0)
{
    if(!m_renderDetails.m_initialized)
    {
        m_renderDetails.m_shader.loadFromMemory(
        R"(
        #version 330 core
        layout (location = 0) in vec2 vertex;
        layout (location = 1) in vec2 texCoord;
        layout (std140) uniform Camera {
            mat4 view;
            mat4 projection;
        };
        uniform mat4 model;
        out vec2 oTexCoord;
        void main()
        {
            gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
            oTexCoord = vec2(texCoord.x, texCoord.y);
        }
        )", // FRAGMENT SHADER
        R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 oTexCoord;
        uniform sampler2D texture1;
        void main()
        {
            FragColor = texture(texture1, oTexCoord);
        }
        )");
        m_renderDetails.m_shader.setInteger("texture1", 0);
        m_renderDetails.m_initialized = true;
    }
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

void VertexArray::draw()
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
        m_renderDetails.m_shader.setMatrix4("model", getModel());
        static const GLenum modes[] = {GL_POINTS, GL_TRIANGLES, GL_TRIANGLES};
        GLenum mode = modes[static_cast<int>(m_primitiveType)];
        glBindVertexArray(m_vao);
        glDrawArrays(mode, 0, size());
        glBindVertexArray(0);
    }
}

void VertexArray::update()
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
