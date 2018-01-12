local Graphics = require('Zadymka.Graphics')
--Make sure to init graphics module before doing anything Graphics related
Graphics.init()

-- Window properties
-- (Static) - Style { Windowed = 0, Fulscreen = 1, FullscreenWindowed(aka borderless) = 2 }
-- Members:
-- - title
-- - size
-- - camera
-- - isOpen
-- Methods:
-- create: creates window and has two overloads (int, int, string) and (int, int, string, Style(int))
-- setTitle
local window = Graphics.Window:new()
-- Create window
window:create(800, 600, 'title', window.Style.Windowed)
window.title = 'xd'

while window.isOpen do
    window:clear(125, 125, 125, 255) -- Clear window
    window:display() -- Swap buffers and handle window events
end

-- Make sure to deinit graphics module at the end
Graphics.deinit()