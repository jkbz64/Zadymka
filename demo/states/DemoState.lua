-- Demo State
ECS.registerState('DemoState', {
    -- You can specify 'starting' components
    systems = {'RenderingSystem', 'MovementSystem'},
    init = function()
        self.camera:setCenter(Math.Vec2f:new(400, 300))
        self.player = self.entityManager:createEntity(ECS.entities["Player"])
        self.systems['RenderingSystem']:onTileMapSet({ tilemap = dofile('maps/testmap.lua') })
    end,
    update = function(dt)

    end,
    fixedUpdate = function(dt)
        self.systems['RenderingSystem']:fixedUpdate(dt)
        self.systems['MovementSystem']:fixedUpdate(dt)
    end,
    draw = function(window, alpha)
        self.systems['RenderingSystem']:draw(window, alpha)
    end,
});