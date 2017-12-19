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
cmake .. //-DDEMO=ON to enable demo -DTESTS=ON to enable tests
make -j4
// Run tests
busted .
// or Run demo
cp Zadymka.so demo/Zadymka.so // copy lib to demo directory
cd demo/
lua init.lua //run demo
```

## Usage
Zadymka is a lua module, so you can just copy libraries along with Zadymka.so/dll and `require("Zadymka")` in your lua code.
Remember to use function `init` at the start of your program.

## Tests
If you want to run tests you will need to generate `cmake .. -DTESTS=ON` and install busted lua library.
To run tests execute `busted .` in build directory.