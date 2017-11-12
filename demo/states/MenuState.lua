local MenuState = class('MenuState')

function MenuState:init()
    self.renderingSystem = self.systemManager:addSystem('RenderingSystem')
    self.testSystem = self.systemManager:addSystem('TestSystem')
    --self.entity = self.entityManager:createEntity('Player')
    --print(self.entity:get('Movable').speed)
end

function MenuState:update(dt)

end

function MenuState:fixedUpdate(dt)
    --self.renderingSystem:fixedUpdate(dt)
    --print(self.renderingSystem)
	--self.entity:move(100 * dt, 0)
end

function MenuState:draw(window, alpha)
	self.testSystem:draw(window, alpha)
end

return MenuState
