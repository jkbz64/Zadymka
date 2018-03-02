local Math = require('Zadymka.Math')

-- There are three types of each variantion of vectors
-- Vec2 -> Vec2f
--         Vec2i
--         Vec2u
-- Vec3 -> Vec3f
--         Vec3i
--         Vec3u
-- Matrix4
-- Utility Math functions
-- Lerp (Vec2f, Vec2f, float), (float, float, float)
-- Normalize (Vec2f), (Vec3f), (Vec4f)
-- Distance (Vec2f), (Vec3f), (Vec4f)
-- Dot product (Vec2f), (Vec3f), (Vec4f)
-- Length (Vec2f), (Vec3f), (Vec4f)

-- Convenient Vec2f factory method
local vec = Math.Vec2(10.0, 10.0) -- Creates Vec2f
print(vec)

-- You can unpack vectors into two/three/four variables using call metafunction ()
local x, y = vec() -- <- unpacking vec into two numbers
print(x, y)

-- Specific types vecs
local v2
v2 = Math.Vec2f:new(1.0, 1.0)
print(v2)
v2 = Math.Vec2i:new(2, 2)
print(v2)
v2 = Math.Vec2u:new(3, 3)

print(vec + v2)

local v3
v3 = Math.Vec3f:new(1.0, 1.0, 1.0)
print(v3)
v3 = Math.Vec3i:new(2, 2, 2)
print(v3)
v3 = Math.Vec3u:new(3, 3)
print(v3)



