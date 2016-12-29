set(lib-src
    MetaOutput.cpp
    Options.cpp
    OptionsManager.cpp
    TerrainImages.cpp
    TileGenerator.cpp
    TilePartitionGradient.cpp
    TilePartitionSquares.cpp
    Tile.cpp
    TileLocation.cpp
    Tileset.cpp
    TilesetGenerator.cpp
)

add_library(wangscape STATIC ${lib-src})
add_executable(Wangscape Main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/Wangscape)
include_directories(${PROJECT_SOURCE_DIR}/lib/spotify-json/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/spotify-json/vendor/double-conversion)
target_link_libraries(Wangscape wangscape)
target_link_libraries(Wangscape spotify-json)


find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    link_directories(${Boost_LIBRARY_DIR})
    target_link_libraries(Wangscape ${Boost_LIBRARIES})
endif()

find_package(SFML 2 REQUIRED system graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Wangscape ${SFML_LIBRARIES})
endif()
