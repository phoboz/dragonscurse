ADD_EXECUTABLE(dragonscurse
    object.cpp body.cpp actor.cpp player.cpp
    bullet.cpp vector_bullet.cpp solid_bullet.cpp gravity_bullet.cpp
    world_db.cpp world.cpp status.cpp knight.cpp dragon.cpp climber.cpp
    monster.cpp walker.cpp guardian.cpp diver.cpp dancer.cpp falling.cpp
    crawler.cpp erupter.cpp hovering.cpp meka_dragon.cpp mummy_dragon.cpp
    floater.cpp swimmer.cpp shooter.cpp obstacle.cpp
    area.cpp material.cpp coin.cpp curse.cpp morph.cpp
    object_factory.cpp heart.cpp statusbar.cpp status_screen.cpp
    room.cpp church.cpp shop.cpp hospital.cpp chest.cpp
    title_menu.cpp main_menu.cpp sub_menu.cpp
    item_list.cpp equipment_list.cpp save_list.cpp
    main.cpp
    )

TARGET_LINK_LIBRARIES(dragonscurse
    tinyxml tmx phoboz
    ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLMIXER_LIBRARY} ${SDLTTF_LIBRARY}
    ${ZLIB_LIBRARIES}
    )

INSTALL(TARGETS dragonscurse RUNTIME DESTINATION .)

