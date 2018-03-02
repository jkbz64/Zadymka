#include <Math.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>
#include <sol/state_view.hpp>
#include <cstddef>
#include <iostream>

namespace
{
    template<class T>
    T lerp(const T& start, const T& end, double alpha)
    {
        return glm::mix(start, end, alpha);
    }
    
    template<class T>
    T normalize(const T& a)
    {
        return glm::normalize(a);
    }
    
    template<class T>
    float distance(const T& a, const T& b)
    {
        return glm::distance(a, b);
    }
    
    template<class T>
    float dot(const T& a, const T& b)
    {
        return glm::dot(a, b);
    }
    
    template<class T>
    float length(const T& a)
    {
        return glm::length(a);
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec2<V>>::value>>
    constexpr auto unpack()
    {
        return [](const T& vec) { return std::make_tuple(vec.x, vec.y); };
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec3<V>>::value>,
            typename = void>
    constexpr auto unpack()
    {
        return [](const T& vec) { return std::make_tuple(vec.x, vec.y, vec.z); };
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec4<V>>::value>,
            typename = void,
            typename = void>
    constexpr auto unpack()
    {
        return [](const T& vec) { return std::make_tuple(vec.x, vec.y, vec.z, vec.w); };
    }
    
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec2<V>>::value>>
    auto add()
    {
        return sol::overload(
                [](const T& a, const glm::vec2& b)  { return a + T(b); },
                [](const T& a, const glm::ivec2& b) { return a + T(b); },
                [](const T& a, const glm::uvec2& b) { return a + T(b); },
                [](const T& a, const glm::vec3& b)  { return a + T(b); },
                [](const T& a, const glm::ivec3& b) { return a + T(b); },
                [](const T& a, const glm::uvec3& b) { return a + T(b); }
        );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec3<V>>::value>,
            typename = void>
    auto add()
    {
        return sol::overload(
                [](const T& a, const glm::vec2& b)  { return a + T(b, 0.f); },
                [](const T& a, const glm::ivec2& b) { return a + T(b, 0); },
                [](const T& a, const glm::uvec2& b) { return a + T(b, 0u); },
                [](const T& a, const glm::vec3& b)  { return a + T(b); },
                [](const T& a, const glm::ivec3& b) { return a + T(b); },
                [](const T& a, const glm::uvec3& b) { return a + T(b); }
        );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec4<V>>::value>,
            typename = void,
            typename = void>
    auto add()
    {
        return sol::overload(
                [](const T& a, const glm::vec2& b)  { return a + T(b, 0.f, 0.f); },
                [](const T& a, const glm::ivec2& b) { return a + T(b, 0, 0); },
                [](const T& a, const glm::uvec2& b) { return a + T(b, 0u, 0u); },
                [](const T& a, const glm::vec3& b)  { return a + T(b, 0.f); },
                [](const T& a, const glm::ivec3& b) { return a + T(b, 0); },
                [](const T& a, const glm::uvec3& b) { return a + T(b, 0u); }
        );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec2<V>>::value>>
    auto sub()
    {
        return sol::overload(
                [](const T& a, const glm::vec2& b)  { return a - T(b); },
                [](const T& a, const glm::ivec2& b) { return a - T(b); },
                [](const T& a, const glm::uvec2& b) { return a - T(b); },
                [](const T& a, const glm::vec3& b)  { return a + T(b); },
                [](const T& a, const glm::ivec3& b) { return a + T(b); },
                [](const T& a, const glm::uvec3& b) { return a + T(b); }
        );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec3<V>>::value>,
            typename = void>
    auto sub()
    {
        return sol::overload(
                [](const T& a, const glm::vec2& b)  { return a - T(b, 0.f); },
                [](const T& a, const glm::ivec2& b) { return a - T(b, 0); },
                [](const T& a, const glm::uvec2& b) { return a - T(b, 0u); },
                [](const T& a, const glm::vec3& b)  { return a + T(b); },
                [](const T& a, const glm::ivec3& b) { return a + T(b); },
                [](const T& a, const glm::uvec3& b) { return a + T(b); }
        );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec4<V>>::value>,
            typename = void,
            typename = void>
    auto sub()
    {
        return sol::overload(
                [](const T& a, const glm::vec2& b)  { return a - T(b, 0.f, 0.f); },
                [](const T& a, const glm::ivec2& b) { return a - T(b, 0, 0); },
                [](const T& a, const glm::uvec2& b) { return a - T(b, 0u, 0u); },
                [](const T& a, const glm::vec3& b)  { return a + T(b, 0.f); },
                [](const T& a, const glm::ivec3& b) { return a + T(b, 0); },
                [](const T& a, const glm::uvec3& b) { return a + T(b, 0u); }
        );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec2<V>>::value>>
    auto mul()
    {
        return sol::overload(
                [](const T& a, int b)  { return a * static_cast<V>(b); },
                [](const T& a, float b)  { return a * static_cast<V>(b); },
                [](const T& a, const glm::vec2& b) { return a * T(b); },
                [](const T& a, const glm::ivec2& b) { return a * T(b); },
                [](const T& a, const glm::uvec2& b) { return a * T(b); },
                [](const T& a, const glm::vec3& b) { return a * T(b); },
                [](const T& a, const glm::ivec3& b) { return a * T(b); },
                [](const T& a, const glm::uvec3& b) { return a * T(b); }
         );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec3<V>>::value>,
            typename = void>
    auto mul()
    {
        return sol::overload(
                [](const T& a, int b)  { return a * static_cast<V>(b); },
                [](const T& a, float b)  { return a * static_cast<V>(b); },
                [](const T& a, const glm::vec2& b) { return a * T(b, 0.f); },
                [](const T& a, const glm::ivec2& b) { return a * T(b, 0); },
                [](const T& a, const glm::uvec2& b) { return a * T(b, 0u); },
                [](const T& a, const glm::vec3& b) { return a * T(b); },
                [](const T& a, const glm::ivec3& b) { return a * T(b); },
                [](const T& a, const glm::uvec3& b) { return a * T(b); }
        );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec4<V>>::value>,
            typename = void,
            typename = void>
    auto mul()
    {
        return sol::overload(
                [](const T& a, int b)  { return a * static_cast<V>(b); },
                [](const T& a, float b)  { return a * static_cast<V>(b); },
                [](const T& a, const glm::vec2& b) { return a * T(b, 0.f, 0.f); },
                [](const T& a, const glm::ivec2& b) { return a * T(b, 0, 0); },
                [](const T& a, const glm::uvec2& b) { return a * T(b, 0u, 0u); },
                [](const T& a, const glm::vec3& b) { return a * T(b, 0.f); },
                [](const T& a, const glm::ivec3& b) { return a * T(b, 0); },
                [](const T& a, const glm::uvec3& b) { return a * T(b, 0u); }
        );
    }
    
    template<class T,
             typename V = typename T::value_type>
    auto div()
    {
        return sol::overload(
                [](const T& a, int b) { return a / static_cast<V>(b); },
                [](const T& a, float b) { return a / static_cast<V>(b); }
        );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec2<V>>::value>>
    auto registerVec(sol::table& module, const std::string& name)
    {
        module.new_usertype<T>(name,
                               sol::constructors<T(), T(V, V), T(const glm::vec2&), T(const glm::ivec2&), T(const glm::uvec2&)>(),
                               "x", &T::x,
                               "y", &T::y,
                               sol::meta_function::call, unpack<T>(),
                               sol::meta_function::addition, add<T>(),
                               sol::meta_function::subtraction, sub<T>(),
                               sol::meta_function::multiplication, mul<T>(),
                               sol::meta_function::division, div<T>(),
                               sol::meta_function::equal_to, [](const T& a, const T& b)
                               {
                                   return a == b;
                               },
                               sol::meta_function::to_string, [](const T& a)
                               {
                                   return std::string(std::to_string(a.x) + '\t' + std::to_string(a.y));
                               }
        );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec3<V>>::value>,
            typename = void>
    auto registerVec(sol::table& module, const std::string& name)
    {
        module.new_usertype<T>(name,
                               sol::constructors<T(), T(V, V, V), T(const T&)>(),
                               "x", &T::x,
                               "y", &T::y,
                               "z", &T::z,
                               sol::meta_function::call, unpack<T>(),
                               sol::meta_function::addition, add<T>(),
                               sol::meta_function::subtraction, sub<T>(),
                               sol::meta_function::multiplication, mul<T>(),
                               sol::meta_function::division, div<T>(),
                               sol::meta_function::equal_to, [](const T& a, const T& b)
                               {
                                   return a == b;
                               },
                               sol::meta_function::to_string, [](const T& a)
                               {
                                   return std::string(std::to_string(a.x) + '\t' + std::to_string(a.y) + '\t' + std::to_string(a.z));
                               }
        );
    }
    
    template<class T,
            typename V = typename T::value_type,
            typename = std::enable_if_t<std::is_same<T, glm::tvec4<V>>::value>,
            typename = void,
            typename = void>
    auto registerVec(sol::table& module, const std::string& name)
    {
        module.new_usertype<T>(name,
                               sol::constructors<T(), T(V, V, V, V), T(const T&)>(),
                               "x", &T::x,
                               "y", &T::y,
                               "z", &T::z,
                               "w", &T::w,
                               sol::meta_function::call, unpack<T>(),
                               sol::meta_function::addition, add<T>(),
                               sol::meta_function::subtraction, sub<T>(),
                               sol::meta_function::multiplication, mul<T>(),
                               sol::meta_function::division, div<T>(),
                               sol::meta_function::equal_to, [](const T& a, const T& b)
                               {
                                   return a == b;
                               },
                               sol::meta_function::to_string, [](const T& a)
                               {
                                   return std::string(std::to_string(a.x) + '\t' + std::to_string(a.y) + '\t' + std::to_string(a.z) + '\t' + std::to_string(a.w));
                               }
        );
    }
}

sol::table Math::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module.set_function("Vec2", sol::overload(
            [](float a, float b)
            {
                return glm::vec2(a, b);
            },
            [](int a, int b)
            {
                return glm::ivec2(a, b);
            },
            [](const glm::vec2& a)
            {
                return glm::vec2(a);
            },
            [](const glm::uvec2& a)
            {
                return glm::uvec2(a);
            },
            [](const glm::ivec2& a)
            {
                return glm::ivec2(a);
            }
    ));
    
    //Vec2
    registerVec<glm::vec2>(module, "Vec2f");
    registerVec<glm::ivec2>(module, "Vec2i");
    registerVec<glm::uvec2>(module, "Vec2u");
    //Vec3
    registerVec<glm::vec3>(module, "Vec3f");
    registerVec<glm::ivec3>(module, "Vec3i");
    registerVec<glm::uvec3>(module, "Vec3u");
    //Vec4
    registerVec<glm::vec4>(module, "Vec4f");
    registerVec<glm::ivec4>(module, "Vec4i");
    registerVec<glm::uvec4>(module, "Vec4u");
    
    module.new_usertype<glm::mat4>("Matrix4", sol::constructors<glm::mat4(), glm::mat4(const glm::mat4&)>(),
                                   sol::meta_function::addition, [](const glm::mat4& a, const glm::mat4& b)
                                   {
                                       return a + b;
                                   },
                                   sol::meta_function::subtraction, [](const glm::mat4& a, const glm::mat4& b)
                                   {
                                       return a - b;
                                   },
                                   sol::meta_function::multiplication,
                                   sol::overload(
                                           [](const glm::mat4& a, const glm::mat4& b)
                                           {
                                               return a * b;
                                           },
                                           [](const glm::mat4& a, const glm::vec2& b)
                                           {
                                               return a * glm::vec4(b, 1.f, 1.f);
                                           },
                                           [](const glm::mat4& a, const glm::vec3& b)
                                           {
                                               return a * glm::vec4(b, 1.f);
                                           },
                                           [](const glm::mat4& a, const glm::vec4& b)
                                           {
                                               return a * b;
                                           }
                                           
                                   )
    );
    
    module["Lerp"] = sol::overload(
            &lerp<glm::vec2>,
            &lerp<glm::uvec2>,
            &lerp<glm::ivec2>,
            &lerp<float>
    );
    
    module["Normalize"] = sol::overload(
            &normalize<glm::vec2>,
            &normalize<glm::vec3>,
            &normalize<glm::vec4>
    );
    
    module["Distance"] = sol::overload(
            &distance<glm::vec2>,
            &distance<glm::vec3>,
            &distance<glm::vec4>
    );
    
    module["Dot"] = sol::overload(
            &dot<glm::vec2>,
            &dot<glm::vec3>,
            &dot<glm::vec4>
    );
    
    module["Length"] = sol::overload(
            &length<glm::vec2>,
            &length<glm::vec3>,
            &length<glm::vec4>
    );
    
    return module;
}

extern "C" int luaopen_Zadymka_Math(lua_State* L)
{
    return sol::stack::call_lua(L, 1, Math::createModule);
}