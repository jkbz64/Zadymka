local MovementSystem = class('MovementSystem')

function MovementSystem:init(ev, em)

end

function MovementSystem:fixedUpdate(dt)
    if Keyboard:isKeyPressed(Keys.A) then
        self.entities[1]:move(-100 * dt, 0)
    elseif Keyboard:isKeyPressed(Keys.D) then
        self.entities[1]:move(100 * dt, 0)
    end

    if Keyboard:isKeyPressed(Keys.W) then
        self.entities[1]:move(0, -100 * dt)
    elseif Keyboard:isKeyPressed(Keys.S) then
        self.entities[1]:move(0, 100 * dt)
    end
end

function MovementSystem:require()
    return {"Movable"}
end


return MovementSystem