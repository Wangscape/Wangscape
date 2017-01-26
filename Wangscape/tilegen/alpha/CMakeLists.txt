set(tilegen-alpha-src
    ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorLinear.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorMax.cpp
)

set(tilegen-src
    ${tilegen-src}
    ${tilegen-alpha-src}
    PARENT_SCOPE
)
