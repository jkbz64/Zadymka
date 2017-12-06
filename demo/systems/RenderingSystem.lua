ECS.registerSystem('RenderingSystem', {
init = function(self, ev, em)
    ev:subscribe('EntityCreated', self, self.onEntityCreated)
    self.renderables = {}
end,
fixedUpdate = function(self, dt)
    for _, k in pairs(self.renderables) do
        k:get('Position')._position = k:getPosition()
    end
end,
draw = function(self, window, alpha)
    for _, k in pairs(self.renderables) do
        local position = Math.Lerp(k:get('Position')._position, k:get('Position').position, alpha)
        window:drawRect(position.x, position.y, 100, 100, 255, 0, 0, 255)
    end
end,
onEntityCreated = function(self, event)
    if event.entity:has('Position') then
        table.insert(self.renderables, event.entity)
    end
end
})