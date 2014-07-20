ADD_EXECUTABLE(dragonscurse
    area.cpp object.cpp actor.cpp player.cpp bullet.cpp world_db.cpp world.cpp
    status.cpp knight.cpp human.cpp dragon.cpp
    monster.cpp walker.cpp guardian.cpp lock_flyer.cpp dancer.cpp falling.cpp
    crawler.cpp erupter.cpp meka_dragon.cpp
    material.cpp item.cpp coin.cpp curse.cpp morph.cpp
    object_factory.cpp statusbar.cpp
    room.cpp church.cpp shop.cpp
    main.cpp
    )

TARGET_LINK_LIBRARIES(dragonscurse
    tmx phoboz
    ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLMIXER_LIBRARY} ${SDLTTF_LIBRARY}
    ${TINYXML_LIBRARIES} ${ZLIB_LIBRARIES}
    )

INSTALL(TARGETS dragonscurse RUNTIME DESTINATION .)

