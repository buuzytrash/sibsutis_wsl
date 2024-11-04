set(target_name libsud)
add_library(${target_name} STATIC
sudoku.cpp
../../include/lib/sudoku.hpp)

include (CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
    ../../include
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
    ${target_name}
    m
)