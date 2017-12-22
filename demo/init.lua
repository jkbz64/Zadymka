Zadymka = require("Zadymka")
Zadymka.init()
ECS = Zadymka.ECS
Math = Zadymka.Math
Entity = Zadymka.ECS.Entity
Vec2f = Zadymka.Math.Vec2f
Vec2u = Zadymka.Math.Vec2u
class = require("lib.middleclass")

-- Register our ECS stuff -- notice that these can be reloaded during runtime
-- Components
dofile('components/Position.lua')
-- Entities
dofile('entities/Player.lua')
-- Systems
dofile('systems/RenderingSystem.lua')
dofile('systems/MovementSystem.lua')
-- States
dofile('states/DemoState.lua')

local window = Zadymka.Graphics.Window:new()
window:create(800, 600, 'Zadymka', 0)

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
	Zadymka.ImGui.NewFrame()
	local alpha = accumulator / dt
	window:setCamera(demoState.camera)
	window:clear(0, 125, 125, 255)
	demoState:draw(window, alpha)
	Zadymka.ImGui.Text('Test')
	Zadymka.ImGui.Render()
	window:display()
	Timer.sleep(1)
end

Zadymka.deinit()
