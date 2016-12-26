set(lib-src
    MetaOutput.cpp
    Options.cpp
    TerrainImages.cpp
    TileGenerator.cpp
    TilePartitionGradient.cpp
    TilePartitionSquares.cpp
    Tileset.cpp
    TilesetGenerator.cpp
)

add_library(wangscape STATIC ${lib-src})
add_executable(Wangscape Main.cpp)

target_link_libraries(Wangscape wangscape)

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

find_package(RapidJSON REQUIRED)
if(RapidJSON_FOUND)
    include_directories(${RAPIDJSON_INCLUDE_DIRS})
endif()
