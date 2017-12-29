-- Demo State
ECS.registerState('DemoState', {
    -- You can specify 'starting' components
    systems = {'RenderingSystem', 'MovementSystem', 'PhysicsSystem'},
    init = function()
        -- Game camera
        self.camera = Zadymka.Graphics.Camera:new()
        self.camera:setCenter(Math.Vec2f:new(400, 300))

        -- GUI camera
        self.guiCamera = Zadymka.Graphics.Camera:new()
        self.guiCamera:setCenter(Math.Vec2f:new(400, 300))

        -- Game logic stuff
        --Create some kind of ground
        local ground = self.entityManager:createEntity("Ground", {
            Position = { position = Vec2f:new(0.0, 10.0) },
            Physics = { size = Vec2u:new(400, 10) }
        })
        -- Create player
        self.entityManager:createEntity("Player")

        self.eventManager:emit('MapSet', { map = dofile('maps/testmap.lua') })
    end,
update = function(dt)
    end,
    fixedUpdate = function(dt)
        self.systems['RenderingSystem']:fixedUpdate(dt)
        self.systems['MovementSystem']:fixedUpdate(dt)
        self.systems['PhysicsSystem']:fixedUpdate(dt)
    end,
    draw = function(window, alpha)
        window:setCamera(self.camera)
        self.systems['RenderingSystem']:draw(window, alpha)
    end,
});