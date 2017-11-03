PositionComponent = class('PositionComponent')

function PositionComponent:initialize(m_x, m_y)
	self.x = m_x or 0
	self.y = m_y or 0
end

return PositionComponent
