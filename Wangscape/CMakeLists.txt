set(lib-src
    OptionsManager.cpp
    TerrainImages.cpp
    OptionsPaths.cpp
)

add_subdirectory(logging)
add_subdirectory(metaoutput)
add_subdirectory(noise)
add_subdirectory(tilegen)

add_library(wangscape-main STATIC ${lib-src})
add_executable(Wangscape Main.cpp)

target_link_libraries(wangscape-main metaoutput)
target_link_libraries(wangscape-main noise)
target_link_libraries(wangscape-main tilegen)
target_link_libraries(wangscape-main double-conversion)
target_link_libraries(wangscape-main spotify-json)

target_link_libraries(Wangscape wangscape-main)


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
