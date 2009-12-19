cmake_minimum_required (VERSION 2.6)
project (GPSI)

set(CMAKE_MODULE_PATH "${GPSI_SOURCE_DIR}")

add_definitions (-DTIXML_USE_TICPP -Wall -Werror -pedantic)

add_subdirectory (tinyxml)
include_directories (${GPSI_SOURCE_DIR})
enable_testing ()
add_subdirectory (src)

include(FindSDL)
include(FindSDL_ttf)
include(FindSDL_image)
include(FindSDL_gfx)

if(SDL_FOUND AND SDLTTF_FOUND AND SDLIMAGE_FOUND AND SDLGFX_FOUND)
	add_subdirectory (zabbr)
	add_subdirectory (sdl)
else()
	message(STATUS "SDL Found: ${SDL_FOUND}")
	message(STATUS "SDL TTF Found: ${SDLTTF_FOUND}")
	message(STATUS "SDL Image Found: ${SDLIMAGE_FOUND}")
	message(STATUS "SDL Gfx Found: ${SDLGFX_FOUND}")
endif()
