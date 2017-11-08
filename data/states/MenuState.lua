local GameState = require('states/GameState')
local MenuState = class('MenuState', GameState)

function MenuState:initialize()
    GameState.initialize(self)
    self.system = self.systemManager:addSystem('RenderingSystem')
    self.entity = self.entityManager:createEntity()
end

function MenuState:update(dt)

end

function MenuState:fixedUpdate(dt)
	self.system:fixedUpdate(dt)
	self.entity:move(100 * dt, 0)
end

function MenuState:draw(window, alpha)
	print(alpha)
	self.system:draw(window, alpha)
end

return MenuState
