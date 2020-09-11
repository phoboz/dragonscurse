ADD_EXECUTABLE(tmx2bin
    main.cpp
    )

TARGET_LINK_LIBRARIES(tmx2bin
    tmx phoboz tinyxml
    ${ZLIB_LIBRARIES}
    )

INSTALL(TARGETS tmx2bin RUNTIME DESTINATION .)

