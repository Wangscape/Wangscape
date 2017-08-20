set(noise-module-src
    ${CMAKE_CURRENT_SOURCE_DIR}/Bitmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CornerCombinerBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ModuleWithSources.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NormLPQ.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/QuadrantSelector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Wrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WrapperBase.cpp)

add_subdirectory(codecs)

set(noise-src
    ${noise-src}
    ${noise-module-src}
    PARENT_SCOPE
)
