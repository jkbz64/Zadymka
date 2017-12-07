cmake_minimum_required(VERSION 3.1)
project(Zadymka)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build(Release or Debug)" FORCE)
endif()

# Enforce C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wpedantic -pedantic -pedantic-errors -g")
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

option(DEMO "Build demo?" OFF)
option(TESTS "Build tests?" OFF)

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(Freetype2 REQUIRED)
find_package(Lua53 REQUIRED)
find_package(OpenAL REQUIRED)

file(GLOB_RECURSE HDRS include/*.hpp)
file(GLOB_RECURSE SRCS src/*.cpp)

set(GLAD_C ${CMAKE_SOURCE_DIR}/src/Graphics/glad/glad.c)
set(STB_IMAGE_CPP ${CMAKE_SOURCE_DIR}/src/Graphics/stb_image/stb_image.cpp)
set(STB_VORBIS_C ${CMAKE_SOURCE_DIR}/lib/stb/stb_vorbis.c)

add_library(Zadymka SHARED
		${HDRS}
		${SRCS}
		${GLAD_C}
		${STB_IMAGE_CPP}
		${STB_VORBIS_C}
)

target_include_directories(Zadymka PUBLIC
						${CMAKE_SOURCE_DIR}/include/
						${LUA53_INCLUDE_DIR}
						${CMAKE_SOURCE_DIR}/lib/sol2/
						${CMAKE_SOURCE_DIR}/lib/glm/
						${CMAKE_SOURCE_DIR}/lib/glad/
						${CMAKE_SOURCE_DIR}/lib/stb/
						${CMAKE_SOURCE_DIR}/lib/tinyheaders/
						${OPENGL_INCLUDE_DIR}
						${GLFW_INCLUDE_DIR}
						${FREETYPE2_ROOT_INCLUDE_DIR}
						${OPENAL_INCLUDE_DIR}
)

target_link_libraries(Zadymka
					${OPENGL_LIBRARIES}
					${GLFW_LIBRARIES}
					${FREETYPE2_LIBRARIES}
					${LUA53_LIBRARIES}
					${OPENAL_LIBRARIES}
)

if(DEMO)
	file(COPY demo/ DESTINATION ${CMAKE_BINARY_DIR}/demo/)
endif()

if(TESTS)
    file(COPY tests/ DESTINATION ${CMAKE_BINARY_DIR}/tests/)
endif()
