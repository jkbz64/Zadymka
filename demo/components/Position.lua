local PositionComponent = class('Position')

function PositionComponent:initialize(t)
    self.x = t.x or 0
    self.y = t.y or 0
    self._x = self.x
    self._y = self.y
end

return PositionComponent