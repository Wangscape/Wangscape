set(metaoutput-src
    MetaOutput.cpp
    Tile.cpp
    TileLocation.cpp
    Tileset.cpp
)

add_library(metaoutput STATIC ${metaoutput-src})

target_include_directories(metaoutput PUBLIC ${PROJECT_SOURCE_DIR}/Wangscape)
target_include_directories(metaoutput PUBLIC ${PROJECT_SOURCE_DIR}/lib/spotify-json/include)
target_include_directories(metaoutput PUBLIC ${PROJECT_SOURCE_DIR}/lib/spotify-json/vendor/double-conversion)
