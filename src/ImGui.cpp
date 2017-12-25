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
    template<class T>
    using Buffer = std::shared_ptr<T>;
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
    
    module["MakeBuffer"] = sol::overload(
            [](const int& integer)
            {
                return std::make_shared<int>(integer);
            },
            [](const float& f)
            {
                return std::make_shared<float>(f);
            },
            [](const std::string& string)
            {
                auto buffer = std::make_shared<std::string>(string);
                buffer->reserve(256);
                return buffer;
            },
            [](bool boolean)
            {
                return std::make_shared<bool>(boolean);
            }
    );
    
    module["Render"] = &ImGui::Render;
    module["NewFrame"] = &ImGui_ImplGlfwGL3_NewFrame;
    module["Begin"] = [](const std::string& name)
    {
        ImGui::Begin(name.c_str());
    };
    module["End"] = &ImGui::End;
    module["Text"] = [](const std::string& text) { ImGui::Text(text.c_str()); };
    module["Button"] = [](const std::string& text) { ImGui::Button(text.c_str()); };
    module["InputText"] = [](const std::string& name, Buffer<std::string> buffer)
    {
        ImGui::InputText(name.c_str(), &(*buffer.get())[0], 256);
    };
    module["InputTextMultiline"] = [](const std::string& name, Buffer<std::string>& buffer)
    {
        ImGui::InputText(name.c_str(), &(*buffer.get())[0], buffer->capacity());
    };
    module["SliderFloat"] = [](const std::string& name, Buffer<float> f, float min, float max)
    {
        ImGui::SliderFloat(name.c_str(), &*f.get(), min, max);
    };
    module["Separator"] = &ImGui::Separator;
    module["SameLine"] = &ImGui::SameLine;
    module["NewLine"] = &ImGui::NewLine;
    module["Image"] = [](const Texture& texture, const glm::uvec2& size)
    {
        ImGui::Image((void*)texture.getID(), ImVec2(size.x, size.y));
    };
    module["ImageButton"] = [](const Texture& texture, const glm::uvec2& size)
    {
        return ImGui::ImageButton((void*)texture.getID(), ImVec2(size.x, size.y));
    };
    module["CheckBox"] = [](const std::string& name, Buffer<bool>& buffer)
    {
        ImGui::Checkbox(name.c_str(), &*buffer.get());
    };
    module["BeginCombo"] = [](const std::string& name, const std::string& preview)
    {
        return ImGui::BeginCombo(name.c_str(), preview.c_str());
    };
    module["Combo"] = [](const std::string& name, Buffer<int>& currentItem, const std::string& items)
    {
        auto comboItems = items;
        std::replace_if(comboItems.begin(), comboItems.end(), [](char& c){ return std::isspace(c); }, '\0');
        comboItems += "\0";
        return ImGui::Combo(name.c_str(), &*currentItem.get(), comboItems.c_str());
    };
    module["EndCombo"] = &ImGui::EndCombo;
    //TODO MORE
    return module;
}

extern "C" int luaopen_Zadymka_ImGui(lua_State* L)
{
    return sol::stack::call_lua(L, 1, ImGUI::createModule);
}