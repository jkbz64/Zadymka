ECS.registerEntity('Player', {
    Position = { position = Vec2f:new(0, 0) },
    Movable = { speed = 300 },
    Physics = { size = Vec2u:new(100, 100) }
})
