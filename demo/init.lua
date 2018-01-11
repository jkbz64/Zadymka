Zadymka = require("Zadymka")
Zadymka.init()

ECS = Zadymka.ECS
Math = Zadymka.Math
Entity = Zadymka.ECS.Entity
Vec2f = Zadymka.Math.Vec2f
Vec2u = Zadymka.Math.Vec2u
class = require("lib.middleclass")

--[[ Register our ECS stuff -- notice that these can be reloaded during runtime
-- Components
dofile('components/Position.lua')
dofile('components/Movable.lua')
dofile('components/Physics.lua')
-- Entities
dofile('entities/Player.lua')
dofile('entities/Ground.lua')
-- Systems
dofile('systems/RenderingSystem.lua')
dofile('systems/MovementSystem.lua')
dofile('systems/PhysicsSystem.lua')
-- States
dofile('states/DemoState.lua')
--]]

local v = Zadymka.Math.Vec2f:new(10, 15)
local c, x = v()
print(c, x)

local window = Zadymka.Graphics.Window:new()
window:create(Vec2(800, 600), 'Zadymka', 0)

local demoState = ECS.createState('DemoState')

local Timer = Zadymka.Timer
dt = 1.0 / 20.0
local currentTime = Timer.getTime()
local accumulator = 0.0

while window:isOpen() do
	local newTime = Timer.getTime()
	local frameTime = newTime - currentTime
	if frameTime > 0.25 then
		frameTime = 0.25
	end
	currentTime = newTime
    accumulator = accumulator + frameTime

    demoState:update(dt)
    while accumulator >= dt do
        demoState:fixedUpdate(dt)
        accumulator = accumulator - dt
	end
	local alpha = accumulator / dt
    window:clear(0, 125, 125, 255)
    window:setCamera(demoState.camera)
	demoState:draw(window, alpha)
	window:display()
	Timer.sleep(1)
end

Zadymka.deinit()
