#include <Graphics/Window.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Drawable.hpp>
#include <Input.hpp>
#include <Graphics/glad/glad.h>
#include <GLFW/glfw3.h>
#include <Graphics/DefaultRenderer.hpp>
#include <ImGui.hpp>

namespace
{
    template <typename T>
    constexpr float normalize(T value)
    {
      return value < 0 ? 0 : static_cast<float>(value) / 255.f;
    }
}

Window::Window() :
    RenderTarget(new DefaultRenderer(m_camera)),
    m_window(nullptr),
    m_isOpen(false),
    m_style(Window::Style::Windowed)
{

}

Window::~Window()
{
    Input::setWindow(nullptr);
    ImGUI::setWindow(nullptr);
    if(m_window)
        glfwDestroyWindow(getNativeWindow());
}

GLFWwindow* Window::getNativeWindow()
{
    return m_window;
}

void Window::create(unsigned int w, unsigned int h, const std::string& title, const Style& style = Window::Style::Windowed)
{
    if(w == 0 || h == 0)
    {
        m_isOpen = false;
        throw std::logic_error("Window width nor height cannot be 0");
    }

    m_size = glm::uvec2(w, h);
    m_title = title;
    m_style = style;
    
    if(m_window)
        glfwDestroyWindow(getNativeWindow());
    
    switch(m_style)
    {
    case Style::Windowed:
        m_window = glfwCreateWindow(m_size.x, m_size.y, title.c_str(), NULL, NULL);
        break;
    case Style::Fullscreen:
        m_window = glfwCreateWindow(m_size.x, m_size.y, title.c_str(), glfwGetPrimaryMonitor(), NULL);
        break;
    case Style::FullscreenWindowed:
        auto monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        m_window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, NULL);
        break;
    }

    m_isOpen = true;
    glfwMakeContextCurrent(getNativeWindow());
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSetWindowUserPointer(getNativeWindow(), this);
    glfwSetFramebufferSizeCallback(getNativeWindow(), [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });
    Input::setWindow(getNativeWindow());
    ImGUI::setWindow(getNativeWindow());
}

bool Window::isOpen()
{
    if(m_window)
        return !glfwWindowShouldClose(getNativeWindow()) && m_isOpen;
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
        m_isOpen = false;
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

    m_size = glm::uvec2(width, height);
    if(m_isOpen)
        glfwSetWindowSize(getNativeWindow(), m_size.x, m_size.y);
}

const glm::uvec2& Window::getSize()
{
    return m_size;
}
