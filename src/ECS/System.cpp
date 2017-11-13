#include <ECS/System.hpp>
#include <ECS/EventManager.hpp>
#include <ECS/EntityManager.hpp>
#include <Graphics/Window.hpp>

void System::registerClass()
{
    Lua::getState().new_usertype<System>("System",
                                         "new", sol::no_constructor,
                                         sol::meta_function::index, [](sol::object, const std::string& name)
                                         {
                                             return [name](System& system, sol::variadic_args args)
                                             {
                                                 sol::table meta = system.m_system;
                                                 return meta[name].call(system.m_system, args);
                                             };
                                         },
                                         "update", &System::update,
                                         "fixedUpdate", &System::fixedUpdate,
                                         "draw", &System::draw);
}

System::System()
{
    m_system = Lua::getState().script("return nil");
    sol::tie(m_init, m_update, m_fixedUpdate, m_draw) = Lua::getState().script(
    R"(
    local nilf = function() end
    return nilf, nilf, nilf, nilf
    )");
}

System::System(sol::object system) :
    m_system(system)
{
    sol::tie(m_init, m_update, m_fixedUpdate, m_draw) = Lua::scriptArgs(
    R"(
    local system = arg[1]
    local returnWrappedFunction = function(f)
        if f ~= nil then
            return function(...) return f(system, ...) end
        else
            return nil
        end
    end
    local nilf = function(...) end
    system.entities = arg[2]
    if system.require ~= nil then
        local requireds = system:require()
        for _, v in pairs(requireds) do
            arg[3]:add(v)
        end
    end
    return returnWrappedFunction(system.init) or nilf,
           returnWrappedFunction(system.update) or nilf,
           returnWrappedFunction(system.fixedUpdate) or nilf,
           returnWrappedFunction(system.draw) or nilf
    )", m_system, &m_entities, &m_requiredComponents);
}

void System::init(EventManager &ev, EntityManager &em)
{
    m_init.call(ev, em);
}

void System::update(float dt)
{
    m_update.call(dt);
}

void System::fixedUpdate(float dt)
{
    m_fixedUpdate.call(dt);
}

void System::draw(Window &w, float alpha)
{
    m_draw.call(w, alpha);
}
