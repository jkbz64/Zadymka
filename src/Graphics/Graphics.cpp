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
