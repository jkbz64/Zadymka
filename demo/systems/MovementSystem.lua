Keyboard = Zadymka.Input["Keyboard"]
Keys = Keyboard.Keys

ECS.registerSystem('MovementSystem', {
    init = function(ev, em)
        ev:subscribe('EntityCreated', self, self.onEntityCreated)
        self.player = nil
    end,
    update = function(dt)

    end,
    fixedUpdate = function(dt)
        if self.player ~= nil then
            local speed = 250
            if Keyboard.isKeyPressed(Keys["A"]) then
                self.player:move(-speed * dt, 0)
            end
            if Keyboard.isKeyPressed(Keys["D"]) then
                self.player:move(speed * dt, 0)
            end
            if Keyboard.isKeyPressed(Keys["W"]) then
                self.player:move(0, -speed * dt)
            end
            if Keyboard.isKeyPressed(Keys["S"]) then
                self.player:move(0, speed * dt)
            end
        end
    end,
    onEntityCreated = function(event)
        self.player = event.entity
    end
})