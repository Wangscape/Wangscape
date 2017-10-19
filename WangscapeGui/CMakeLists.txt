# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIR})

qt5_wrap_ui(UIS_HDRS MainWindow.ui OptionsEditor.ui)

# Tell CMake to create the helloworld executable
add_executable(WangscapeGui WIN32 Main.cpp MainWindow.cpp OptionsEditor.cpp CustomGraphicsView.cpp ${UIS_HDRS})

# Use the Widgets module from Qt 5.
target_link_libraries(WangscapeGui wangscape-main)

target_link_libraries(WangscapeGui Qt5::Widgets)

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    link_directories(${Boost_LIBRARY_DIR})
    target_link_libraries(WangscapeGui ${Boost_LIBRARIES})
endif()

find_package(SFML 2 REQUIRED system graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(WangscapeGui ${SFML_LIBRARIES})
endif()
