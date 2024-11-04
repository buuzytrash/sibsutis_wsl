set(target_name libparse)

add_library(${target_name} STATIC
    libparse/libparse.cpp
    ../../include/libfts/libparse.hxx)

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
    pugixml
    m
)

set(target_name2 libindex)

add_library(${target_name2} STATIC
    libindex/libindex.cpp
    ../../include/libfts/libindex.hxx)

include(CompileOptions)
set_compile_options(${target_name2})

target_include_directories(
    ${target_name2}
    PUBLIC
    ../../include
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
    ${target_name2}
    PRIVATE
    pugixml
    picosha2
    m
)

set(target_name3 libsearcher)

add_library(${target_name3} STATIC
    libsearcher/libsearcher.cpp
    ../../include/libfts/libsearcher.hxx)

include(CompileOptions)
set_compile_options(${target_name3})

target_include_directories(
    ${target_name3}
    PUBLIC
    ../../include
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
    ${target_name3}
    PRIVATE
    pugixml
    picosha2
    m
)
