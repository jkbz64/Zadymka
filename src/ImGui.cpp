#include <ImGui.hpp>
#include <sol/state_view.hpp>

#include <imgui.h>
#include <ImGui/imgui_impl_glfw_gl3.h>
#include <Graphics/glad/glad.h>
#include <GLFW/glfw3.h>

namespace
{
    GLFWwindow* m_window = nullptr;
}

void ImGUI::setWindow(GLFWwindow *window)
{
    if(m_window != nullptr)
        ImGui_ImplGlfwGL3_Shutdown();
    m_window = window;
    ImGui_ImplGlfwGL3_Init(m_window, true);
}

sol::table ImGUI::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module["Render"] = &ImGui::Render;
    module["NewFrame"] = &ImGui_ImplGlfwGL3_NewFrame;
    module["Text"] = [](const std::string& text) { ImGui::Text(text.c_str()); };
    return module;
}

extern "C" int luaopen_Zadymka_ImGui(lua_State* L)
{
    return sol::stack::call_lua(L, 1, ImGUI::createModule);
}