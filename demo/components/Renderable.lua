local RenderableComponent = class('Renderable')

function RenderableComponent:initialize(t)
    self.texture = t.texture or ''
    self.width = t.width or 0
    self.height = t.height or 0
end

return RenderableComponent