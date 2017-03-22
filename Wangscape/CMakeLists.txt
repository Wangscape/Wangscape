set(lib-src
    OptionsManager.cpp
    TerrainImages.cpp
    OptionsPaths.cpp
)

add_subdirectory(metaoutput)
add_subdirectory(noise)
add_subdirectory(tilegen)

add_library(wangscape STATIC ${lib-src})
add_executable(Wangscape Main.cpp)

target_link_libraries(wangscape metaoutput)
target_link_libraries(wangscape noise)
target_link_libraries(wangscape tilegen)
target_link_libraries(wangscape double-conversion)
target_link_libraries(wangscape spotify-json)

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
