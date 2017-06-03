set(tilegen-src
    TileGenerator.cpp
    TilesetGenerator.cpp)

add_subdirectory(alpha)
add_subdirectory(partition)

add_library(tilegen STATIC ${tilegen-src})

target_include_directories(tilegen PUBLIC ${PROJECT_SOURCE_DIR}/Wangscape)

target_link_libraries(tilegen noise)
target_link_libraries(tilegen wangscape-noise)
target_link_libraries(tilegen wangscape-main)
