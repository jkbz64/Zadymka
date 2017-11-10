function Entity:getSpeed()
    if self:has('Movable') then
        return self.components.Movable.m_speed
    end
end

function Entity:setSpeed(speed)
    if self:has('Movable') then
        self.component.Movable.m_speed = speed
    end
end