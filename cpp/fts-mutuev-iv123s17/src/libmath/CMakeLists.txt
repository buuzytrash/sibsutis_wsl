set(target_name libmath)

add_library(${target_name} STATIC
    libmath/addition.cxx
    ../../include/libmath/addition.hxx)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
    ../../include
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
    ${target_name}
    PRIVATE
    m
)
