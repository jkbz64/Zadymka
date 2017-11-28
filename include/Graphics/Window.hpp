#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <Lua.hpp>
#include <Graphics/glad/glad.h>
#include <Graphics/Drawable.hpp>
#include <Graphics/RenderTarget.hpp>


class Window : public RenderTarget
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
    virtual void clear(unsigned int, unsigned int, unsigned int, unsigned int = 255u) override;
    virtual void draw(Drawable&, const Shader& = Shader()) override;
    virtual void display() override;

    void setTitle(const std::string&);
    void setSize(unsigned int, unsigned int);
    const Camera& getCamera();
    void setCamera(const Camera&);
protected:
    //Window
    struct DestroyGLFWWindow
    {
        void operator()(GLFWwindow* ptr)
        {
            glfwDestroyWindow(ptr);
        }
    };
    std::unique_ptr<GLFWwindow, DestroyGLFWWindow> m_window{nullptr};
    bool m_isOpen;
    //Window details
    unsigned int m_width;
    unsigned int m_height;
    std::string m_title;
    Style m_style;
    //Camera
    Camera m_camera;
    bool m_viewChanged;
    //Callbacks
    void onCreate();
    void onResize();
    sol::function m_onOpen;
    sol::function m_onResize;
    sol::function m_onClose;
};

#endif
