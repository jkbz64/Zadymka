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

Rectangle::Rectangle(unsigned int width, unsigned int height) :
    Drawable<Rectangle>()
{
    if(!m_renderDetails.m_initialized)
    {
        GLuint& vao = m_renderDetails.m_vao;
        GLuint vbo;
        GLfloat vertices[] =
        {
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_renderDetails.m_shader.loadFromMemory( // VERTEX SHADER
        R"(
        #version 330 core
        layout (location = 0) in vec2 vertex;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
        }
        )", // FRAGMENT SHADER
        R"(
        #version 330 core
        out vec4 FragColor;

        in vec3 ourColor;

        void main()
        {
            FragColor = vec4(1.0, 0, 0, 1.0);
        }
        )");
        m_renderDetails.m_initialized = true;
    }
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

void Rectangle::draw(Window &window)
{
    getShader().setMatrix4("model", getModel());
    glBindVertexArray(m_renderDetails.m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
