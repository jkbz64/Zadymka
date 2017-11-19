local MovableComponent = class('Movable')

function MovableComponent:initialize(t)
    self.speed = t.speed or 0
end

return MovableComponent