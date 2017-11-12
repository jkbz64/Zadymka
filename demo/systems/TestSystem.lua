local TestSystem = class('TestSystem')

function TestSystem:init(eventManager, entityManager)

end

function TestSystem:update(dt)
    
end

function TestSystem:draw(window, alpha)
    window:drawText('test', 0, 0, 'artyard.ttf', 24)
end

return TestSystem
