set(tst-src
    main.cpp
    TestCalculatorMax.cpp
    TestCalculatorDither.cpp
    TestCalculatorTopTwo.cpp
    removeWhitespace.cpp
    DocumentationPath.cpp
    TestCartesianPower.cpp
    TestCoordinatePacker.cpp
    TestCornerCombiner.cpp
    TestEncodedModuleGroup.cpp
    TestIPow.cpp
    TestMetaOutput.cpp
    TestModuleDecode.cpp
    TestNormLPQ.cpp
    TestOptions.cpp
    TestRequiringOptions.cpp
    TestTilePartitionerSquares.cpp
    TestTilesetGenerator.cpp)

add_executable(WangscapeTest ${tst-src})

target_link_libraries(WangscapeTest wangscape)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if(Threads_FOUND)
    target_link_libraries(WangscapeTest Threads::Threads)
endif()

find_package(GTest REQUIRED)
if(GTest_FOUND)
    include_directories(${GTest_INCLUDE_DIR})
    target_link_libraries(WangscapeTest ${GTEST_BOTH_LIBRARIES})
endif()

find_package(Boost COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    link_directories(${Boost_LIBRARY_DIR})
    target_link_libraries(WangscapeTest ${Boost_LIBRARIES})
endif()

find_package(SFML 2 REQUIRED system graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(WangscapeTest ${SFML_LIBRARIES})
endif()
