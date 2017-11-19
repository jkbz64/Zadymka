#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <Lua.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/glad/glad.h>
#include <GLFW/glfw3.h>
#include <Graphics/Drawable.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void drawRect(float, float, int, int, int, int, int, int);
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
        GLuint m_cameraUBO{0};
        bool m_viewChanged;
    } m_renderCache;
};

template<class T>
inline void Window::draw(Drawable<T>& drawable)
{
    Shader& shader = drawable.m_renderDetails.m_shader.use();
    if(!drawable.m_renderDetails.m_cameraSet)
    {
        GLuint blockIndex = glGetUniformBlockIndex(shader.getID(), "Camera");
        glUniformBlockBinding(shader.getID(), blockIndex, 1);
        drawable.m_renderDetails.m_cameraSet = true;
    }
    if(m_renderCache.m_viewChanged)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_renderCache.m_cameraUBO);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(m_camera.getView()));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(m_camera.getProjection()));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        m_renderCache.m_viewChanged = false;
    }
    drawable.draw(*this);
}

#endif
