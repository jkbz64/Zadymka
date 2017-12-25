ECS.registerSystem('RenderingSystem', {
    init = function(ev, em)
        ev:subscribe('EntityCreated', self, self.onEntityCreated)
        ev:subscribe('MapSet', self, self.onMapSet)

        self.currentMap = nil
        self.renderables = {}
    end,
    fixedUpdate = function(dt)
        for _, k in pairs(self.renderables) do
            k:get('Position')._position = k:getPosition()
        end
    end,
    draw = function(window, alpha)
        for _, k in pairs(self.renderables) do
            local position = Math.Lerp(k:get('Position')._position, k:get('Position').position, alpha)
            window:drawRect(position.x, position.y, 100, 100, 255, 0, 0, 255)
        end
        if self.currentMap ~= nil then
            window:draw(self.currentMap)
        end
    end,
    onEntityCreated = function(event)
        if event.entity:has('Position') then
            table.insert(self.renderables, event.entity)
        end
    end,
    onMapSet = function(event)
        local map = event.map
        local tileset = Zadymka.Graphics.Texture:new()
        if tileset:loadFromFile(map.tileset.image) == false then
            print('Failed to load tileset')
        end
        self.currentMap = Zadymka.Graphics.Tilemap:new(tileset, Vec2u:new(map.tilewidth, map.tileheight))
        for l = 1, #map.layers do
            local layer = self.currentMap:appendLayer(Vec2u:new(map.layers[l].width, map.layers[l].height))
            for i = 1, #map.layers[l].data do
                layer.data[i] = map.layers[l].data[i]
            end
        end
    end
})