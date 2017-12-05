#include <Graphics/DefaultRenderer.hpp>
#include <Graphics/Shader.hpp>

DefaultRenderer::DefaultRenderer(Camera& camera) :
        Renderer(camera)
{

}

#include <Graphics/Rectangle.hpp>

void DefaultRenderer::render(Rectangle &rectangle)
{
    static Shader shader = Shader(R"(
        #version 330 core
        layout (location = 0) in vec2 vertex;
        uniform mat4 projection;
        uniform mat4 view;
        uniform mat4 model;
        void main()
        {
            gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
        }
        )",R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec4 color;
        void main()
        {
            FragColor = color;
        }
        )");
    shader.use();
    shader.setMatrix4("projection", m_camera.getProjection());
    shader.setMatrix4("view", m_camera.getView());
    shader.setMatrix4("model", rectangle.getModel());
    shader.setVector4f("color", rectangle.getColor().normalized());
    
    static GLuint vao = 0;
    if(vao == 0)
    {
        GLfloat vertices[] =
                {   // Vertex
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
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

#include <Graphics/Sprite.hpp>

void DefaultRenderer::render(Sprite &sprite)
{
    static Shader shader = Shader(R"(
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
        )", R"(
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
    shader.use();
    shader.setInteger("texture1", 0);
    shader.setMatrix4("projection", m_camera.getProjection());
    shader.setMatrix4("view", m_camera.getView());
    shader.setMatrix4("model", sprite.getModel());
    shader.setVector4f("color", sprite.getColor().normalized());
    
    glActiveTexture(GL_TEXTURE0);
    sprite.getTexture().bind();
    
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
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

#include <Graphics/Text.hpp>
#include <Graphics/Font.hpp>

void DefaultRenderer::render(Text &text)
{
    static Shader shader(R"(
    #version 330 core
    layout (location = 0) in vec4 vertex;
    uniform mat4 projection;
    uniform mat4 view;
    out vec2 TexCoords;
    out vec4 oTextColor;
    void main()
    {
        gl_Position = projection * view * vec4(vertex.x, vertex.y, 0.0, 1.0);
        TexCoords = vertex.zw;
    }
    )", // FRAGMENT SHADER
            R"(
    #version 330 core
    in vec2 TexCoords;
    in vec4 oTextColor;
    out vec4 FragColor;
    uniform vec4 color;
    uniform sampler2D texture1;
    void main()
    {
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture1, TexCoords).r) ;
        FragColor = color * sampled;
    }
    )");
    shader.use();
    shader.setInteger("texture1", 0);
    shader.setMatrix4("projection", m_camera.getProjection());
    shader.setMatrix4("view", m_camera.getView());
    shader.setVector4f("color", text.getColor().normalized());
    
    static GLuint vao = 0;
    static GLuint vbo = 0;
    if(vao == 0)
    {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    if(text.getFont())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(vao);
        
        glm::vec2 m_pos = text.getPosition();
        auto font = text.getFont();
        auto scale = static_cast<float>(text.getCharacterSize());
        std::string::const_iterator c;
        for (c = text.getString().begin(); c != text.getString().end(); ++c)
        {
            Glyph ch = font->getGlyph(*c);
            GLfloat xpos = m_pos.x + ch.m_bearing.x * scale;
            GLfloat ypos = m_pos.y - (ch.m_size.y - ch.m_bearing.y) * scale;
            GLfloat w = ch.m_size.x * scale;
            GLfloat h = ch.m_size.y * scale;
            GLfloat vertices[6][4] = {
                    { xpos,     ypos,           0.0, 0.0 },
                    { xpos,     ypos + h,       0.0, 1.0 },
                    { xpos + w, ypos + h,       1.0, 1.0 },
                    
                    { xpos,     ypos,           0.0, 0.0 },
                    { xpos + w, ypos + h,       1.0, 1.0 },
                    { xpos + w, ypos,           1.0, 0.0 }
            };
            glBindTexture(GL_TEXTURE_2D, ch.m_textureID);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, vertices, GL_DYNAMIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            m_pos.x += (ch.m_advance >> 6) * scale;
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
}

#include <Graphics/VertexArray.hpp>

void DefaultRenderer::render(VertexArray &array)
{
    static Shader shader = Shader(R"(
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
        )", R"(
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
    shader.use();
    shader.setInteger("texture1", 0);
    shader.setMatrix4("projection", m_camera.getProjection());
    shader.setMatrix4("view", m_camera.getView());
    if(!array.getVertexes().empty())
    {
        glActiveTexture(GL_TEXTURE0);
        array.getTexture().bind();
        shader.setMatrix4("model", array.getModel());
        static const GLenum modes[] = {GL_POINTS, GL_TRIANGLES, GL_TRIANGLES};
        GLenum mode = modes[static_cast<int>(array.getPrimitiveType())];
        glBindVertexArray(array.update());
        glDrawArrays(mode, 0, array.getVertexes().size());
        glBindVertexArray(0);
    }
}