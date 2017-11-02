local GameState = require('states/GameState')
local MenuState = class('MenuState', GameState)

function MenuState:initialize()
    GameState.initialize(self)
end

function MenuState:update(dt)

end

function MenuState:fixedUpdate(dt)
    self.camera:move(1, 0)
end

function MenuState:draw()
    window:drawText('test', 100, 100, 'artyard.ttf', 24)
end

return MenuState
