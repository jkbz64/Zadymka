local PhysicsComponent = class('Physics')

function PhysicsComponent:initialize(t)
    self.body = Body:new(t)
end

return PhysicsComponent