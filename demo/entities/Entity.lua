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