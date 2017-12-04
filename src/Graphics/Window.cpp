#include <Graphics/Window.hpp>
#include <Graphics/Drawable.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/Font.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <Graphics/RenderTexture.hpp>
#include <Lua.hpp>
#include <Input.hpp>

namespace
{
    template <typename T>
    constexpr float normalize(T value)
    {
      return value < 0 ? 0 : static_cast<float>(value) / 255.f;
    }
}

void Window::registerClass(sol::table module)
{
    module.new_usertype<Window>("Window", sol::constructors<Window()>(),
                             "create", [](Window& window, unsigned int width, unsigned int height, const std::string& title, int style)
                             {
                                 window.create(width, height, title, static_cast<Window::Style>(style));
                             },
                             "isOpen", &Window::isOpen,
                             "close", &Window::close,
                             "setTitle", &Window::setTitle,
                             "getSize", [](Window& window) { return glm::vec2(window.m_width, window.m_height); },
                             "setSize", &Window::setSize,
                             "onOpen", &Window::m_onOpen,
                             "onResize", &Window::m_onResize,
                             "onClose", &Window::m_onClose,
                             "setCamera", &Window::setCamera,
                             //Draw
                             "draw",
                             sol::overload(
                             [](Window& window, Drawable& drawable)
                             {
                                window.draw(drawable);
                             },
                             &Window::draw
                             ),
                             "drawRect", &Window::drawRect,
                             "drawText", &Window::drawText,
                             "drawSprite", &Window::drawSprite,
                             "clear", &Window::clear,
                             "display", &Window::display
    );
}

Window::Window() :
    RenderTarget(),
    m_isOpen(false),
    m_style(Window::Style::Windowed)
{
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
    Input::setWindow(getNativeWindow());
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
