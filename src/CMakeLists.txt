include_directories (${GPSI_SOURCE_DIR}/src)

link_directories (${GPSI_BINARY_DIR}/tinyxml)

add_library (si SHARED
               ./game/entitygroup.cpp
               ./game/gameentity.cpp
               ./game/synchronousdriver.cpp
               ./game/bullet.cpp
               ./game/game.cpp
               ./game/levelreader.cpp
               ./game/weapons/weapon.cpp
               ./game/weapons/gun.cpp
               ./game/shipdriver.cpp
               ./game/weaponery.cpp
               ./game/ship.cpp
               ./game/builtinenemydriverfactory.cpp
               ./misc/boundingshape.cpp
               ./misc/boundingbox.cpp
               ./misc/vector2.cpp
           )

add_executable (sitest
                 ./game/tests/bullettest.cpp
                 ./game/tests/shiptest.cpp
                 ./game/tests/gametest.cpp
                 ./game/tests/synchronousdrivertest.cpp
                 ./game/tests/test.cpp
                 ./game/weapons/tests/guntest.cpp
                 ./tests/main.cpp
                 ./misc/tests/vector2test.cpp
                 ./misc/tests/boundingboxtest.cpp
)
target_link_libraries (sitest si ticpp cppunit)
add_test(sitest ${EXECUTABLE_OUTPUT_PATH}/sitest)
