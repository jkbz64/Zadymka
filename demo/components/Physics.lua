ECS.registerComponent('Physics', {
    size = Vec2u:new(0, 0),
    type = 'static'
})

function ECS.Entity:setSize(w, h)
    if self:has('Physics') then
        self:get('Physics').size = Vec2u:new(w, h)
        self.events:emit('ChangedSize', { entity = self, size = self:get('Physics').size })
    end
end

function ECS.Entity:getSize()
    if self:has('Physics') then
        return Vec2u:new(self:get('Physics').size)
    else
        return Vec2u:new(0, 0)
    end
end

function ECS.Entity:updatePosition(x, y)
    if self:has('Physics') then
        if self:has('Position') then self:get('Position').position = Vec2f:new(x, y) end
        self.events:emit('UpdatedPosition', { entity = self, pos = Vec2f:new(x, y) })
    end
end