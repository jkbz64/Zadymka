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

Other libraries used - sol2, freetyp2, stb_image, stb_vorbis
##  Buidling
*Remember to clone recursively or ship libraries by yourself*
```
git clone --recursive https://github.com/jkbz64/Zadymka.git
cd Zadymka
mkdir build && cd build
cmake ..
make -j4
```
