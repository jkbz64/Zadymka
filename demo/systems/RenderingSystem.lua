local RenderingSystem = class('RenderingSystem')

function RenderingSystem:init(ev, em)
    self.entities = {}
end

function RenderingSystem:saveCurrentState()
    for _, entity in pairs(self.entities) do
        entity:get('Position')._x, entity:get('Position')._y = entity:getPosition()
    end
end

local lerp = function(a, b, t)
    return a + (b - a) * t
end

function RenderingSystem:draw(window, alpha)
    for _, entity in pairs(self.entities) do
        local x, y = entity:getPosition()
        local px, py = entity:getPreviousPosition()
        local lx, ly = lerp(px, x, alpha), lerp(py, y, alpha)
        local w, h = entity:get('Renderable').width, entity:get('Renderable').height
        window:drawRect(lx, ly, w, h, 0, 0, 0, 255)
    end
	window:drawText('test', 0.0, 200.0, 'artyard.ttf', 48)
	window:drawText('test', 0.0, 100.0, 'artyard.ttf', 48)
end

return RenderingSystem
