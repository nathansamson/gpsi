include_directories (${GPSI_SOURCE_DIR}/src
                     ${GPSI_SOURCE_DIR}/zabbr
                     ${GPSI_SOURCE_DIR}/tclap
                     ${SDL_INCLUDE_DIR}
                     ${SDLIMAGE_INCLUDE_DIR}
                     ${SDLTTF_INCLUDE_DIR}
                     ${SDLGFX_INCLUDE_DIR})

add_executable (gpsi
                  ./sdlship.cpp
                  ./sdlusership.cpp
                  ./main.cpp
                  ./siwindow.cpp
                  ./gamepanel.cpp
                  ./normalgamepanel.cpp
                  ./demogamepanel.cpp
                  ./highscorepanel.cpp
                  ./optionspanel.cpp
                  ./sdlbullet.cpp
                  ./sdlclusterbomb.cpp
                  ./sdlentityfactory.cpp
                  ./sdlkeyboardinputdriver.cpp
                  ./sdlgamevisualizer.cpp
                  ./sdldriverfactory.cpp)

target_link_libraries (gpsi si ticpp zabbr
                             ${SDL_LIBRARY}
                             ${SDLIMAGE_LIBRARY}
                             ${SDLTTF_LIBRARY}
                             ${SDLGFX_LIBRARY})

if(SDLMIXER_FOUND)
	include_directories (${SDLMIXER_INCLUDE_DIR})
	target_link_libraries (gpsi ${SDLMIXER_LIBRARY})
endif()

install(TARGETS gpsi
        RUNTIME DESTINATION bin)
