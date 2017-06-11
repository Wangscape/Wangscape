set(logging-src
    ConsoleAppender.cpp
    FileAppender.cpp
    Logging.cpp
)

add_library(logging STATIC ${logging-src})

target_include_directories(logging PUBLIC ${PROJECT_SOURCE_DIR}/Wangscape)
