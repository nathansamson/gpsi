cmake_minimum_required (VERSION 2.6)
project (GPSI)

set(CMAKE_MODULE_PATH "${GPSI_SOURCE_DIR}")
option(DEBUG "Set true if debug should be used")

if(DEBUG AND NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE "Debug")
	message(STATUS "Build type: Debug")
elseif(NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE "Release")
	message(STATUS "Build type: Release")
else()
	message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif()


add_definitions (-DTIXML_USE_TICPP -Wall -Werror -pedantic)

add_subdirectory (tinyxml)
include_directories (${GPSI_SOURCE_DIR})
include(FindCPPUnit)
if(CPPUNIT_FOUND)
	enable_testing ()
else()
	message(WARNING " CPPUnit not found, will not build/run tests.")
endif()
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
	
	message(FATAL_ERROR "One of the required SDL libs is not found.")
endif()

find_package(Doxygen)
IF (DOXYGEN_FOUND)
	configure_file(${GPSI_SOURCE_DIR}/Doxyfile.conf.in ${GPSI_BINARY_DIR}/Doxyfile.conf)
	add_custom_target(doc ${DOXYGEN_EXECUTABLE} Doxyfile.conf)
ENDIF()

include(FindAA)
if(AA_FOUND)
	#add_subdirectory(aa)
else()
	message(STATUS "AA not found, will not build AA interface")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
		                            ${CMAKE_SOURCE_DIR}/data
		                            ${CMAKE_BINARY_DIR}/data)
