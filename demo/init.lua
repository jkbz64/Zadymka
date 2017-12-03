Zadymka = require("Zadymka")
Zadymka.init()


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
ECS.registerSystem('TestSystem', {
    init = function(self)
        print('lul')
        self.kupa = 50
        print('lul')
    end,
    update = function(self, dt)
        print('lul')
    end,
    fixedUpdate = function(self, dt)


    end,
    draw = function(self, window, alpha)

    end,
    testf = function(self, t)
        print(t)
    end,
    eventCallbacks = {

    }
})

--Register states
ECS.registerState('DemoState', {
    -- You can specify 'starting' components
    systems = {'TestSystem'},
    init = function(self)
        self.camera:setCenter(400, 300)
        local entity = self.entityManager:createEntity(ECS.entities["Player"])
    end,
    update = function(self, dt)
        --sself.systems['TestSystem']:update(dt)
        self.systems['TestSystem']:testf(10)
    end,
    fixedUpdate = function(self, dt)

    end,
    draw = function(self, window, alpha)

    end,
});

-- Code...
stateManager:setState(ECS.states["DemoState"])




-- Deinitialize zadymka
Zadymka.deinit()
