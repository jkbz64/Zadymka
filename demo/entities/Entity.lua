function Entity:getPosition()
    if self:has('Position') then
        return self:get('Position').x, self:get('Position').y
    end
end

function Entity:getPreviousPosition()
    if self:has('Position') then
        return self:get('Position')._x, self:get('Position')._y
    end
end

function Entity:move(dx, dy)
    if self:has('Position') then
        local x, y = self:getPosition()
        self:get('Position').x = x + dx
        self:get('Position').y = y + dy
    end
end

function Entity:setPosition(x, y)
    if self:has('Position') then
        self:get('Position').x = x
        self:get('Position').y = y
    end
end

function Entity:getSpeed()
    if self:has('Movable') then
        return self.components.Movable.speed
    end
end

function Entity:setSpeed(speed)
    if self:has('Movable') then
        self.components.Movable.speed = speed
    end
end