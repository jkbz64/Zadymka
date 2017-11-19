local PhysicsSystem = class('PhysicsSystem')

function PhysicsSystem:init(ev, em)
    self.world = World:new()
end

function PhysicsSystem:require()
    return {"Physics"}
end

function PhysicsSystem:fixedUpdate(dt)
    self.world:step(dt)
end

function PhysicsSystem:onEntityCreated(event)

end

return PhysicsSystem