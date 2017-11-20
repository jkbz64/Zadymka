local DemoState = class('DemoState')

function DemoState:init()
    self.renderingSystem = self.systemManager:addSystem('RenderingSystem')
    self.movementSystem = self.systemManager:addSystem('MovementSystem')
    self.physicsSystem = self.systemManager:addSystem('PhysicsSystem')
    self.entity = self.entityManager:createEntity('Player')
    self.camera:setCenter(400, 200)
end

function DemoState:update(dt)

end

function DemoState:fixedUpdate(dt)
    self.renderingSystem:saveCurrentState()
    self.movementSystem:fixedUpdate(dt)
    self.physicsSystem:fixedUpdate(dt)
end

function DemoState:draw(window, alpha)
    self.renderingSystem:draw(window, alpha)
    window:drawText('testTTTTTTTTTTTTTTTTTTTT', 0.0, 100.0, 'hehe', 40)
end

return DemoState
