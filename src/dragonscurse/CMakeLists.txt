ADD_EXECUTABLE(dragonscurse object.cpp dragon.cpp main.cpp)
TARGET_LINK_LIBRARIES(dragonscurse
    tmx phoboz
    ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${TINYXML_LIBRARIES} ${ZLIB_LIBRARIES}
    )

