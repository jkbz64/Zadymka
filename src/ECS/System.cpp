#include <ECS/System.hpp>

System::System() :
    Scriptable<System>()
{

}

System::System(sol::this_state L) :
        Scriptable<System>(L)
{

}

System::System(sol::this_state L, sol::table systemTable) :
        Scriptable<System>(L, systemTable)
{
    init = m_table["init"];
}