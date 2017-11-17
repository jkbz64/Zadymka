#include <Graphics/Sprite.hpp>
#include <Lua.hpp>

void Sprite::registerClass()
{
    Lua::getState().new_usertype<Sprite>("Sprite",
                                         sol::constructors<Sprite()>(),
                                         "getPosition", [](Sprite& sprite) { return std::make_tuple(sprite.getPosition().x, sprite.getPosition().y); },
                                         "setPosition", &Sprite::setPosition,
                                         "getSize", &Sprite::getSize,
                                         "setSize", &Sprite::setSize,
                                         "getTexture", &Sprite::getTexture,
                                         "setTexture", &Sprite::setTexture
    );
}

Sprite::Sprite() :
    Drawable<Sprite>()
{
    if(!m_renderDetails.m_initialized)
    {
        GLuint& vao = m_renderDetails.m_vao;
        GLuint vbo;
        GLfloat vertices[] =
        {   // Vertex  // Texcoord
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(vao);
        //Position
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        //Texcoord
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_renderDetails.m_shader.loadFromMemory( // VERTEX SHADER
        R"(
        #version 330 core
        layout (location = 0) in vec2 vertex;
        layout (location = 1) in vec2 texCoord;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
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

Sprite::Sprite(const Sprite& other)
{
    static_cast<Transformable>(*this) = static_cast<Transformable>(other);
    m_texture = other.m_texture;
}

Sprite& Sprite::operator =(const Sprite& other)
{
    if(this != &other)
    {
        static_cast<Transformable>(*this) = static_cast<Transformable>(other);
        m_texture = other.m_texture;
    }
    return *this;
}

Sprite::Sprite(Sprite&& other)
{
    static_cast<Transformable>(*this) = std::move(static_cast<Transformable>(other));
    m_texture = other.m_texture;
}

Sprite& Sprite::operator =(Sprite&& other)
{
    if(this != &other)
    {
        static_cast<Transformable>(*this) = std::move(static_cast<Transformable>(other));
        m_texture = other.m_texture;
    }
    return *this;
}

void Sprite::setTexture(const Texture &texture)
{
    m_texture = texture;
}

const Texture& Sprite::getTexture()
{
    return m_texture;
}

void Sprite::setPosition(const glm::vec2& position)
{
    translate(position);
}

const glm::vec2& Sprite::getPosition()
{
    return m_translation;
}

void Sprite::setSize(const glm::vec2& size)
{
    scale(size.x, size.y);
}

const glm::vec2& Sprite::getSize()
{
    return m_scale;
}

void Sprite::draw(Window &)
{
    getShader().setMatrix4("model", getModel());
    glActiveTexture(GL_TEXTURE0);
    m_texture.bind();
    glBindVertexArray(m_renderDetails.m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
