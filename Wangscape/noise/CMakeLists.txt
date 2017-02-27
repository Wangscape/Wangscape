set(noise-src
    EncodedModuleGroup.cpp
    ModuleGroup.cpp
    ModuleGroupContainer.cpp
    ModuleManager.cpp
    RasterBase.cpp
    RasterImage.cpp
    RasterValues.cpp
)

add_subdirectory(module)

add_library(wangscape-noise STATIC ${noise-src})

target_include_directories(wangscape-noise PUBLIC ${PROJECT_SOURCE_DIR}/Wangscape)
target_include_directories(wangscape-noise PUBLIC ${PROJECT_SOURCE_DIR}/lib/libnoise/src)
target_include_directories(wangscape-noise PUBLIC ${PROJECT_SOURCE_DIR}/lib/spotify-json/include)
target_link_libraries(wangscape-noise noise)
