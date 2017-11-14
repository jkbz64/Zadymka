cmake_minimum_required(VERSION 3.1)
project(Zadymka)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build(Release or Debug)")

# Enforce C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -pedantic -pedantic-errors -g")
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

option(DEMO "Build demo?" ON)

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(Lua53 REQUIRED)

#
file(GLOB_RECURSE HDRS include/*.hpp)
file(GLOB_RECURSE SRCS src/*.cpp)

set(STB_IMAGE_CPP ${CMAKE_SOURCE_DIR}/lib/stb_image/stb_image.cpp)
set(GLAD_C ${CMAKE_SOURCE_DIR}/lib/glad/glad.c)

add_executable(Zadymka
	${HDRS}
	${SRCS}
	${STB_IMAGE_CPP}
	${GLAD_C}
)


target_include_directories(Zadymka PUBLIC
						${CMAKE_SOURCE_DIR}/include/
						${LUA53_INCLUDE_DIR}
						${CMAKE_SOURCE_DIR}/lib/sol2/
						${CMAKE_SOURCE_DIR}/lib/glm/
						${CMAKE_SOURCE_DIR}/lib/glad/
						${CMAKE_SOURCE_DIR}/lib/stb/
						${OPENGL_INCLUDE_DIR}
						${GLFW_INCLUDE_DIR}
)

target_link_libraries(Zadymka
					${LUA53_LIBRARIES}
					${OPENGL_LIBRARIES}
					${GLFW_LIBRARIES}
)

if(DEMO)
	file(COPY demo/ DESTINATION ${CMAKE_BINARY_DIR})
endif()
