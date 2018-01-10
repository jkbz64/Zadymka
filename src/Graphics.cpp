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

namespace
{
    template<class T>
    struct get_class;
    
    template<class T, class R>
    struct get_class<R T::*> { using type = T; };
    
    template<class T>
    struct get_argument_type;
    
    template<class R, class Arg, class T>   // Strip argument type to non-const, non-reference
    struct get_argument_type<R (T::*)(Arg)> { using argument_type = std::remove_const_t        <
                                                                    std::remove_reference_t    <
                                                                            Arg                >>; };
}

namespace sol
{
    template<typename F>
    auto readonly_getter(F f)
    {
        using C = typename get_class<F>::type;
        return sol::property([f](C& c)
        {
            return (c.*f)();
        });
    }
    
    template<typename F,
            typename VecType = typename get_argument_type<F>::argument_type,
            typename Val = typename VecType::value_type
    >
    auto vec_as_Ts(F f)
    {
        using C = typename get_class<F>::type;
        return [f](C& c, Val a, Val b)
        {
            return (c.*f)(VecType(a, b));
        };
    }
    
    template<typename F,
            typename VecType = typename get_argument_type<F>::argument_type,
            typename Val = typename VecType::value_type,
            typename std::enable_if_t<std::is_unsigned<Val>::value>
    > // Lua doesn't know about unsigned integers :(
    auto vec_as_Ts(F f)
    {
        using C = typename get_class<F>::type;
        return [f](C& c, int a, int b)
        {
            return (c.*f)(VecType(a, b));
        };
    }
}

