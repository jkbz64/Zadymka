return {
    systems = {"RenderingSystem", "MovementSystem"},
    init = function(self)
        self.camera:setCenter(400, 300)
    end,
    update = function(self, dt)

    end,
    fixedUpdate = function(self, dt)
        self.systems["RenderingSystem"]:saveCurrentState()
    end,
    draw = function(self, window, alpha)
        self.systems["RenderingSystem"]:draw(window, alpha)
    end,
}
