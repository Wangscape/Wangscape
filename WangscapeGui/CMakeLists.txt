# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

qt5_wrap_ui(UIS_HDRS mainwindow.ui)

# Tell CMake to create the helloworld executable
add_executable(WangscapeGui WIN32 main.cpp mainwindow.cpp ${UIS_HDRS})

# Use the Widgets module from Qt 5.
target_link_libraries(WangscapeGui Qt5::Widgets)
