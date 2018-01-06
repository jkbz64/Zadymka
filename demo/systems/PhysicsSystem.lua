local bump = require('lib.bump')

ECS.registerSystem('PhysicsSystem', {
    init = function(ev, em)
        ev:subscribe('EntityCreated', self, self.onEntityCreated)
        ev:subscribe('EntityDestroyed', self, self.onEntityDestroyed)
        ev:subscribe('MapSet', self, self.onMapSet)

        self.world = bump.newWorld()
        self.movables = {}
    end,
    fixedUpdate = function(dt)
        for _, v in pairs(self.movables) do
            local oldPos = v:getPosition()
            local newPos = v:getPosition() + v:getVelocity() * dt

            local dx, dy, cols, len = self.world:move(v, newPos.x, newPos.y)
            if len > 0 then
                print('collision')
            end
            v:setPosition(dx, dy)
        end
    end,
    onMapSet = function(event)
        --local map = event.map
        --
    end,
    onEntityCreated = function(event)
        local entity = event.entity
        if entity:has('Physics') then
            entity.events:subscribe('UpdatedPosition', self, self.onEntityUpdatedPosition)
            entity.events:subscribe('ChangedSize', self, self.onEntityChangedSize)
            local position = entity:getPosition()
            local size = entity:getSize()
            if(size.x > 0 and size.y > 0) then
                self.world:add(entity, position.x, position.y, size.x, size.y)
            end
            if entity:has('Movable') then
                 table.insert(self.movables, entity)
            end
        end
    end,
    onEntityDestroyed = function(event)
        local entity = event.entity
        if entity:has('Physics') then
            if self.world:hasItem(entity) then
                self.world:remove(entity)
            end
            if entity:has('Movable') then
                for _, v in pairs(self.movables) do
                    if v == entity then self.movables[_] = nil end
                end
            end
        end
    end,
    onEntityUpdatedPosition = function(event)
        if not self.world:hasItem(event.entity) then
            local entity = event.entity
            local position = entity:getPosition()
            local size = entity:getSize()
            if size.x > 0 and size.y > 0 then
                self.world:add(entity, position.x, position.y, size.x, size.y)
            end
        else
            self.world:update(event.entity, event.pos.x, event.pos.y)
        end
    end,
    onEntityChangedSize = function(event)
        local entity = event.entity
        local position = entity:getPosition()
        local size = entity:getSize()
        if not self.world:hasItem(event.entity) then
            if size.x > 0 and size.y > 0 then
                self.world:add(entity, position.x, position.y, size.x, size.y)
            end
        else
            self.world:update(entity, position.x, position.y, event.size.x, event.size.y)
        end
    end
})