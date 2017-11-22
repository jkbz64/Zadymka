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
    --self.renderingSystem:draw(window, alpha)
    window:drawRect(0, 0, 100, 100,   math.random(0, 255), 0, 0, 255)
    window:drawRect(0, 105, 100, 100, 0, math.random(0, 255), 0, 255)
    window:drawRect(0, 205, 100, 100, 0, 0, math.random(0, 255), 255)
    window:drawRect(0, 305, 100, 100, math.random(0, 255), math.random(0, 255), 0, 255)
    window:drawRect(0, 405, 100, 100, 0, math.random(0, 255), math.random(0, 255), 255)
    window:drawRect(0, 506, 100, 100, math.random(0, 255), 0, math.random(0, 255), 255)
    window:drawRect(0, 606, 100, 100, math.random(0, 255), math.random(0, 255), math.random(0, 255), 255)
end

return DemoState
