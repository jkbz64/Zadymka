#include <ImGui.hpp>
#include <sol/state_view.hpp>

#include <imgui.h>
#include <ImGui/imgui_impl_glfw_gl3.h>
#include <Graphics/glad/glad.h>
#include <GLFW/glfw3.h>
#include <Graphics/Texture.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace
{
    GLFWwindow* m_window = nullptr;
    
    template<class T>
    using Buffer = std::unique_ptr<T>;
    
    auto vector_getter = [](void* vec, int idx, const char** out_text)
    {
        auto& vector = *static_cast<std::vector<std::string>*>(vec);
        if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
        *out_text = vector.at(idx).c_str();
        return true;
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
    
    module.new_usertype<ImVec2>("ImVec2", sol::constructors<ImVec2(float, float), ImVec2(const ImVec2&)>(),
                                "x", &ImVec2::x,
                                "y", &ImVec2::y
    );
    
    module["Vec2"] = [](float x, float y)
    {
        return ImVec2(x, y);
    };
    
    module["MakeBuffer"] = sol::overload(
            [](const int& integer)
            {
                return std::make_unique<int>(integer);
            },
            [](const float& f)
            {
                return std::make_unique<float>(f);
            },
            [](const std::string& string)
            {
                auto buffer = std::make_unique<std::string>(string);
                buffer->reserve(256);
                return buffer;
            },
            [](const std::string& string, std::size_t size)
            {
                auto buffer = std::make_unique<std::string>(string);
                buffer->reserve(size);
                return buffer;
            },
            [](bool boolean)
            {
                return std::make_unique<bool>(boolean);
            }
    );
    
    module["Get"] = sol::overload(
            [](std::unique_ptr<int>& value)
            {
                return *value;
            },
            [](std::unique_ptr<float>& value)
            {
                return *value;
            },
            [](std::unique_ptr<std::string>& value)
            {
                return value->data();
            },
            [](std::unique_ptr<bool>& value)
            {
                return *value;
            }
    );
    
    
    // Main
    module["NewFrame"] = &ImGui_ImplGlfwGL3_NewFrame;
    module["Render"] = &ImGui::Render;
    
    
    // Window
    module["Begin"] = sol::overload(
            [](const char* text)
            {
                return ImGui::Begin(text);
            },
            [](const char* text, int flag)
            {
                return ImGui::Begin(text, NULL, flag);
            }
    );
    module["End"] = &ImGui::End;
    module["BeginChild"] = sol::overload(
            [](const char* text)
            {
                return ImGui::BeginChild(text);
            },
            [](const char* text, const glm::uvec2& size)
            {
                return ImGui::BeginChild(text, ImVec2(size.x, size.y));
            },
            [](const char* text, const glm::uvec2& size, bool border)
            {
                return ImGui::BeginChild(text, ImVec2(size.x, size.y), border);
            },
            [](const char* text, const glm::uvec2& size, int flags)
            {
                return ImGui::BeginChild(text, ImVec2(size.x, size.y), false, flags);
            },
            [](const char* text, const glm::uvec2& size, bool border, int flags)
            {
                return ImGui::BeginChild(text, ImVec2(size.x, size.y), border, flags);
            }
    );
    module["EndChild"] = &ImGui::EndChild;
    module.new_usertype<ImDrawList>("ImDrawList",
                                    "new", sol::no_constructor,
                                    "AddRect", [](ImDrawList& d, const ImVec2 &topleft, const ImVec2& botright, float r, float g, float b, float a)
                                    {
                                        d.AddRect(topleft, botright, IM_COL32(r, g, b, a));
                                    }
    );
    module["GetDrawList"] = &ImGui::GetWindowDrawList;
    // Content / Region
    module["GetContentRegionMax"] = &ImGui::GetContentRegionMax;
    module["GetContentRegionAvail"] = &ImGui::GetContentRegionAvail;
    module["GetContentRegionAvailWidth"] = &ImGui::GetContentRegionAvailWidth;
    module["GetWindowContentRegionMin"] = &ImGui::GetWindowContentRegionMin;
    module["GetWindowContentRegionMax"] = &ImGui::GetWindowContentRegionMax;
    module["GetWindowContentRegionWidth"] = &ImGui::GetWindowContentRegionWidth;
    // Size / Pos
    module["GetWindowPos"] = []() { return std::make_tuple(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y); };
    module["GetWindowSize"] = []() -> glm::uvec2 { return glm::uvec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight()); };
    module["IsWindowCollapsed"] = &ImGui::IsWindowCollapsed;
    module["IsWindowAppearing"] = &ImGui::IsWindowAppearing;
    module["SetWindowFontScale"] = &ImGui::SetWindowFontScale;
    
    module["SetNextWindowPos"] = sol::overload(
            [](float x, float y)
            {
                ImGui::SetNextWindowPos(ImVec2(x, y));
            },
            [](const ImVec2& pos)
            {
                ImGui::SetNextWindowPos(pos);
            },
            [](const ImVec2& pos, int cond)
            {
                ImGui::SetNextWindowPos(pos, cond);
            },
            &ImGui::SetNextWindowPos
    );
    module["SetNextWindowSize"] = sol::overload(
            [](float w, float h)
            {
                ImGui::SetNextWindowSize(ImVec2(w, h));
            },
            [](const ImVec2& size)
            {
                ImGui::SetNextWindowSize(size);
            },
            &ImGui::SetNextWindowSize
    );
    module["SetNextWindowSizeConstraints"] = [](const ImVec2& min, const ImVec2& max)
    {
        ImGui::SetNextWindowSizeConstraints(min, max);
    };
    module["SetNextWindowContentSize"] = &ImGui::SetNextWindowContentSize;
    module["SetNextWindowCollapsed"] = sol::overload(
            [](bool collapsed)
            {
                ImGui::SetNextWindowCollapsed(collapsed);
            },
            &ImGui::SetNextWindowCollapsed
    );
    module["SetNextWindowFocus"] = &ImGui::SetNextWindowFocus;
    
    
    // Scroll
    module["GetScrollX"] = &ImGui::GetScrollX;
    module["GetScrollY"] = &ImGui::GetScrollY;
    module["GetScrollMaxX"] = &ImGui::GetScrollMaxX;
    module["GetScrollMaxY"] = &ImGui::GetScrollMaxY;
    module["SetScrollX"] = &ImGui::SetScrollX;
    module["SetScrollY"] = &ImGui::SetScrollY;
    module["SetScrollHere"] = &ImGui::SetScrollHere;
    module["SetScrollFromPosY"] = sol::overload(
            [](float y)
            {
                ImGui::SetScrollFromPosY(y);
            },
            &ImGui::SetScrollFromPosY
    );
    
    // Parameter stacks - Global
    module["PushStyleVar"] = sol::overload(
            [](int style, const ImVec2& vec)
            {
                ImGui::PushStyleVar(style, vec);
            },
            [](int style, float v)
            {
                ImGui::PushStyleVar(style, v);
            }
    );
    module["PopStyleVar"] = &ImGui::PopStyleVar;
    
    // Parameter stacks - Current Window
    module["PushItemWidth"] = &ImGui::PushItemWidth;
    module["PopItemWidth"] = &ImGui::PopItemWidth;
    module["CalcItemWidth"] = &ImGui::CalcItemWidth;
    module["PushTextWrapPos"] = &ImGui::PushTextWrapPos;
    module["PopTextWrapPos"] = &ImGui::PopTextWrapPos;
    module["PushAllowKeyboardFocus"] = &ImGui::PushAllowKeyboardFocus;
    module["PopAllowKeyboardFocus"] = &ImGui::PopAllowKeyboardFocus;
    module["PushButtonRepeat"] = &ImGui::PushButtonRepeat;
    module["PopButtonRepeat"] = &ImGui::PopButtonRepeat;
    
    // Cursor / Layout
    module["Separator"] = &ImGui::Separator;
    module["SameLine"] = sol::overload(
            []()
            {
                ImGui::SameLine();
            },
            [](float pos_x)
            {
                ImGui::SameLine(pos_x);
            },
            &ImGui::SameLine
    );
    module["NewLine"] = &ImGui::NewLine;
    module["Spacing"] = &ImGui::Spacing;
    module["Dummy"] = &ImGui::Dummy;
    module["Indent"] = &ImGui::Indent;
    module["Unindent"] = &ImGui::Unindent;
    module["BeginGroup"] = &ImGui::BeginGroup;
    module["EndGroup"] = &ImGui::EndGroup;
    module["GetCursorPos"] = []() { std::make_tuple(ImGui::GetCursorPosX(), ImGui::GetCursorPosY()); };
    module["SetCursorPos"] = &ImGui::SetCursorPos;
    module["GetCursorScreenPos"] = &ImGui::GetCursorScreenPos;
    module["SetCursorScreenPos"] = &ImGui::SetCursorScreenPos;
    module["AlignTextToFramePadding"] = &ImGui::AlignTextToFramePadding;
    module["GetTextLineHeight"] = &ImGui::GetTextLineHeight;
    module["GetTextLineHeightWithSpacing"] = &ImGui::GetTextLineHeightWithSpacing;
    module["GetFrameHeight"] = &ImGui::GetFrameHeight;
    module["GetFrameHeightWithSpacing"] = &ImGui::GetFrameHeightWithSpacing;
    
    // Columns
    module["Columns"] = sol::overload(
            []()
            {
                ImGui::Columns();
            },
            [](int count)
            {
                ImGui::Columns(count);
            },
            [](int count, bool border)
            {
                ImGui::Columns(count, NULL, border);
            }
    );
    module["NextColumn"] = &ImGui::NextColumn;
    module["GetColumnIndex"] = &ImGui::GetColumnIndex;
    module["GetColumnsCount"] = &ImGui::GetColumnsCount;
    
    // Widgets: Text
    module["Text"] = [](const char* text) { ImGui::TextUnformatted(text); };
    module["Bullet"] = [](const char* label)
    {
        ImGui::BulletText(label);
    };
    
    // Widgets: Buttons
    module["Button"] = sol::overload(
            [](const char *text)
            {
                return ImGui::Button(text);
            },
            [](const char* text, const glm::uvec2& size)
            {
                return ImGui::Button(text, ImVec2(size.x, size.y));
            }
    );
    module["SmallButton"] = &ImGui::SmallButton;
    module["CheckBox"] = [](const char* label, Buffer<bool>& boolean)
    {
        return ImGui::Checkbox(label, &*boolean);
    };
    
    // Image
    module["Image"] = sol::overload(
            [](const Texture& texture)
            {
              ImGui::Image((void*)texture.getID(), ImVec2(texture.getSize().x, texture.getSize().y), ImVec2(0, 1), ImVec2(1, 0));
            },
            [](const Texture& texture, const glm::uvec2& size)
            {
                ImGui::Image((void*)texture.getID(), ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
            }
    );
    module["ImageButton"] = [](const Texture& texture, const glm::uvec2& size)
    {
        return ImGui::ImageButton((void*)texture.getID(), ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    };
    
    // Combo
    module["BeginCombo"] = sol::overload(
            [](const char* label, const char* preview)
            {
                return ImGui::BeginCombo(label, preview);
            },
            [](const char* label, const char* preview, int flags)
            {
                return ImGui::BeginCombo(label, preview, flags);
            }
    );
    module["EndCombo"] = &ImGui::EndCombo;
    module["Combo"] = [](const char* label, Buffer<int>& currentItem, const std::string& items)
    {
        auto comboItems = items;
        std::replace_if(comboItems.begin(), comboItems.end(), [](const char& c){ return std::isspace(c); }, '\0');
        comboItems += "\0";
        return ImGui::Combo(label, &*currentItem.get(), comboItems.c_str());
    };
    
    // Inputs
    module["InputText"] = [](const std::string& name, Buffer<std::string>& buffer)
    {
        ImGui::InputText(name.c_str(), &(*buffer)[0], buffer->capacity());
    };
    module["InputTextMultiline"] = [](const std::string& name, Buffer<std::string>& buffer)
    {
        ImGui::InputText(name.c_str(), &(*buffer)[0], buffer->capacity());
    };
    module["SliderInt"] = [](sol::this_state L, const char* label, sol::object buffer, int min, int max)
    {
        if(buffer.is<Buffer<float>&>())
        {
            auto val = *buffer.as<Buffer<float>>().get();
            buffer = sol::make_object(L, std::make_unique<int>(val));
        }
        auto& buff = buffer.as<Buffer<int>>();
        return ImGui::SliderInt(label, &*buff, min, max);
    };
    module["SliderFloat"] = [](const char* label, Buffer<float>& buffer, float min, float max)
    {
        ImGui::SliderFloat(label, &*buffer, min, max);
    };
    
    // Trees
    module["TreeNode"] = static_cast<bool(*)(const char*)>(&ImGui::TreeNode);
    module["TreeNodeEx"] = sol::overload(
            [](const char* text)
            {
                return ImGui::TreeNodeEx(text);
            },
            [](const char* text, int flags)
            {
                return ImGui::TreeNodeEx(text, flags);
            }
    );
    module["SetNextTreeNodeOpen"] = [](bool isOpen)
    {
        ImGui::SetNextTreeNodeOpen(isOpen);
    };
    module["TreePop"] = &ImGui::TreePop;
    
    // Selectables / Lists
    module["Selectable"] = sol::overload(
            [](const char* label)
            {
                return ImGui::Selectable(label);
            },
            [](const char* label, bool selected)
            {
                return ImGui::Selectable(label, selected);
            },
            [](const char* label, bool selected, int flags)
            {
                return ImGui::Selectable(label, selected, flags);
            },
            [](const char* label, const glm::uvec2& size)
            {
                return ImGui::Selectable(label, false, 0, ImVec2(size.x, size.y));
            },
            [](const char* label, int flags)
            {
                return ImGui::Selectable(label, false, flags);
            }
    );
    
    module["ListBox"] = [](const std::string& name, Buffer<int>& currentItem, std::vector<std::string>& values)
    {
        if (values.empty()) { return false; }
        return ImGui::ListBox(name.c_str(), &*currentItem.get(), vector_getter,
                              static_cast<void*>(&values), values.size());
    };
    
    // Menus
    module["BeginMenuBar"] = &ImGui::BeginMenuBar;
    module["MenuItem"] = [](const char* label)
    {
        return ImGui::MenuItem(label);
    };
    module["EndMenuBar"] = &ImGui::EndMenuBar;
    
    // Popups
    module["OpenPopup"] = &ImGui::OpenPopup;
    module["BeginPopup"] = &ImGui::BeginPopup;
    module["BeginPopupModal"] = sol::overload(
            [](const char* label)
            {
                return ImGui::BeginPopupModal(label);
            },
            [](const char* label, int flags)
            {
                return ImGui::BeginPopupModal(label, NULL, flags);
            }
    );
    module["EndPopup"] = &ImGui::EndPopup;
    module["CloseCurrentPopup"] = &ImGui::CloseCurrentPopup;
    
    
    // Widgets: Color Edit
    module["ColorEdit3"] = [](const char* label, glm::vec3& buffer)
    {
        return ImGui::ColorEdit3(label, &buffer.r);
    };
    
    module["ColorEdit4"] = [](const char* label, glm::vec4& buffer)
    {
        return ImGui::ColorEdit3(label, &buffer.r);
    };
    
    // Utilities
    module["IsItemHovered"] = sol::overload(
            []()
            {
                return ImGui::IsItemHovered();
            },
            [](int flags)
            {
                return ImGui::IsItemHovered(flags);
            }
    );
    module["IsItemActive"] = &ImGui::IsItemActive;
    module["IsItemClicked"] = sol::overload(
            []()
            {
                return ImGui::IsItemClicked();
            },
            [](int flags)
            {
                return ImGui::IsItemClicked(flags);
            }
    );
    module["IsItemVisible"] = &ImGui::IsItemVisible;
    module["IsAnyItemHovered"] = &ImGui::IsAnyItemHovered;
    module["IsAnyItemActive"] = &ImGui::IsAnyItemActive;
    module["GetItemRectMin"] = []() { return std::make_tuple(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y); };
    module["GetItemRectMax"] = []() { return std::make_tuple(ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y); };
    module["GetItemRectSize"] = []() { return std::make_tuple(ImGui::GetItemRectSize().x, ImGui::GetItemRectSize().y); };
    module["SetItemAllowOverlap"] = &ImGui::SetItemAllowOverlap;
    module["IsWindowFocused"] = sol::overload(
            []()
            {
                return ImGui::IsWindowFocused();
            },
            [](int flags)
            {
                return ImGui::IsWindowFocused(flags);
            }
    );
    module["IsWindowHovered"] = sol::overload(
            []()
            {
                return ImGui::IsWindowHovered();
            },
            [](int flags)
            {
                return ImGui::IsWindowHovered(flags);
            }
    );
    module["IsAnyWindowFocused"] = &ImGui::IsAnyWindowFocused;
    module["IsAnyWindowHovered"] = &ImGui::IsAnyWindowHovered;
    module["IsRectVisible"] = static_cast<bool(*)(const ImVec2&, const ImVec2&)>(&ImGui::IsRectVisible);
    module["GetTime"] = &ImGui::GetTime;
    module["GetFrameCount"] = &ImGui::GetFrameCount;
    module["CalcTextSize"] = [](const char* text) { return ImGui::CalcTextSize(text); };
    module["RGBtoHSV"] = [](float r, float g, float b)
    {
        float h, s, v;
        ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
        return std::make_tuple(h, s, v);
    };
    module["HSVtoRGB"] = [](float h, float s, float v)
    {
        float r, g, b;
        ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
        return std::make_tuple(r, g, b);
    };
    
    // Inputs
    module["IsKeyDown"] = &ImGui::IsKeyDown;
    module["IsKeyPressed"] = sol::overload(
            [](int key)
            {
                return ImGui::IsKeyPressed(key);
            },
            &ImGui::IsKeyPressed
    );
    module["IsKeyReleased"] = &ImGui::IsKeyReleased;
    module["IsMouseDown"] = &ImGui::IsMouseDown;
    module["IsMouseClicked"] = sol::overload(
            [](int button)
            {
                return ImGui::IsMouseClicked(button);
            },
            &ImGui::IsMouseClicked
    );
    module["IsMouseDoubleClicked"] = &ImGui::IsMouseDoubleClicked;
    module["IsMouseReleased"] = &ImGui::IsMouseReleased;
    module["IsMouseDragging"] = sol::overload(
            []()
            {
                return ImGui::IsMouseDragging();
            },
            [](int button)
            {
                return ImGui::IsMouseDragging(button);
            },
            &ImGui::IsMouseDragging
    );
    module["IsMouseHoveringRect"] = sol::overload(
            [](const ImVec2& min, const ImVec2& max)
            {
                return ImGui::IsMouseHoveringRect(min, max);
            },
            &ImGui::IsMouseHoveringRect
    );
    module["IsMousePosValid"] = &ImGui::IsMousePosValid;
    module["GetMousePos"] = []() { return std::make_tuple(ImGui::GetMousePos().x, ImGui::GetMousePos().y); };
    module["EnableKeyboard"] = &ImGui::CaptureKeyboardFromApp;
    module["EnableMouse"] = &ImGui::CaptureMouseFromApp;
    
    return module;
}

extern "C" int luaopen_Zadymka_ImGui(lua_State* L)
{
    return sol::stack::call_lua(L, 1, ImGUI::createModule);
}