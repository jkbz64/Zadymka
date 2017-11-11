local GameState = class('GameState')

function GameState:initialize()
    self.camera = Camera:new()
    self.eventManager = EventManager:new()
    self.entityManager = EntityManager:new(self.eventManager)
    self.systemManager = SystemManager:new(self.eventManager, self.entityManager)
end
function GameState:init(eventManager, entittyManager) end
function GameState:cleanup() end
function GameState:update(dt) end
function GameState:fixedUpdate(dt) end
function GameState:draw(window, alpha) end

return GameState
