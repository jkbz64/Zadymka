local DemoState = class('DemoState')

function DemoState:init()
    self.renderingSystem = self.systemManager:addSystem('RenderingSystem')
    self.movementSystem = self.systemManager:addSystem('MovementSystem')
    self.entity = self.entityManager:createEntity('Player')
    self.camera:setCenter(400, 300)
end

function DemoState:update(dt)

end

function DemoState:fixedUpdate(dt)
    self.renderingSystem:saveCurrentState()
    self.movementSystem:fixedUpdate(dt)
end

function DemoState:draw(window, alpha)
    self.renderingSystem:draw(window, alpha)
    window:drawText('test', 0.0, 100.0, 'artyard.ttf', 48)
    window:drawText('test2', 0.0, -100.0, 'artyard.ttf', 48)
end

return DemoState
