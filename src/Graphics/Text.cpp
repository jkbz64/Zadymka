#include <Graphics/Text.hpp>
#include <Graphics/Glyph.hpp>
#include <Graphics/Font.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Lua.hpp>

void Text::registerClass()
{
    Lua::getState().new_usertype<Text>("Text",
                                       sol::constructors<Text(), Text(Font&)>(),
                                       "setString", &Text::setString,
                                       "getString", &Text::getString,
                                       "setFont", &Text::setFont,
                                       "setCharacterSize", &Text::setCharacterSize,
                                       "getCharacterSize", &Text::getCharacterSize,
                                       "setColor", &Text::setColor,
                                       "getColor", &Text::getColor
                                       );
}

Text::Text() :
    Drawable<Text>()
{
    if(!m_renderDetails.m_initialized)
    {
        GLuint& vao = m_renderDetails.m_vao;
        GLuint& vVBO = m_renderDetails.m_verticesVBO;
        glGenBuffers(1, &vVBO);
        glBindBuffer(GL_ARRAY_BUFFER, vVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_renderDetails.m_shader.loadFromMemory( // VERTEX SHADER
        R"(
        #version 330 core
        layout (location = 0) in vec4 vertex;
        layout (std140) uniform Camera {
            mat4 view;
            mat4 projection;
        };
        uniform vec4 textColor;
        out vec2 TexCoords;
        out vec4 oTextColor;
        void main()
        {
            gl_Position = projection * view * vec4(vertex.x, vertex.y * -1, 0.0, 1.0);
            TexCoords = vertex.zw;
            oTextColor = textColor;
        }
        )", // FRAGMENT SHADER
        R"(
        #version 330 core
        in vec2 TexCoords;
        in vec4 oTextColor;
        out vec4 FragColor;

        uniform sampler2D texture1;
        void main()
        {
            vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture1, TexCoords).r);
            FragColor = oTextColor * sampled;
        }
        )");

        m_renderDetails.m_initialized = true;
    }
    setColor(Color::Black);
    setCharacterSize(48);
}

Text::Text(Font &font) :
    Text()
{
    m_font = &font;
}

void Text::setFont(Font *font)
{
    m_font = font;
}

void Text::setString(const std::string& str)
{
    m_text = str;
}

const std::string& Text::getString()
{
    return m_text;
}

void Text::setPosition(const glm::vec2& pos)
{
    translate(glm::vec2(pos.x, -pos.y));
}

const glm::vec2& Text::getPosition()
{
    return m_translation;
}

void Text::setCharacterSize(unsigned int charSize)
{
    m_characterSize = charSize;
    scale(1.f, static_cast<float>(m_characterSize) / 48.f);
}

unsigned int Text::getCharacterSize()
{
    return m_characterSize;
}

void Text::draw(Window &w)
{
    if(m_font)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(m_renderDetails.m_vao);
        m_renderDetails.m_shader.setVector4f("textColor", glm::vec4(m_colorArray[0], m_colorArray[1], m_colorArray[2], m_colorArray[3]));

        glm::vec2 m_pos = m_translation;
        m_pos.y -= 48.f;
        float scale = m_scale.y;
        std::string::const_iterator c;
        for (c = m_text.begin(); c != m_text.end(); c++)
        {
            Glyph ch = m_font->getGlyph(*c);
            GLfloat xpos = m_pos.x + ch.m_bearing.x * scale;
            GLfloat ypos = m_pos.y - (ch.m_size.y - ch.m_bearing.y) * scale;
            GLfloat w = ch.m_size.x * scale;
            GLfloat h = ch.m_size.y * scale;
            GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
            };
            glBindTexture(GL_TEXTURE_2D, ch.m_textureID);
            glBindBuffer(GL_ARRAY_BUFFER, m_renderDetails.m_verticesVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            m_pos.x += (ch.m_advance >> 6) * scale;
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
