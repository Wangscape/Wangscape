set(tilegen-alpha-src
    ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorDither.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorLinear.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorMax.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorTopTwo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorMode.cpp
)

set(tilegen-src
    ${tilegen-src}
    ${tilegen-alpha-src}
    PARENT_SCOPE
)
