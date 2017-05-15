set(logging-src
    Logging.cpp
)

add_library(logging STATIC ${logging-src})

target_include_directories(logging PUBLIC ${PROJECT_SOURCE_DIR}/Wangscape)
