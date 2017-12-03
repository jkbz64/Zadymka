Zadymka = require("Zadymka")
ECS = Zadymka.ECS
Entity = Zadymka.ECS.Entity
Vec2f = Zadymka.Math.Vec2f

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

function Entity:move(dx, dy)
	if self:has('Position') then
		local pos = self:getPosition()
		self:get('Position').position = Vec2f:new(pos.x + dx, pos.y + dy)
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
ECS.registerSystem('MovementSystem', {
    init = function(self, ev, em)
		ev:subscribe('EntityCreated', self, self.onEntityCreated)
		self.player = nil
    end,
    update = function(self, dt)
       
    end,
    fixedUpdate = function(self, dt)
		if self.player ~= nil then
			self.player:move(250 * dt, 0)
		end
    end,
    draw = function(self, window, alpha)

    end,
    onEntityCreated = function(self, event)
		self.player = event.entity
    end
})

--Register states
ECS.registerState('DemoState', {
    -- You can specify 'starting' components
    systems = {'MovementSystem'},
    init = function(self)
        self.camera:setCenter(400, 300)
        self.player = self.entityManager:createEntity(ECS.entities["Player"])
    end,
    update = function(self, dt)

    end,
    fixedUpdate = function(self, dt)
		self.systems['MovementSystem']:fixedUpdate(dt)
    end,
    draw = function(self, window, alpha)
		local position = self.player:getPosition()
		window:drawRect(position.x, position.y, 100, 100, 255, 0, 0, 255)
    end,
});

local demoState = Zadymka.ECS.GameState:new(ECS.states["DemoState"])

local window = Zadymka.Graphics.Window:new()
window:create(800, 600, 'Zadymka', WindowStyle.Windowed)

local Timer = Zadymka.Timer
dt = 1.0 / 60.0
local currentTime = Timer.getTime()
local accumulator = 0.0

while(window:isOpen()) do
	local newTime = Timer.getTime()
	local frameTime = newTime - currentTime
	if frameTime > 0.25 then
		frameTime = 0.25
	end
	currentTime = newTime
	accumulator = accumulator + frameTime
	
	demoState:update(dt)
	
	while(accumulator >= dt) do
		demoState:fixedUpdate(dt)
		accumulator = accumulator - dt
	end

	local alpha = accumulator / dt
	window:setCamera(demoState.camera)
	window:clear(0, 125, 125)
	demoState:draw(window, alpha)
	window:display()
	Timer.sleep(1)
end

Zadymka.deinit()
