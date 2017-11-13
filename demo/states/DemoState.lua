local DemoState = class('DemoState')

function DemoState:init()
    self.renderingSystem = self.systemManager:addSystem('RenderingSystem')
    self.movementSystem = self.systemManager:addSystem('MovementSystem')
    self.entity = self.entityManager:createEntity('Player')
end

function DemoState:update(dt)

end

function DemoState:fixedUpdate(dt)
    self.renderingSystem:saveCurrentState()
    self.movementSystem:fixedUpdate(dt)
end

function DemoState:draw(window, alpha)
	self.renderingSystem:draw(window, alpha)
end

return DemoState
