ADD_EXECUTABLE(dragonscurse main.cpp)
TARGET_LINK_LIBRARIES(dragonscurse
    tmx phoboz
    ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${TINYXML_LIBRARIES}
    )

