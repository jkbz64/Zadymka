local System = require('systems/System')
local TestSystem = class('TestSystem', System)

function TestSystem:initialize()
    System.initialize(self)
end

function TestSystem:init(eventManager, entityManager)
    
end

function TestSystem:draw(window)
    window:drawText('test', 0, 0, 'artyard.ttf', 24)
end

return TestSystem
