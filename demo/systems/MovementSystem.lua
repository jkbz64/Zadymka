local MovementSystem = class('MovementSystem')

function MovementSystem:init(ev, em)
    self.entityManager = em
    ev:subscribe('EntityCreated', self, MovementSystem.onEntityCreated)
    self.player = nil
end

function MovementSystem:fixedUpdate(dt)
    if self.player ~= nil then
        --self.player:get('Physics').body:setVelocity(100, 0)
    end
 	--[[self.player:move(speed, 0)
        if Keyboard:isKeyPressed(Keys.A) then
            self.player:move(-speed, 0)
        elseif Keyboard:isKeyPressed(Keys.D) then
            self.player:move(speed, 0)
        end

        if Keyboard:isKeyPressed(Keys.W) then
            self.player:move(0, -speed)
        elseif Keyboard:isKeyPressed(Keys.S) then
            self.player:move(0, speed)
        end
    end]]--
end

function MovementSystem:onEntityCreated(e)
    local entity = e.entity
    if(entity:has('Identity') and entity:get('Identity').isPlayer == true) then
        self.player = entity
    end
end

return MovementSystem
