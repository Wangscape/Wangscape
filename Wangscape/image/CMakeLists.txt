set(image-src
    CopyRegionParameters.cpp
    Image.cpp
    TileRearrangement.cpp
    TileRearranger.cpp
)

add_library(image STATIC ${image-src})

target_include_directories(image PUBLIC ${PROJECT_SOURCE_DIR}/Wangscape)
