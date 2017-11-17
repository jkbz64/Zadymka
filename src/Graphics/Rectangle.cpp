#include <Graphics/Rectangle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Lua.hpp>
#include <Graphics/Window.hpp>

void Rectangle::registerClass()
{
    Lua::getState().new_usertype<Rectangle>("Rectangle",
                                            sol::constructors<Rectangle(unsigned int, unsigned int)>(),
                                            "getPosition", &Rectangle::getPosition,
                                            "setPosition", &Rectangle::setPosition,
                                            "getSize", &Rectangle::getSize,
                                            "setSize", &Rectangle::setSize
    );
}

Rectangle::Rectangle() :
    Drawable<Rectangle>(),
    m_colorChanged(true),
    m_color(Color::Black)
{
    if(!m_renderDetails.m_initialized)
    {
        GLuint& vao = m_renderDetails.m_vao;
        GLuint& vVBO = m_renderDetails.m_verticesVBO;
        GLfloat vertices[] =
        {   // Vertex
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
        };
        glGenBuffers(1, &vVBO);
        glBindBuffer(GL_ARRAY_BUFFER, vVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        GLuint& cVBO = m_renderDetails.m_colorVBO;
        GLfloat color[] =
        {
            1.f, 0.f, 0.f, 1.f,
            1.f, 0.f, 0.f, 1.f,
            1.f, 0.f, 0.f, 1.f,
            1.f, 0.f, 0.f, 1.f,
            1.f, 0.f, 0.f, 1.f,
            1.f, 0.f, 0.f, 1.f,
        };

        glGenBuffers(1, &cVBO);
        glBindBuffer(GL_ARRAY_BUFFER, cVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STREAM_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vVBO);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, cVBO);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_renderDetails.m_shader.loadFromMemory( // VERTEX SHADER
        R"(
        #version 330 core
        layout (location = 0) in vec2 vertex;
        layout (location = 1) in vec4 vcolor;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        out vec4 oColor;
        void main()
        {
            gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
            oColor = vcolor;
        }
        )", // FRAGMENT SHADER
        R"(
        #version 330 core
        out vec4 FragColor;
        in vec4 oColor;
        void main()
        {
            FragColor = oColor;
        }
        )");
        m_renderDetails.m_initialized = true;

    }
}

Rectangle::Rectangle(unsigned int width, unsigned int height) :
    Rectangle()
{
    setSize(glm::vec2(width, height));
}

Rectangle::Rectangle(const Rectangle &other)
{
    static_cast<Transformable>(*this) = static_cast<Transformable>(other);
}

Rectangle& Rectangle::operator =(const Rectangle& other)
{
    if(this != &other)
        static_cast<Transformable>(*this) = static_cast<Transformable>(other);
    return *this;
}

Rectangle::Rectangle(Rectangle&& other)
{
    static_cast<Transformable>(*this) = std::move(static_cast<Transformable>(other));
}

Rectangle& Rectangle::operator =(Rectangle&& other)
{
    if(this != &other)
        static_cast<Transformable>(*this) = std::move(static_cast<Transformable>(other));
    return *this;
}

void Rectangle::setPosition(const glm::vec2 &position)
{
    translate(position);
}

const glm::vec2& Rectangle::getPosition()
{
    return m_translation;
}

void Rectangle::setSize(const glm::vec2 &size)
{
    scale(size.x, size.y);
}

const glm::vec2& Rectangle::getSize()
{
    return m_scale;
}

void Rectangle::setColor(const Color &color)
{
    m_color = color;
}

const Color& Rectangle::getColor()
{
    return m_color;
}

void Rectangle::draw(Window &window)
{
    getShader().setMatrix4("model", getModel());
    glBindBuffer(GL_ARRAY_BUFFER, m_renderDetails.m_colorVBO);
    std::array<float, 4> c = m_color.normalized();
    GLfloat color[] = {
        c[0], c[1], c[2], c[3],
        c[0], c[1], c[2], c[3],
        c[0], c[1], c[2], c[3],
        c[0], c[1], c[2], c[3],
        c[0], c[1], c[2], c[3],
        c[0], c[1], c[2], c[3],
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), NULL, GL_STREAM_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STREAM_DRAW);
    glBindVertexArray(m_renderDetails.m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
