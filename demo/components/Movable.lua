ECS.registerComponent('Movable', {
    speed = 0,
    velocity = Vec2f:new(0.0, 0.0),
    jumpHeight = 0,
    jumpSpeed = 0
})

function ECS.Entity:getSpeed()
    if self:has('Movable') then
        return self:get('Movable').speed
    else
        return 0
    end
end

function ECS.Entity:getVelocity()
    if self:has('Movable') then
        return self:get('Movable').velocity
    else
        return Vec2f:new(0.0, 0.0)
    end
end

function ECS.Entity:getJumpSpeed()
    if self:has('Movable') then
        return self:get('Movable').jumpSpeed
    else
        return 0
    end
end


function ECS.Entity:getJumpHeight()
    if self:has('Movable') then
        return self:get('Movable').jumpHeight
    else
        return 0
    end
end