#------------------------------------------------------------------------------
# CMakeLists.txt
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)

project(CloneBand VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#------------------------------------------------------------------------------
# Get source files
#------------------------------------------------------------------------------
file(GLOB_RECURSE SOURCE_FILES source/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)

foreach(HEADER_FILE ${HEADER_FILES})
	get_filename_component(HEADER_DIRECTORY ${HEADER_FILE} DIRECTORY)
	include_directories(${HEADER_DIRECTORY})
endforeach(HEADER_FILE)

#------------------------------------------------------------------------------
# Create executable target
#------------------------------------------------------------------------------
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

#------------------------------------------------------------------------------
# Compiler flags
#------------------------------------------------------------------------------
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g -Wall -Wextra -Wfatal-errors -Wno-variadic-macros)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_14)

#------------------------------------------------------------------------------
# Packages
#------------------------------------------------------------------------------
# - gamekit
#------------------------------------------------------------------------------
find_package(GameKit REQUIRED)
if(NOT GAMEKIT_FOUND)
	message(FATAL_ERROR "gamekit is needed to build the project. Please install it correctly.")
endif()

include_directories(${GAMEKIT_INCLUDE_DIR})
link_directories(${GAMEKIT_LIBRARY_DIRS})

#------------------------------------------------------------------------------
# - tinyxml2
#------------------------------------------------------------------------------
find_package(TinyXml2 REQUIRED)
if(NOT TINYXML2_FOUND)
	message(FATAL_ERROR "tinyxml2 is needed to build the project. Please install it correctly.")
endif()

include_directories(${TINYXML2_INCLUDE_DIR})
link_directories(${TINYXML2_LIBRARY_DIRS})

#------------------------------------------------------------------------------
# - OpenGL
#------------------------------------------------------------------------------
set(OpenGL_GL_PREFERENCE "LEGACY")

find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)

if(NOT OPENGL_FOUND)
	message(FATAL_ERROR "OpenGL not found!")
endif(NOT OPENGL_FOUND)

if(NOT GLM_FOUND)
	message(FATAL_ERROR "glm not found!")
endif(NOT GLM_FOUND)

include_directories(${GLM_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# - SFML
#------------------------------------------------------------------------------
find_package(SFML COMPONENTS audio REQUIRED)
if(NOT SFML_FOUND)
	message(FATAL_ERROR "SFML is needed to build the project. Please install it correctly.")
endif()

include_directories(${SFML_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# - SDL2, SDL2_image, SDL2_mixer
#------------------------------------------------------------------------------
include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)

if(NOT SDL2_FOUND)
	message(FATAL_ERROR "SDL2 not found!")
endif(NOT SDL2_FOUND)

if(NOT SDL2IMAGE_FOUND)
	message(FATAL_ERROR "SDL2_image not found!")
endif(NOT SDL2IMAGE_FOUND)

if(NOT SDL2MIXER_FOUND)
	message(FATAL_ERROR "SDL2_mixer not found!")
endif(NOT SDL2MIXER_FOUND)

if(NOT SDL2TTF_FOUND)
	message(FATAL_ERROR "SDL2_ttf not found!")
endif(NOT SDL2TTF_FOUND)

include_directories(${SDL2_INCLUDE_DIRS}
                    ${SDL2IMAGE_INCLUDE_DIRS}
                    ${SDL2MIXER_INCLUDE_DIRS}
                    ${SDL2TTF_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# Link options
#------------------------------------------------------------------------------
target_link_libraries(${CMAKE_PROJECT_NAME}
                      ${GAMEKIT_LIBRARIES}
                      ${TINYXML2_LIBRARIES}
                      ${OPENGL_LIBRARIES}
                      sfml-system
                      sfml-audio
                      ${SDL2_LIBRARIES}
                      ${SDL2IMAGE_LIBRARIES}
                      ${SDL2MIXER_LIBRARIES}
                      ${SDL2TTF_LIBRARIES})

