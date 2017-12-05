#include <include/Graphics.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/RenderTexture.hpp>
#include <Graphics/VertexArray.hpp>
#include <Graphics/Window.hpp>
#include <sol/state_view.hpp>
#include <include/Lua.hpp>

void draw(const Rectangle&);

sol::table Graphics::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    Window::registerClass(module);
    Camera::registerClass(module);
    Texture::registerClass(module);
    Shader::registerClass(module);
    module.new_usertype<Drawable>("Drawable", "new", sol::no_constructor);
    Rectangle::registerClass(module);
    Sprite::registerClass(module);
    Font::registerClass(module);
    Text::registerClass(module);
    RenderTexture::registerClass(module);
    VertexArray::registerClass(module);
    return module;
}

bool Graphics::init()
{
    if(!glfwInit())
        return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    Lua::getState()["WindowStyle"] = Lua::getState().create_table_with(
            "Windowed", 0,
            "Fullscreen", 1,
            "FullscreenWindowed", 2
    );
    
    return true;
}

void Graphics::deinit()
{
    glfwTerminate();
}

extern "C" int luaopen_Zadymka_Graphics(lua_State* L)
{
    return sol::stack::call_lua(L, 1, Graphics::createModule);
}