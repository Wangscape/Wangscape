set(src
    Main.cpp
    MetaOutput.cpp
    Options.cpp
    TerrainImages.cpp
    TileGenerator.cpp
    TilePartitionGradient.cpp
    TilePartitionSquares.cpp
    TilesetGenerator.cpp
)

add_executable(Wangscape ${src})

find_package(Boost COMPONENTS system filesystem REQUIRED)
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
