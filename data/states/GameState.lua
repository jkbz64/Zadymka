local GameState = class('GameState')

function GameState:initialize()
    self.camera = Camera:new()
    self.systemManager = SystemManager:new()
    self.entityManager = EntityManager:new(self.systemManager)
end

function GameState:cleanup()

end

function GameState:update(dt) end
function GameState:fixedUpdate(dt) end
function GameState:draw() end

return GameState
