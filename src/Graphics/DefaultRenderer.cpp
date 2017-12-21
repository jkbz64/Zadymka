#include <Graphics/DefaultRenderer.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/glad/glad.h>
#include <GLFW/glfw3.h>

DefaultRenderer::DefaultRenderer(Camera& camera) :
        m_camera(camera)
{

}

DefaultRenderer::~DefaultRenderer() = default;

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

#include <Graphics/Tilemap.hpp>
#include <Graphics/RenderTexture.hpp>

void DefaultRenderer::render(Tilemap &tilemap)
{
    for(auto& layer : tilemap.getLayers())
    {
        std::map<unsigned int, Texture> cachedTiles;
        if(layer.m_needUpdate)
        {
            auto& tileset = tilemap.getTileset();
            const auto& tileSize = tilemap.getTileSize();
            RenderTexture tilesetFramebuffer;
            tilesetFramebuffer.create(tileset.getSize().x, tileset.getSize().y);
            tilesetFramebuffer.clear(255, 255, 255, 0);
            tilesetFramebuffer.drawTexture(tilemap.getTileset(), 0, 0);
            tilesetFramebuffer.display();
            RenderTexture layerTexture;
            layerTexture.create(layer.m_size.x * tileSize.x, layer.m_size.y * tileSize.y);
            layerTexture.clear(255, 255, 255, 0);
            
            for(auto row = 0u; row < layer.m_size.y; row++)
            {
                for(auto column = 0u; column < layer.m_size.x; column++)
                {
                    const auto tileN = column + row * layer.m_size.x;
                    const auto& tileID = layer.m_data[tileN];
                    if(tileID != 0)
                    {
                        if(cachedTiles.find(tileID) == std::end(cachedTiles))
                        {
                            glBindFramebuffer(GL_READ_FRAMEBUFFER, tilesetFramebuffer.getID());
                            Texture tileTexture;
                            tileTexture.create(tileSize.x, tileSize.y);
                            tileTexture.bind();
                            glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                                             column * tileSize.x,
                                             (tileset.getSize().y - tileSize.y) - row * tileSize.y,
                                             tileSize.x, tileSize.y, 0);
                            glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
                            cachedTiles[tileID] = std::move(tileTexture);
                        }
                        layerTexture.drawTexture(cachedTiles[tileID],
                                                 column * tileSize.x,
                                                 row * tileSize.y);
                    }
                }
            }
            
            layerTexture.display();
            // Make layer texture render texture
            layer.m_texture = layerTexture.getTexture();
            layer.m_needUpdate = false;
        }
        Sprite layerSprite;
        layerSprite.setTexture(layer.m_texture);
        render(layerSprite);
    }
}