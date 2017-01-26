set(noise-module-src
    ${CMAKE_CURRENT_SOURCE_DIR}/CornerCombinerBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ModuleFactories.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ModuleGroup.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NormLPQ.cpp)

set(noise-src
    ${noise-src}
    ${noise-module-src}
    PARENT_SCOPE
)
