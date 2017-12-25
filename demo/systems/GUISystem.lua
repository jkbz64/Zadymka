local ImGui = Zadymka.ImGui

text = ImGui.MakeBuffer('omegalul')
print(text)


ECS.registerSystem('GUISystem', {
    init = function(ev, em)
        ev:subscribe('WindowResize', self, self.onWindowResize)
        self.camera = Zadymka.Graphics.Camera:new()
        self.widgets = {
            test = function()
                ImGui.InputText('test', text)
                print(text:get())
            end
        }
    end,
    update = function(dt)
        ImGui.NewFrame()
        for _, widget in pairs(self.widgets) do
            ImGui.Begin(_)
            widget()
            ImGui.End()
        end
    end,
    draw = function(window, alpha)
        ImGui.Render()
    end
})