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
-- - create (int, int, string) and (int, int, string, Style(int))
-- - close
-- - clear (r, g, b, a)
-- - display

-- Draw Methods:
-- - draw (Drawable) and (Drawable, Shader)
-- - drawRect (x, y, width, height, r, g, b, a)
-- - drawTexture(texture, x, y)
-- - drawSprite(texture, x, y, w, h)
-- - drawText(text, x, y, font name, character size)

local window = Graphics.Window:new()
-- Create window
window:create(800, 600, 'title', window.Style.Windowed)
window.title = 'some title'

while window.isOpen do
    window:clear(125, 125, 125, 255) -- Clear window
    window:drawRect(0, 0, 100, 100, 255, 0, 0, 255)
    window:display() -- Swap buffers and handle window events
end

-- Aaaaaaannd deinit graphics module at the end
Graphics.deinit()