set(tilegen-alpha-src
    ${CMAKE_CURRENT_SOURCE_DIR}/AlphaCalculatorBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlphaCalculatorLinear.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AlphaCalculatorMax.cpp
)

set(tilegen-src
    ${tilegen-src}
    ${tilegen-alpha-src}
    PARENT_SCOPE
)
