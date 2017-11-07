TestSystem = class('TestSystem')

function TestSystem:initialize()
    print('init')
end

function TestSystem:draw(window)
    print('lul')
    window:drawText('test', 0, 0, 'artyard.ttf', 24)
end
return TestSystem
