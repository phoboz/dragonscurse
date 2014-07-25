ADD_EXECUTABLE(dragonscurse
    object.cpp body.cpp actor.cpp player.cpp bullet.cpp gravity_bullet.cpp
    world_db.cpp world.cpp status.cpp knight.cpp human.cpp dragon.cpp
    monster.cpp walker.cpp guardian.cpp lock_flyer.cpp dancer.cpp falling.cpp
    crawler.cpp erupter.cpp meka_dragon.cpp
    area.cpp material.cpp item.cpp coin.cpp curse.cpp morph.cpp
    object_factory.cpp statusbar.cpp status_screen.cpp
    room.cpp church.cpp shop.cpp chest.cpp
    main_menu.cpp sub_menu.cpp item_list.cpp equipment_list.cpp main.cpp
    )

TARGET_LINK_LIBRARIES(dragonscurse
    tinyxml tmx phoboz
    ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLMIXER_LIBRARY} ${SDLTTF_LIBRARY}
    ${ZLIB_LIBRARIES}
    )

INSTALL(TARGETS dragonscurse RUNTIME DESTINATION .)

