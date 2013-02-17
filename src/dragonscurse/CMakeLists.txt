ADD_EXECUTABLE(dragonscurse
    object.cpp actor.cpp player.cpp bullet.cpp world.cpp
    knight.cpp human.cpp dragon.cpp
    walker.cpp guardian.cpp object_factory.cpp main.cpp
    )
TARGET_LINK_LIBRARIES(dragonscurse
    tmx phoboz
    ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${TINYXML_LIBRARIES} ${ZLIB_LIBRARIES}
    )

