local DemoState = class('DemoState')

function DemoState:init()
    --self.renderingSystem = self.systemManager:addSystem('RenderingSystem')
    --self.movementSystem = self.systemManager:addSystem('MovementSystem')
    --self.entity = self.entityManager:createEntity('Player')
    self.camera:setCenter(400, 300)
    print('')
end

function DemoState:update(dt)

end

function DemoState:fixedUpdate(dt)
    --self.renderingSystem:saveCurrentState()
    --self.movementSystem:fixedUpdate(dt)
end

function DemoState:draw(window, alpha)
    --self.renderingSystem:draw(window, alpha)
    --window:drawRect(0.0, 100.0, 300, 300, 255, 0, 255, 255)
    --window:draw(self.sprite)
end

return DemoState
