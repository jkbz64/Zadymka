-- Define basic stuff
dt = 1.0 / 60.0

-- You can implement some syntax sugar for operating on components
function Entity:getPosition()
    if self:has('Position') then
        return Vec2f:new(self:get('Position').position)
    end
end

function Entity:setPosition(x, y)
    if self:has('Position') then
       self:get('Position').position = Vec2f:new(x, y)
    end
end

-- Register components
ECS.registerComponent('Position', {
    position = Vec2f:new(0, 0),
    beforePos = Vec2f:new(0, 0)
})

-- Register entities
ECS.registerEntity('Player', {
    Position = { position = Vec2f:new(10, 0) },
})

-- Register systems
-- TODO

--Register states
ECS.registerState('DemoState', {
    -- You can specify 'starting' components
    systems = {},
    init = function(self)
        self.camera:setCenter(400, 300)
        local entity = self.entityManager:createEntity(ECS.entities["Player"])
    end,
    update = function(self, dt)

    end,
    fixedUpdate = function(self, dt)

    end,
    draw = function(self, window, alpha)

    end,
});

-- Code...
stateManager:setState(ECS.states["DemoState"])
