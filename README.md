# Zadymka
**Work in progress**

Zadymka is a simple 2D graphics and input Lua module.

| Language    | C++14 + Lua   |
|-----------	|-------------	|


| Module    	| Technology    |
|-----------	|-------------	|
| Window / Context / Input |  GLFW 3    |
| Rendering 	| OpenGL 3.3  	|
| OpenGL extensions | GLAD    |
| Math        | glm           |
| Lua Binding 	| sol2       |
| Other - freetype2, stb_image, ImGui

##  Building
Before building install GLFW3 / Freetype2 / Lua53 libraries. Header libraries will be cloned recursively, so you don't have to ship them yourself.
```
git clone --recursive https://github.com/jkbz64/Zadymka.git
cd Zadymka
mkdir build && cd build
cmake .. //-DEXAMPLES=ON to copy examples to build directory
make -j4

// OPTIONALLY run any example

```

## Usage
Zadymka is a lua module, so you can just copy libraries along with Zadymka.so/dll and `require("Zadymka")` in your lua code.
Remember to use function `init` at the start of your program.
