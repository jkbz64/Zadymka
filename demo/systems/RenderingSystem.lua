local Tilemap = class('Tilemap')

function Tilemap:initialize(data)
    self.mapSize = Vec2u.new(data.width or 0, data.height or 0)
    self.tileSize = Vec2u.new(data.tilewidth or 0, data.tileheight or 0)
    local combinedTileset = Zadymka.Graphics.RenderTexture.new()
    local maxWidth = 0
    local maxHeight = 0
    for i = 1, #data.tilesets do
        local tileset = data.tilesets[i]
        if tileset.imagewidth > maxWidth then maxWidth = tileset.imagewidth end
        maxHeight = maxHeight + tileset.imageheight
    end
    combinedTileset:create(768, 448)
    combinedTileset:clear(255, 255, 255, 255)
    for i = 1, #data.tilesets do
        local tileset = data.tilesets[i]
        local tempTexture = Zadymka.Graphics.Texture.new()
        tempTexture:loadFromFile(tileset.image)
        combinedTileset:drawTexture(tempTexture, 0, 0, 768, 448)
    end
    combinedTileset:display()
    self.combinedTexture = combinedTileset:getTexture()
end

function Tilemap:draw(window)
    window:drawTexture(self.combinedTexture, 0, 0)
end

ECS.registerSystem('RenderingSystem', {
    init = function(ev, em)
        ev:subscribe('EntityCreated', self, self.onEntityCreated)
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
            self.currentMap:draw(window)
        end
    end,
    onEntityCreated = function(event)
        if event.entity:has('Position') then
            table.insert(self.renderables, event.entity)
        end
    end,
    onTileMapSet = function(event)
        self.currentMap = Tilemap:new(event.tilemap)
    end
})