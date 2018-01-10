#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <Graphics/RenderTarget.hpp>

struct GLFWwindow;

class Window : public RenderTarget
{
public:
    enum class Style
    {
        Windowed,
        Fullscreen,
        FullscreenWindowed
    };
    Window();
    virtual ~Window();
    GLFWwindow* getNativeWindow();
    void create(const glm::uvec2&, const std::string&, const Style& = Window::Style::Windowed);
    bool isOpen();
    void close();
    virtual void clear(unsigned int, unsigned int, unsigned int, unsigned int = 255u) override;
    virtual void display() override;

    const std::string& title() const;
    const glm::uvec2& size();
    void setTitle(const std::string&);
    void resize(const glm::uvec2& size);
    glm::vec2 mapToWorld(const glm::vec2&);
protected:
    friend class Graphics;
    GLFWwindow* m_window;
    bool m_isOpen;
    glm::uvec2 m_size;
    std::string m_title;
    Style m_style;
};

#endif