sol::table Graphics::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module["init"] = &Graphics::init;
    module["deinit"] = &Graphics::deinit;
    module.new_usertype<Camera>("Camera",
                                sol::constructors<Camera(), Camera(const Camera &)>(),
                                "center", sol::readonly_getter(&Camera::center),
                                "size", sol::readonly_getter(&Camera::size),
                                "setCenter", sol::vec_as_Ts(&Camera::setCenter),
                                "setSize", sol::vec_as_Ts(&Camera::setSize),
                                "move", sol::vec_as_Ts(&Camera::move)
    );
    sol::table styles = lua.create_table_with(
            "Windowed", 0,
            "Fullscreen", 1,
            "FullscreenWindowed", 2
    );
    module.new_usertype<Window>("Window", sol::constructors<Window()>(),
                                "Style", sol::var(styles),
                                "title", sol::readonly_getter(&Window::title),
                                "size", sol::readonly_getter(&Window::size),
                                "camera", &Window::m_camera,
                                "create",
                                sol::overload(
                                        [](Window& window, int w, int h, const std::string& t)
                                        {
                                            window.create(glm::uvec2(w, h), t);
                                        },
                                        [](Window& window, int w, int h, const std::string& t, const Window::Style& style)
                                        {
                                            window.create(glm::uvec2(w, h), t, style);
                                        }
                                ),
                                "isOpen", &Window::isOpen,
                                "close", &Window::close,
                                "setTitle", &Window::setTitle,
                                "resize", sol::vec_as_Ts(&Window::resize),
                                "draw",
                                sol::overload(
                                        static_cast<void (Window::*)(Drawable &)>(&Window::draw),
                                        static_cast<void (Window::*)(Drawable &, const Shader &)>(&Window::draw)
                                ),
                                "drawRect", &Window::drawRect,
                                "drawText", &Window::drawText,
                                "drawSprite", &Window::drawSprite,
                                "drawTexture", &Window::drawTexture,
                                "clear", &Window::clear,
                                "display", &Window::display,
                                "mapToWorld",
                                sol::overload(
                                        sol::vec_as_Ts(&Window::mapToWorld),
                                        &Window::mapToWorld
                                )
    );
    module.new_usertype<Texture>("Texture",
                                 sol::constructors<Texture(), Texture(const Texture &)>(),
                                 "LINEAR", sol::var(GL_LINEAR),
                                 "NEAREST", sol::var(GL_NEAREST),
                                 "CLAMP", sol::var(GL_CLAMP),
                                 "REPEAT", sol::var(GL_REPEAT),
                                 "ID", sol::property(&Texture::getID),
                                 "size", sol::readonly_getter(&Texture::size),
                                 "create", &Texture::create,
                                 "bind", &Texture::bind,
                                 "loadFromMemory", &Texture::loadFromMemory,
                                 "loadFromFile", &Texture::loadFromFile,
                                 "setFilter", &Texture::setFilter,
                                 "getFilter", [](const Texture& texture) { return std::make_tuple(texture.m_filterMin, texture.m_filterMax); },
                                 "setWrap", &Texture::setWrap,
                                 "getWrap", [](const Texture& texture) { return std::make_tuple(texture.m_wrapS, texture.m_wrapT); },
                                 "subimage", [](Texture& texture, float x, float y, int w, int h) { return texture.subimage(glm::ivec2(x, y), glm::uvec2(w, h)); }
    );
    module.new_usertype<Shader>("Shader",
                                sol::constructors<Shader(), Shader(const std::string &, const std::string &)>(),
                                "use", &Shader::use,
                                "getID", &Shader::getID,
                                "isLoaded", &Shader::isLoaded,
                                "loadFromFile",
                                sol::overload(
                                        static_cast<bool (Shader::*)(const std::string &, const std::string &,
                                                                     const std::string &)>(&Shader::loadFromFile),
                                        [](Shader &shader, const std::string &vs, const std::string &fs)
                                        {
                                            return shader.loadFromFile(vs, fs);
                                        }
                                ),
                                "loadFromMemory",
                                sol::overload(
                                        static_cast<bool (Shader::*)(const std::string &, const std::string &,
                                                                     const std::string &)>(&Shader::loadFromMemory),
                                        [](Shader &shader, const std::string &vs, const std::string &fs)
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
    module.new_usertype<Color>("Color", sol::constructors<Color(), Color(unsigned int, unsigned int, unsigned int,
                                                                         unsigned int), Color(const Color &)>(),
                               "r", &Color::m_r,
                               "g", &Color::m_g,
                               "b", &Color::m_b,
                               "a", &Color::m_a,
                               "normalized", &Color::normalized
    );
    module.new_usertype<Drawable>("Drawable", "new", sol::no_constructor);
    module.new_usertype<Rectangle>("Rectangle",
                                   sol::constructors<Rectangle(unsigned int, unsigned int)>(),
                                   "position", sol::readonly_getter(&Rectangle::position),
                                   "size", sol::readonly_getter(&Rectangle::size),
                                   "color", sol::property(&Rectangle::m_color, &Rectangle::setColor),
                                   "setPosition", sol::vec_as_Ts(&Rectangle::setPosition),
                                   "setSize", sol::vec_as_Ts(&Rectangle::setSize),
                                   sol::base_classes, sol::bases<Drawable>()
    );
    module.new_usertype<Sprite>("Sprite",
                                sol::constructors<Sprite()>(),
                                "position", sol::readonly_getter(&Sprite::position),
                                "size", sol::readonly_getter(&Sprite::size),
                                "texture", sol::property(&Sprite::m_texture, &Sprite::setTexture),
                                "setPosition", &Sprite::setPosition,
                                "setSize", &Sprite::setSize,
                                sol::base_classes, sol::bases<Drawable>()
    );
    module.new_usertype<Font>("Font",
                              sol::constructors<Font(), Font(const std::string &)>(),
                              "loadFromFile", &Font::loadFromFile
    );
    module.new_usertype<Text>("Text",
                              sol::constructors<Text(), Text(Font &)>(),
                              "position", sol::readonly_getter(&Text::position),
                              "string", sol::readonly_getter(&Text::string),
                              "characterSize", sol::readonly_getter(&Text::characterSize),
                              "font", sol::readonly_getter(&Text::font),
                              "color", sol::readonly_getter(&Text::color),
                              "setPosition", &Text::setPosition,
                              "setString", &Text::setString,
                              "setFont", &Text::setFont,
                              "setCharacterSize", &Text::setCharacterSize,
                              "setColor", &Text::setColor,
                              sol::base_classes, sol::bases<Drawable>()
    );
    module.new_usertype<RenderTexture>("RenderTexture",
                                       sol::constructors<RenderTexture()>(),
                                       "create", [](RenderTexture& rt, sol::object w, sol::object h)
                                       {
                                           if(w.get_type() != sol::type::number || h.get_type() != sol::type::number)
                                               throw sol::error("expected number");
                                           rt.create(w.as<unsigned int>(), h.as<unsigned int>());
                                       },
                                       "texture", &RenderTexture::texture,
                                       "draw",
                                       sol::overload(
                                               static_cast<void (RenderTexture::*)(Drawable &)>(&RenderTexture::draw),
                                               static_cast<void (RenderTexture::*)(Drawable &, const Shader &)>(&RenderTexture::draw)
                                       ),
                                       "drawRect", &RenderTexture::drawRect,
                                       "drawSprite", &RenderTexture::drawSprite,
                                       "drawTexture", &RenderTexture::drawTexture,
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

extern "C" int luaopen_Zadymka_Graphics(lua_State *L)
{
    return sol::stack::call_lua(L, 1, Graphics::createModule);
}