#include <Graphics/Rectangle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Lua.hpp>
#include <Graphics/Window.hpp>

void Rectangle::registerClass()
{
    Lua::getState().new_usertype<Rectangle>("Rectangle",
                                            sol::constructors<Rectangle(unsigned int, unsigned int)>(),
                                            "getPosition", [](Rectangle& rect) { return std::make_tuple(rect.getSize().x, rect.getSize().y); },
                                            "setPosition", [](Rectangle& rect, float x, float y) { rect.setPosition(glm::vec2(x, y)); },
                                            "getSize", [](Rectangle& rect) { return std::make_tuple(rect.getSize().x, rect.getSize().y); },
                                            "setSize", [](Rectangle& rect, unsigned int w, unsigned int h) { rect.setSize(glm::vec2(w, h)); },
                                            "getColor", &Rectangle::getColor,
                                            "setColor", &Rectangle::setColor,
                                            sol::base_classes, sol::bases<Drawable>()
    );
}

Shader& Rectangle::getDefaultShader()
{
    static Shader shader = Shader(
    R"(
    #version 330 core
    layout (location = 0) in vec2 vertex;
    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;
    void main()
    {
        gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
    }
    )",
    R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec4 color;
    void main()
    {
        FragColor = color;
    }
    )");
    return shader;
}

Rectangle::Rectangle()
{

}

Rectangle::Rectangle(unsigned int width, unsigned int height) :
    Rectangle()
{
    setSize(glm::vec2(width, height));
}

Rectangle::Rectangle(const Rectangle &other) :
    Transformable(other)
{

}

Rectangle::Rectangle(Rectangle&& other) :
    Transformable(std::move(other))
{

}

Rectangle& Rectangle::operator =(const Rectangle& other)
{
    if(this != &other)
        static_cast<Transformable>(*this) = static_cast<Transformable>(other);
    return *this;
}

Rectangle& Rectangle::operator =(Rectangle&& other)
{
    if(this != &other)
        static_cast<Transformable>(*this) = std::move(static_cast<Transformable>(other));
    return *this;
}

void Rectangle::setPosition(const glm::vec2 &position)
{
    translate(glm::vec2(position.x, position.y));
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

const Color& Rectangle::getColor()
{
    return m_color;
}

void Rectangle::setColor(const Color& color)
{
    m_color = color;
}

GLuint Rectangle::update()
{
    static GLuint vao = 0;
    if(vao == 0)
    {
        GLfloat vertices[] =
        {   // Vertex  // Texcoord
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
        };
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    return vao;
}

void Rectangle::draw(const Shader& shader)
{
    shader.setMatrix4("model", getModel());
    shader.setVector4f("color", m_color.normalized());
    glBindVertexArray(update());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
