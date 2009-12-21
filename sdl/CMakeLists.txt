include_directories (${GPSI_SOURCE_DIR}/src
                     ${GPSI_SOURCE_DIR}/zabbr
                     ${SDL_INCLUDE_DIR}
                     ${SDLIMAGE_INCLUDE_DIR}
                     ${SDLTTF_INCLUDE_DIR}
                     ${SDLGFX_INCLUDE_DIR})

add_executable (sisdl
                  ./sdlship.cpp
                  ./main.cpp
                  ./siwindow.cpp
                  ./gamecontroller.cpp
                  ./sdlbullet.cpp
                  ./sdlclusterbomb.cpp
                  ./sdlentityfactory.cpp
                  ./sdlkeyboardinputdriver.cpp
                  ./sdlgamevisualizer.cpp
                  ./sdldriverfactory.cpp)

target_link_libraries (sisdl si ticpp zabbr
                             ${SDL_LIBRARY}
                             ${SDLIMAGE_LIBRARY}
                             ${SDLTTF_LIBRARY}
                             ${SDLGFX_LIBRARY})
