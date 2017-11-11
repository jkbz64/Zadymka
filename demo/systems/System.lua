local System = class('System')

function System:initialize() self.requiredComponents = {} end
function System:init(eventManager, entityManager) end
function System:update(dt) end
function System:fixedUpdate(dt) end
function System:draw(window, alpha) end

return System