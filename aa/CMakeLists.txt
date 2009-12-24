include_directories (${GPSI_SOURCE_DIR}/src
                     ${GPSI_SOURCE_DIR}/tclap
                     ${AA_INCLUDE_DIR})

add_executable (siaa
                ./main.cpp)

target_link_libraries (siaa si ticpp 
                             ${AA_LIBRARY})
