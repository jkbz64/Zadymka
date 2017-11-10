local GameState = require('states/GameState')
local MenuState = class('MenuState', GameState)

function MenuState:initialize()
    GameState.initialize(self)
    self.renderingSystem = self.systemManager:addSystem('RenderingSystem')
    self.entity = self.entityManager:createEntity()
    self.entity:addComponent('Movable')
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
