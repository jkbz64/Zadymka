# Zadymka [![Build Status](https://travis-ci.org/jkbz64/Zadymka.svg?branch=master)](https://travis-ci.org/jkbz64/Zadymka)
**Work in progress**

Zadymka is a simple 2D graphics (and Input) module. It also has built-in ImGui support.

| Language    | C++14  |
|-----------	|-------------	|

***Technology Chart***

|           |               |
|-----------	|-------------	|
| Window / Context / Input |  GLFW 3    |
| Rendering 	| OpenGL 3.3  	|
| OpenGL extensions | GLAD    |
| Math        | glm           |
| Lua Binding 	| sol2       |
| Font loading | Freetype2 |
| Image loading | stb_image |
| Other |ImGui |

##  Building
Before building install GLFW3 / Freetype2 / any lua version( 5.2 and 5.3 were the only one I tested so far though) libraries. Header libraries will be cloned recursively, so you don't have to ship them yourself.
```
git clone --recursive https://github.com/jkbz64/Zadymka.git
cd Zadymka
mkdir build && cd build
cmake .. //-DEXAMPLES=ON to copy examples to build directory
make -j4
```

## Usage
1. Copy `Zadymka.dll or .so` along with other `.dll's(freetype.dll and glfw3.dll(maybe?))` to the project directory
2. `local Zadymka = require('Zadymka')` in your code
3. `Zadymka.init()` or `Zadymka.Graphics.init()` to init graphics module (may be done automagically in the future)
4. You are ready to go :)

Check out examples directory to see Zadymka usage.

## Quickstart

```
local Graphics = require('Zadymka.Graphics')
Graphics.init()
local window = Graphics.Window:new()
window:create(800, 600, 'title', window.Style.Windowed)
window.title = 'some title'

local font = Graphics.Font:new()
font:loadFromFile('arial.ttf')

local text = Graphics.Text:new()
text:setString('test')
text:setPosition(100, 100)

while window.isOpen do
    window:clear(125, 125, 125, 255) -- Clear window
    window:draw(text)
    window:drawRect(0, 0, 100, 100, 255, 0, 0, 255)
    window:display()
end

Graphics.deinit()
```

## Docs?
.. Not now? I guess?
If you want to know usertypes/bindings check out src/(module name).cpp's.
