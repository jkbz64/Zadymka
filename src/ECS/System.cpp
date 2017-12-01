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
                                                 sol::function_result results;
                                                 if(system.m_system.valid())
                                                 {
                                                     sol::table meta = system.m_system;
                                                     results = meta[name].call(system.m_system, args);
                                                 }
                                                 return results;
                                             };
                                         },
                                         "update", &System::update,
                                         "fixedUpdate", &System::fixedUpdate,
                                         "draw", &System::draw
            );
}

System::System()
{
    m_system = Lua::getState().script("return nil");
    m_init = [](EventManager &, EntityManager &) {};
    m_update = [](double) {};
    m_fixedUpdate = [](double) {};
    m_draw = [](Window &, double) {};
}

System::System(sol::object system) :
    m_system(std::move(system))
{
    m_init = [](EventManager &, EntityManager &) {};
    m_update = [](double) {};
    m_fixedUpdate = [](double) {};
    m_draw = [](Window &, double) {};
    sol::function _init, _update, _fixedUpdate, _draw;
    sol::tie(_init, _update, _fixedUpdate, _draw) = Lua::scriptArgs(
    R"(
        local system = arg[1]
        local returnWrappedFunction = function(f)
            if f ~= nil then
                return function(...) return f(system, ...) end
            else
                return nil
            end
        end
        return returnWrappedFunction(system.init),
               returnWrappedFunction(system.update),
               returnWrappedFunction(system.fixedUpdate),
               returnWrappedFunction(system.draw)
    )", m_system);
    
    if(_init.valid())
        m_init = [_init](EventManager &ev, EntityManager &em) { _init.call(ev, em); };
    if(_update.valid())
        m_update = [_update](double dt) { _update.call(dt); };
    if(_fixedUpdate.valid())
        m_fixedUpdate = [_fixedUpdate](double dt) { _fixedUpdate.call(dt); };
    if(_draw.valid())
        m_draw = [_draw](Window &w, double alpha) { _draw.call(w, alpha); };
}

void System::init(EventManager &ev, EntityManager &em) const
{
    m_init(ev, em);
}

void System::update(double dt) const
{
    m_update(dt);
}

void System::fixedUpdate(double dt) const
{
    m_fixedUpdate(dt);
}

void System::draw(Window &w, double alpha) const
{
    m_draw(w, alpha);
}
