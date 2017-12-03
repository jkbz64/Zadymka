# Zadymka
**Work in progress**

Zadymka is a 2D game framework lua module.

| Language    | C++14 + Lua   |
|-----------	|-------------	|


| Module    	| Technology    |
|-----------	|-------------	|
| Window / Context |  GLFW 3    |
| Input       | GLFW 3       |
| Rendering 	| OpenGL 3.3  	|
| OpenGL extensions | GLAD    |
| Audio     	| OpenAL      	|
| Math        | glm           |
| Scripting 	| Lua 5.3       |

Other libraries - sol2, freetype2, stb_image, stb_vorbis

##  Building
Before building install GLFW3 / Freetype2 / Lua53 / OpenAL libraries. Header libraries will be cloned recursively, so you don't have to ship them yourself.
```
git clone --recursive https://github.com/jkbz64/Zadymka.git
cd Zadymka
mkdir build && cd build
cmake ..
make -j4
// Optionally run demo, check demo for code
lua init.lua
```

## Usage
Zadymka is a lua module, so you can just copy library file and `require("Zadymka")` in your lua code.
Remember to use function `init` before using other library features.
Check demo directory to see the example code.
