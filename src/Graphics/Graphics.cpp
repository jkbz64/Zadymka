#include <Graphics/Graphics.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/RenderTexture.hpp>
#include <Graphics/VertexArray.hpp>
#include <Graphics/Window.hpp>

namespace
{

}

void Graphics::registerModule()
{
    Window::registerClass();
    Camera::registerClass();
    Texture::registerClass();
    Shader::registerClass();
    Lua::getState().new_usertype<Drawable>("Drawable", "new", sol::no_constructor);
    Rectangle::registerClass();
    Sprite::registerClass();
    Font::registerClass();
    Text::registerClass();
    RenderTexture::registerClass();
    VertexArray::registerClass();
}

bool Graphics::init()
{
    if(!glfwInit())
        return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return true;
}