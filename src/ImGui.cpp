#include <ImGui.hpp>
#include <sol/state_view.hpp>

#include <imgui.h>
#include <ImGui/imgui_impl_glfw_gl3.h>
#include <Graphics/glad/glad.h>
#include <GLFW/glfw3.h>
#include <Graphics/Texture.hpp>

namespace
{
    GLFWwindow* m_window = nullptr;
    
    template<class T, class V = T>
    struct Buffer
    {
        V& get()
        {
            return value;
        }
        V value;
    };
    
    struct StringBuffer : public Buffer<std::string, char[256]>
    {
        StringBuffer(const std::string& v)
        {
            strncpy(value, v.c_str(), v.size());
        }
    };
    
    struct FloatBuffer : public Buffer<float>
    {
        FloatBuffer(float f)
        {
            value = f;
        }
    };
}

void ImGUI::setWindow(GLFWwindow *window)
{
    if(m_window != nullptr)
        ImGui_ImplGlfwGL3_Shutdown();
    m_window = window;
    if(m_window != nullptr)
        ImGui_ImplGlfwGL3_Init(m_window, true);
}

sol::table ImGUI::createModule(sol::this_state L)
{
    sol::state_view lua(L);
    sol::table module = lua.create_table();
    module.new_usertype<StringBuffer>("StringBuffer", sol::constructors<StringBuffer (const std::string&)>(), "get", &StringBuffer::get);
    module.new_usertype<FloatBuffer>("FloatBuffer", sol::constructors<FloatBuffer(float)>(), "get", &FloatBuffer::get);
    module["Render"] = &ImGui::Render;
    module["NewFrame"] = &ImGui_ImplGlfwGL3_NewFrame;
    module["Begin"] = [](const std::string& name)
    {
        ImGui::Begin(name.c_str());
    };
    module["End"] = &ImGui::End;
    module["Text"] = [](const std::string& text) { ImGui::Text(text.c_str()); };
    module["Button"] = [](const std::string& text) { ImGui::Button(text.c_str()); };
    module["InputText"] = [](const std::string& name, StringBuffer& buffer)
    {
        ImGui::InputText(name.c_str(), &buffer.value[0], 256);
    };
    module["SliderFloat"] = [](const std::string& name, FloatBuffer& buffer, float min, float max)
    {
        ImGui::SliderFloat(name.c_str(), &buffer.value, min, max);
    };
    module["Separator"] = &ImGui::Separator;
    module["SameLine"] = &ImGui::SameLine;
    module["NewLine"] = &ImGui::NewLine;
    module["Image"] = [](const Texture& texture, const glm::uvec2& size)
    {
        ImGui::Image((void*)texture.getID(), ImVec2(size.x, size.y));
    };
    return module;
}

extern "C" int luaopen_Zadymka_ImGui(lua_State* L)
{
    return sol::stack::call_lua(L, 1, ImGUI::createModule);
}