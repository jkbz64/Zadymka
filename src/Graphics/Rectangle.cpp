#include <Graphics/Rectangle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Lua.hpp>

void Rectangle::registerClass()
{
    Lua::getState().new_usertype<Rectangle>("Rectangle",
                                            sol::constructors<Rectangle(unsigned int, unsigned int)>(),
                                            sol::base_classes, sol::bases<Transformable>()
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
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_renderDetails.m_shader.loadFromMemory(
        R"(
        #version 330 core
        layout (location = 0) in vec4 vertex;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
        }
        )",
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
    setSize(width, height);
}

#include <Graphics/Window.hpp>
#include <iostream>

void Rectangle::draw(Window &window)
{
    Shader& shader = m_renderDetails.m_shader.use();
    auto camera = window.getCamera();
    shader.setMatrix4("view", camera.getView());
    shader.setMatrix4("projection", camera.getProjection());
    shader.setMatrix4("model", getModel());
    glBindVertexArray(m_renderDetails.m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
