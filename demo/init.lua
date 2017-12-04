Zadymka = require("Zadymka")
ECS = Zadymka.ECS
Math = Zadymka.Math
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
    _position = Vec2f:new(0, 0)
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

ECS.registerSystem('RenderingSystem', {
    init = function(self, ev, em)
        ev:subscribe('EntityCreated', self, self.onEntityCreated)
        self.renderables = {}
    end,
    fixedUpdate = function(self, dt)
        for _, k in pairs(self.renderables) do
            k:get('Position')._position = k:getPosition()
            print(k:get('Position')._position)
        end
    end,
    draw = function(self, window, alpha)
        for _, k in pairs(self.renderables) do
            print(k:get('Position')._position)
            print(k:get('Position').position)
            local position = Math.Lerp(k:get('Position')._position, k:get('Position').position, alpha)
            window:drawRect(position.x, position.y, 100, 100, 255, 0, 0, 255)
        end
    end,
    onEntityCreated = function(self, event)
        if event.entity:has('Position') then
            table.insert(self.renderables, event.entity)
        end
    end
})

--Register states
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

local demoState = ECS.createState('DemoState')

local window = Zadymka.Graphics.Window:new()
window:create(800, 600, 'Zadymka', WindowStyle.FullscreenWindowed)

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
