ADD_EXECUTABLE(dragonscurse
    object.cpp actor.cpp player.cpp bullet.cpp world.cpp
    knight.cpp human.cpp dragon.cpp
    monster.cpp walker.cpp guardian.cpp lock_flyer.cpp dancer.cpp falling.cpp
    meka_dragon.cpp
    object_factory.cpp statusbar.cpp main.cpp
    )
TARGET_LINK_LIBRARIES(dragonscurse
    tmx phoboz
    ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLMIXER_LIBRARY}
     ${TINYXML_LIBRARIES} ${ZLIB_LIBRARIES}
    )

