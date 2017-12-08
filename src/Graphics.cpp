#include <Graphics.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Rectangle.hpp>
#include <Graphics/Sprite.hpp>
#include <Graphics/Font.hpp>
#include <Graphics/Text.hpp>
#include <Graphics/RenderTexture.hpp>
#include <Graphics/Window.hpp>
#include <sol/state_view.hpp>
#include <GLFW/glfw3.h>

void draw(const Rectangle&);

sol::table Graphics::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module["init"] = &Graphics::init;
    module["deinit"] = &Graphics::deinit;
    module.new_usertype<Camera>("Camera",
                                sol::constructors<Camera(), Camera(const Camera&)>(),
                                "setCenter", &Camera::setCenter,
                                "getCenter", &Camera::getCenter,
                                "setSize", &Camera::setSize,
                                "getSize", &Camera::getSize,
                                "move", &Camera::move
    );
    sol::table styles = lua.create_table_with(
            "Windowed", 0,
            "Fullscreen", 1,
            "FullscreenWindowed", 2
    );
    module.new_usertype<Window>("Window", sol::constructors<Window()>(),
                                "Style", sol::var(styles),
                                "create", &Window::create,
                                "isOpen", &Window::isOpen,
                                "close", &Window::close,
                                "setTitle", &Window::setTitle,
                                "getSize", &Window::getSize,
                                "setSize", &Window::setSize,
                                "getCamera", &Window::getCamera,
                                "setCamera", &Window::setCamera,
                                "draw", sol::overload(
                                    static_cast<void(Window::*)(Drawable&)>(&Window::draw),
                                    static_cast<void(Window::*)(Drawable&, const Shader&)>(&Window::draw)
                                ),
                                "drawRect", &Window::drawRect,
                                "drawText", &Window::drawText,
                                "drawSprite", &Window::drawSprite,
                                "clear", &Window::clear,
                                "display", &Window::display
    );
    module.new_usertype<Texture>("Texture",
                                 sol::constructors<Texture(), Texture(const Texture&)>(),
                                 "create", &Texture::create,
                                 "getID", &Texture::getID,
                                 "bind", &Texture::bind,
                                 "loadFromFile", &Texture::loadFromFile,
                                 "loadFromMemory", &Texture::loadFromMemory,
                                 "getSize", &Texture::getSize
    );
    module.new_usertype<Shader>("Shader", sol::constructors<Shader(), Shader(const std::string&, const std::string&)>(),
                                "use", &Shader::use,
                                "getID", &Shader::getID,
                                "isLoaded", &Shader::isLoaded,
                                "loadFromFile", sol::overload(
                                      static_cast<bool(Shader::*)(const std::string&, const std::string&, const std::string&)>(&Shader::loadFromFile),
                                      [](Shader& shader, const std::string& vs, const std::string& fs)
                                      {
                                          return shader.loadFromFile(vs, fs);
                                      }
                                ),
                                "loadFromMemory", sol::overload(
                                    static_cast<bool(Shader::*)(const std::string&, const std::string&, const std::string&)>(&Shader::loadFromMemory),
                                    [](Shader& shader, const std::string& vs, const std::string& fs)
                                    {
                                        return shader.loadFromMemory(vs, fs);
                                    }
                                ),
                                "setFloat", &Shader::setFloat,
                                "setInteger", &Shader::setInteger,
                                "setVector2f", &Shader::setVector2f,
                                "setVector3f", &Shader::setVector3f,
                                "setMatrix4", &Shader::setMatrix4
    );
    module.new_usertype<Color>("Color", sol::constructors<Color(), Color(unsigned int, unsigned int, unsigned int, unsigned int), Color(const Color&)>(),
                               "r", &Color::m_r,
                               "g", &Color::m_g,
                               "b", &Color::m_b,
                               "a", &Color::m_a,
                               "normalized", &Color::normalized
    );
    module.new_usertype<Drawable>("Drawable", "new", sol::no_constructor);
    module.new_usertype<Rectangle>("Rectangle",
                                   sol::constructors<Rectangle(unsigned int, unsigned int)>(),
                                   "getPosition", &Rectangle::getPosition,
                                   "setPosition", &Rectangle::setPosition,
                                   "getSize", &Rectangle::getSize,
                                   "setSize", &Rectangle::setSize,
                                   "getColor", &Rectangle::getColor,
                                   "setColor", &Rectangle::setColor,
                                   sol::base_classes, sol::bases<Drawable>()
    );
    module.new_usertype<Sprite>("Sprite",
                                sol::constructors<Sprite()>(),
                                "getPosition", &Sprite::getPosition,
                                "setPosition", &Sprite::setPosition,
                                "getSize", &Sprite::getSize,
                                "setSize", &Sprite::setSize,
                                "getTexture", &Sprite::getTexture,
                                "setTexture", &Sprite::setTexture,
                                sol::base_classes, sol::bases<Drawable>()
    );
    module.new_usertype<Font>("Font",
                              sol::constructors<Font(), Font(const std::string&)>(),
                              "loadFromFile", &Font::loadFromFile
    );
    module.new_usertype<Text>("Text",
                              sol::constructors<Text(), Text(Font&)>(),
                              "setPosition", &Text::setPosition,
                              "getPosition", &Text::getPosition,
                              "setString", &Text::setString,
                              "getString", &Text::getString,
                              "setFont", &Text::setFont,
                              "setCharacterSize", &Text::setCharacterSize,
                              "getCharacterSize", &Text::getCharacterSize,
                              "setColor", &Text::setColor,
                              "getColor", &Text::getColor,
                              sol::base_classes, sol::bases<Drawable>()
    );
    module.new_usertype<RenderTexture>("RenderTexture",
                                       sol::constructors<RenderTexture()>(),
                                       "create", &RenderTexture::create,
                                       "getTexture", &RenderTexture::getTexture,
                                       "draw", sol::overload(
                                           static_cast<void(RenderTexture::*)(Drawable&)>(&RenderTexture::draw),
                                           static_cast<void(RenderTexture::*)(Drawable&, const Shader&)>(&RenderTexture::draw)
                                       ),
                                       "drawRect", &RenderTexture::drawRect,
                                       "drawSprite", &RenderTexture::drawSprite,
                                       "drawText", &RenderTexture::drawText,
                                       "clear", &RenderTexture::clear,
                                       "display", &RenderTexture::display
    );
    return module;
}

bool Graphics::init(sol::this_state L)
{
    if(!glfwInit())
        return false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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