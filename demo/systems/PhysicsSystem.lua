local PhysicsSystem = class('PhysicsSystem')

function PhysicsSystem:init(ev, em)
    ev:subscribe('EntityCreated', self, self.onEntityCreated)
    self.world = World:new(100.0, 0)
    self.dynamicBodies = {}
end

function PhysicsSystem:require()
    return {"Physics"}
end

function PhysicsSystem:fixedUpdate(dt)
    self.world:step(dt)
    for _, v in pairs(self.dynamicBodies) do
        local x, y = v:get('Physics').body:getPosition()
        v:setPosition(x, y)
    end
end

function PhysicsSystem:onEntityCreated(event)
    if event.entity:has('Physics') then
        self.world:addBody(event.entity:get('Physics').body)
        table.insert(self.dynamicBodies, event.entity)
    end
end

return PhysicsSystem