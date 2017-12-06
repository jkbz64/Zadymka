-- Demo State
ECS.registerState('DemoState', {
    -- You can specify 'starting' components
    systems = {'RenderingSystem', 'MovementSystem'},
    init = function(self)
        self.camera:setCenter(400, 300)
        self.player = self.entityManager:createEntity(ECS.entities["Player"])
    end,
    update = function(self, dt)

    end,
    fixedUpdate = function(self, dt)
        self.systems['RenderingSystem']:fixedUpdate(dt)
        self.systems['MovementSystem']:fixedUpdate(dt)
    end,
    draw = function(self, window, alpha)
        self.systems['RenderingSystem']:draw(window, alpha)
    end,
});