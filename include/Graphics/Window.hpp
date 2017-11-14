#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <Lua.hpp>
#include <Graphics/Camera.hpp>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <Graphics/Drawable.hpp>


class Window
{
public:
    static void registerClass();
    enum class Style
    {
        Windowed,
        Fullscreen,
        FullscreenWindowed
    };
    Window();
    virtual ~Window() = default;
    GLFWwindow* getNativeWindow();
    void create(unsigned int, unsigned int, const std::string&, const Style&);
    bool isOpen();
    void close();

    void setTitle(const std::string&);
    void setSize(unsigned int, unsigned int);
    const Camera& getCamera();
    void setCamera(const Camera&);

    void clear(unsigned int, unsigned int, unsigned int, unsigned int = 255u);
    void display();

    template<class T>
    void draw(Drawable<T>&);
    void drawText(const std::string&, float, float, const std::string&, unsigned int);
    void drawSprite(float, float, int, int, const std::string&);
    void drawRect(float, float, int, int, int, int, int);
protected:
    struct DestroyGLFWWindow
    {
        void operator()(GLFWwindow* ptr)
        {
            glfwDestroyWindow(ptr);
        }
    };
    std::unique_ptr<GLFWwindow, DestroyGLFWWindow> m_window{nullptr};
    bool m_isOpen;
    unsigned int m_width;
    unsigned int m_height;
    std::string m_title;
    Style m_style;
    //Callbacks
    void onCreate();
    void onResize();
    sol::function m_onOpen;
    sol::function m_onResize;
    sol::function m_onClose;
    //Draw stuff
    Camera m_camera;
    struct RenderCache
    {
        bool m_viewChanged;
    } m_renderCache;
};

template<class T>
inline void Window::draw(Drawable<T>& drawable)
{
    drawable.draw(*this);
}

#endif
