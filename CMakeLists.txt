cmake_minimum_required (VERSION 2.6)
project (GPSI)
set(CPACK_PACKAGE_NAME "s20081398")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 9)
set(CPACK_PACKAGE_VERSION_PATCH beta2)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Nathan Samson")
set(CPACK_SOURCE_IGNORE_FILES
"~$"
"\\\\.git"
"\\\\.gitignore"
"build/"
"data/music/voices-of-space/02 - Stardust.mp3"
"data/music/voices-of-space/03 - Voice Two.mp3"
"data/music/voices-of-space/04 - Planet's Orbit.mp3"
"data/music/voices-of-space/05 - Visions.mp3"
"data/music/voices-of-space/06 - Voice Three.mp3"
"data/music/voices-of-space/07 - Emotional Signals.mp3"
"data/music/voices-of-space/08 - Voice Four.mp3"
"data/music/voices-of-space/09 - Lost in Space.mp3"
"data/music/voices-of-space/11 - Parsecs Part I.mp3"
"data/music/voices-of-space/12 - Parsecs Part II.mp3"
"data/music/voices-of-space/13 - Final Voice.mp3"
"data/music/voices-of-space/14 - Starlight.mp3"
"data/music/voices-of-space/15 - Voices of Space.mp3"
)
SET(CPACK_SOURCE_TBZ2 "OFF")
SET(CPACK_SOURCE_TGZ "ON")
SET(CPACK_SOURCE_TOPLEVEL_TAG "")
SET(CPACK_SOURCE_TZ "OFF")
SET(CPACK_SOURCE_ZIP "OFF")

SET(CPACK_BINARY_DEB "ON")
SET(CPACK_BINARY_STGZ "OFF")
SET(CPACK_BINARY_TGZ "ON")
SET(CPACK_BINARY_TZ "OFF")


include(CPack)

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
include(FindSDL_mixer)

if(SDLMIXER_FOUND)
	add_definitions(-DENABLE_AUDIO)
else()
	message(STATUS "Will build without audio/music support")
endif()

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

install(DIRECTORY data/
        DESTINATION share/gpsi)
