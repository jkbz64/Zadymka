#include <Graphics/Sprite.hpp>
#include <Lua.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

Shader& Sprite::getDefaultShader()
{
    static Shader shader = Shader(
    R"(
    #version 330 core
    layout (location = 0) in vec2 vertex;
    layout (location = 1) in vec2 tCoord;
    out vec2 texCoord;
    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;
    void main()
    {
        gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
        texCoord = vec2(tCoord.xy);
    }
    )",
    R"(
    #version 330 core
    out vec4 FragColor;
    in vec2 texCoord;
    uniform sampler2D texture1;
    uniform vec4 color;
    void main()
    {
        FragColor = texture(texture1, texCoord);
    }
    )");
    shader.setInteger("texture1", 0);
    return shader;
}

Sprite::Sprite()
{
    m_color = Color(255, 255, 255, 255);
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

GLuint Sprite::update()
{
    static GLuint vao = 0;
    if(vao == 0)
    {
        GLfloat vertices[] =
        {   // Vertex  // Texcoord
            0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f,
        };
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    return vao;
}

void Sprite::draw(const Shader& shader)
{
    shader.setMatrix4("model", getModel());
    shader.setVector4f("color", m_color.normalized());
    glActiveTexture(GL_TEXTURE0);
    m_texture.bind();
    glBindVertexArray(update());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
