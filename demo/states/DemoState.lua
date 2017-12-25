-- Demo State
ECS.registerState('DemoState', {
    -- You can specify 'starting' components
    systems = {'RenderingSystem', 'MovementSystem', 'GUISystem'},
    init = function()
        self.camera = Zadymka.Graphics.Camera:new()
        self.camera:setCenter(Math.Vec2f:new(400, 300))

        self.player = self.entityManager:createEntity(ECS.entities["Player"])
        self.eventManager:emit('MapSet', { map = dofile('maps/testmap.lua') })
    end,
    update = function(dt)
        self.systems['GUISystem']:update(dt)
    end,
    fixedUpdate = function(dt)
        self.systems['RenderingSystem']:fixedUpdate(dt)
        self.systems['MovementSystem']:fixedUpdate(dt)
    end,
    draw = function(window, alpha)
        window:setCamera(self.camera)
        self.systems['RenderingSystem']:draw(window, alpha)
        self.systems['GUISystem']:draw(window, alpha)
    end,
});