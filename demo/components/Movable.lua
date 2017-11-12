local MovableComponent = class('MovableComponent')

function MovableComponent:initialize(t)
    self.speed = t.speed or 0
end

return MovableComponent