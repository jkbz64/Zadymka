# Zadymka
**Work in progress**

Zadymka aims to be an 2D game framework.

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
```
