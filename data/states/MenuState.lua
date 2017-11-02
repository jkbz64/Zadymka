local GameState = require('states/GameState')
local MenuState = class('MenuState', GameState)

function MenuState:initialize()

end

function MenuState:update(dt)

end

function MenuState:draw()
    window:drawText('siema', 100, 100, 'artyard.ttf', 24)
end

return MenuState
