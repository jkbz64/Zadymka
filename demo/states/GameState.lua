local GameState = class('GameState')

function GameState:initialize()
    self.camera = Camera:new()
    self.eventManager = EventManager:new()
    self.systemManager = SystemManager:new(self.eventManager)
    self.entityManager = EntityManager:new(self.eventManager)
end

function GameState:cleanup()

end

function GameState:update(dt) end
function GameState:fixedUpdate(dt) end
function GameState:draw(window, alpha) end

return GameState
