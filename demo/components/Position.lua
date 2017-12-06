ECS.registerComponent('Position', {
    position = Vec2f:new(0, 0),
    _position = Vec2f:new(0, 0)
})

function ECS.Entity:getPosition()
    if self:has('Position') then
        return Vec2f:new(self:get('Position').position)
    end
end

function ECS.Entity:setPosition(x, y)
    if self:has('Position') then
        self:get('Position').position = Vec2f:new(x, y)
    end
end

function ECS.Entity:move(dx, dy)
    if self:has('Position') then
        local pos = self:getPosition()
        self:get('Position').position = Vec2f:new(pos.x + dx, pos.y + dy)
    end
end