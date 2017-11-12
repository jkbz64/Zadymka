local MenuState = class('MenuState')

function MenuState:init()
    self.renderingSystem = self.systemManager:addSystem('RenderingSystem')
    self.entity = self.entityManager:createEntity('Player')
end

function MenuState:update(dt)

end

function MenuState:fixedUpdate(dt)
    self.renderingSystem:fixedUpdate(dt)
    self.entity:move(100 * dt, 0)
end

function MenuState:draw(window, alpha)
	self.renderingSystem:draw(window, alpha)
end

return MenuState
