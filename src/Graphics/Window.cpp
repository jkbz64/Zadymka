#include <Graphics/Window.hpp>
#include <Graphics/Drawable.hpp>
#include <iostream>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/Font.hpp>

namespace
{
    template <typename T>
    constexpr float normalize(T value)
    {
      return value < 0 ? 0 : static_cast<float>(value) / 255;
    }
}

void Window::registerClass()
{
    Lua::getState().new_usertype<Window>("Window",
                             "new", sol::no_constructor,
                             "setTitle", &Window::setTitle,
                             "getSize", [](Window& window) { return std::make_tuple(window.m_width, window.m_height); },
                             "setSize", &Window::setSize,
                             "onOpen", &Window::m_onOpen,
                             "onResize", &Window::m_onResize,
                             "onClose", &Window::m_onClose,
                             //Draw
                             "draw", sol::overload(&Window::draw<Rectangle>,
                                                  &Window::draw<Sprite>
                                                   ),
                             "drawRect", &Window::drawRect,
                             "drawText", &Window::drawText/*
                             "drawRect", &Window::drawRect,
                             "drawSprite", &Window::drawSprite*/
    );
}

Window::Window() :
    m_isOpen(false),
    m_style(Window::Style::Windowed),
    m_renderCache()
{
    if(!glfwInit())
    {
        std::cerr << "Failed to load glfw. Aborting\n";
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_renderCache.m_viewChanged = false;
    sol::tie(m_onOpen, m_onClose, m_onResize) = Lua::getState().script(R"(return function() end,
                                                                                 function() end,
                                                                                 function() end)");
}

GLFWwindow* Window::getNativeWindow()
{
    return m_window.get();
}

void Window::create(unsigned int w, unsigned int h, const std::string& title, const Style& style = Window::Style::Windowed)
{
    if(w == 0 || h == 0)
    {
        m_isOpen = false;
        throw std::logic_error("Window width nor height cannot be 0");
    }

    m_width = w;
    m_height = h;
    m_title = title;
    m_style = style;

    switch(m_style)
    {
    case Style::Windowed:
        m_window.reset(glfwCreateWindow(m_width, m_height, title.c_str(), NULL, NULL));
        break;
    case Style::Fullscreen:
        m_window.reset(glfwCreateWindow(m_width, m_height, title.c_str(), glfwGetPrimaryMonitor(), NULL));
        break;
    case Style::FullscreenWindowed:
        auto monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        m_window.reset(glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, NULL));
        break;
    }

    m_isOpen = true;
    glfwMakeContextCurrent(getNativeWindow());
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSetWindowUserPointer(getNativeWindow(), this);
    glfwSetFramebufferSizeCallback(getNativeWindow(), [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        Window* w = (Window*)glfwGetWindowUserPointer(window);
        w->m_onResize.call(width, height);
    });

    if(m_renderCache.m_cameraUBO == 0)
    {
        //Init camera UBO
        GLuint bindingPoint = 1;
        glGenBuffers(1, &m_renderCache.m_cameraUBO);
        glBindBuffer(GL_UNIFORM_BUFFER, m_renderCache.m_cameraUBO);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, NULL, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(m_camera.getView()));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(m_camera.getProjection()));
        glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_renderCache.m_cameraUBO);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    m_onOpen.call();
}

bool Window::isOpen()
{
    if(m_window)
        return !glfwWindowShouldClose(m_window.get()) && m_isOpen;
    else
        return false;
}


void Window::clear(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(normalize(r), normalize(g), normalize(b), normalize(a));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::display()
{
    glfwSwapBuffers(getNativeWindow());
    glfwPollEvents();
}


void Window::close()
{
    if(m_isOpen)
    {
        if(m_onClose.valid())
            m_onClose.call();
        m_isOpen = false;
    }
}

void Window::setTitle(const std::string& title)
{
    m_title = title;
    if(m_isOpen)
        glfwSetWindowTitle(getNativeWindow(), m_title.c_str());
}


void Window::setSize(unsigned int width, unsigned int height)
{
    if(width == 0 || height == 0)
        return;

    m_width = width;
    m_height = height;
    if(m_isOpen)
        glfwSetWindowSize(getNativeWindow(), m_width, m_height);
}

void Window::setCamera(const Camera& camera)
{
    m_camera = camera;
    m_renderCache.m_viewChanged = true;
}

const Camera& Window::getCamera()
{
    return m_camera;
}

void Window::drawRect(float x, float y, int w, int h, int r = 0, int g = 0, int b = 0, int a = 255)
{
    Rectangle rect(w, h);
    rect.setPosition(glm::vec2(x, y));
    rect.setColor({r, g, b, a});
    draw(rect);
}

void Window::drawSprite(const std::string& textureName, float x, float y, int w, int h)
{
    static std::unordered_map<std::string, Texture> cachedTextures;
    if(cachedTextures.find(textureName) == std::end(cachedTextures))
    {
        auto& texture = cachedTextures[textureName];
        if(!texture.loadFromFile("textures/" + textureName))
        {
            cachedTextures.erase(cachedTextures.find(textureName));
            std::cerr << "Failed to load texture " << textureName << '\n';
            return;
        }
    }
    Texture texture = cachedTextures[textureName];
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(glm::vec2(x, y));
    sprite.setSize(glm::vec2(w, h));
    draw(sprite);
}

void Window::drawText(const std::string& str, float x, float y, const std::string& fontName, unsigned int charSize)
{
    static std::unordered_map<std::string, Font> cachedFonts;
    if(cachedFonts.find(fontName) == std::end(cachedFonts))
    {
        auto& font = cachedFonts[fontName];
        if(!font.loadFromFile("fonts/" + fontName))
        {
            cachedFonts.erase(cachedFonts.find(fontName));
            std::cerr << "Failed to load font " + fontName << '\n';
            return;
        }
    }
    Font& font = cachedFonts[fontName];
    Text text;
    text.setFont(&font);
    text.setPosition(glm::vec2(x, y));
    text.setString(str);
    draw(text);
}
