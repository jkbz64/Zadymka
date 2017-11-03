local GameState = require('states/GameState')
local MenuState = class('MenuState', GameState)

function MenuState:initialize()
    GameState.initialize(self)
    local entity = self.entityManager:createEntity()
    print(entity:getID())
end

function MenuState:update(dt)

end

function MenuState:fixedUpdate(dt)
    self.camera:move(100 * dt, 0)
end

function MenuState:draw()
    window:drawText('test', 500, 100, 'artyard.ttf', 24)
end

return MenuState
