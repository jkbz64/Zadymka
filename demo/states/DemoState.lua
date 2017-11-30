local DemoState = class('DemoState')

function DemoState:init()
    --self.renderingSystem = self.systemManager:addSystem('RenderingSystem')
    --self.movementSystem = self.systemManager:addSystem('MovementSystem')
    --self.entity = self.entityManager:createEntity('Player')
    self.camera:setCenter(400, 300)

    local f = io.open('/home/jkbz/test.png', "rb")
    local content = f:read('*all')
    f:close()
    print(content)
    self.texture = Texture:new()
    self.texture:loadFromMemory(content)
    self.sprite = Sprite:new()
    self.sprite:setTexture(self.texture)
    self.sprite:setSize(300, 300)
end

function DemoState:update(dt)

end

function DemoState:fixedUpdate(dt)
    --self.renderingSystem:saveCurrentState()
    --self.movementSystem:fixedUpdate(dt)
end

function DemoState:draw(window, alpha)
    --self.renderingSystem:draw(window, alpha)
    --window:drawRect(0.0, 100.0, 300, 300, 255, 0, 255, 255)
    --window:draw(self.sprite)
end

return DemoState
