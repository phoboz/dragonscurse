CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(DRAGONSCURSE)

FIND_PACKAGE(SDL REQUIRED)
FIND_PACKAGE(SDL_image REQUIRED)
FIND_PACKAGE(SDL_mixer REQUIRED)
FIND_PACKAGE(SDL_ttf REQUIRED)
FIND_PACKAGE(ZLIB REQUIRED)

SET(CMAKE_C_FLAGS -Wall)
INCLUDE_DIRECTORIES(
    ${DRAGONSCURSE_SOURCE_DIR}/include
    ${DRAGONSCURSE_SOURCE_DIR}/include/tinyxml
    ${SDL_INCLUDE_DIR}
    ${SDLIMAGE_INCLUDE_DIR}
    ${SDLMIXER_INCLUDE_DIR}
    ${SDLTTF_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
    )

ADD_SUBDIRECTORY(tinyxml)
ADD_SUBDIRECTORY(tmx)
ADD_SUBDIRECTORY(phoboz)
ADD_SUBDIRECTORY(dragonscurse)
ADD_SUBDIRECTORY(tmx2bin)
#ADD_SUBDIRECTORY(tools)

