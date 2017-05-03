set(tilegen-partition-src
    ${CMAKE_CURRENT_SOURCE_DIR}/DebugWriter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TilePartitionerBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TilePartitionerGradient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TilePartitionerNoise.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TilePartitionerSquares.cpp
)

set(tilegen-src
    ${tilegen-src}
    ${tilegen-partition-src}
    PARENT_SCOPE
)
