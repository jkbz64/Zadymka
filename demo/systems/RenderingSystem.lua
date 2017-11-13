local RenderingSystem = class('RenderingSystem')

function RenderingSystem:init(ev, em)

end

function RenderingSystem:require()
    return {"Position"}
end

function RenderingSystem:fixedUpdate(dt)
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
        window:drawText('test', lx, ly, 'artyard.ttf', 24)
    end
end

return RenderingSystem