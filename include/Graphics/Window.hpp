#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <Graphics/RenderTarget.hpp>

struct GLFWwindow;

class Window : public RenderTarget
{
public:
    static void registerClass(sol::table);
    enum class Style
    {
        Windowed,
        Fullscreen,
        FullscreenWindowed
    };
    Window();
    virtual ~Window();
    GLFWwindow* getNativeWindow();
    void create(unsigned int, unsigned int, const std::string&, const Style&);
    bool isOpen();
    void close();
    virtual void clear(unsigned int, unsigned int, unsigned int, unsigned int = 255u) override;
    virtual void display() override;

    void setTitle(const std::string&);
    void setSize(unsigned int, unsigned int);
    const glm::uvec2& getSize();
protected:
    //Window
    GLFWwindow* m_window;
    bool m_isOpen;
    //Window details
    glm::uvec2 m_size;
    std::string m_title;
    Style m_style;
    //Callbacks
    sol::function m_onOpen;
    sol::function m_onResize;
    sol::function m_onClose;
};

#endif
