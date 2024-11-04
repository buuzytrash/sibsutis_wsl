set(target_name_1 add)

add_executable(${target_name_1})

include(CompileOptions)
set_compile_options(${target_name_1})

target_sources(
    ${target_name_1}
    PRIVATE
    add.cxx
)

target_link_libraries(
    ${target_name_1}
    PRIVATE
    libmath
    cxxopts
)
set(target_name_2 app)

add_executable(${target_name_2})

set_compile_options(${target_name_2})

target_sources(
    ${target_name_2}
    PRIVATE
    main.cxx
)

target_link_libraries(
    ${target_name_2}
    PRIVATE
    libsearcher
    libparse
    libindex
    cxxopts
    pugixml
    picosha2
    replxx
)

set(target_name_3 indexer)
add_executable(${target_name_3})
set_compile_options(${target_name_3})
target_sources(
    ${target_name_3}
    PRIVATE
    indexer.cxx
)
target_link_libraries(
    ${target_name_3}
    PRIVATE
    libsearcher
    libparse
    libindex
    cxxopts
    pugixml
    picosha2
    replxx
    rapidcsv
)


set(target_name_4 searcher)
add_executable(${target_name_4})
set_compile_options(${target_name_4})
target_sources(
    ${target_name_4}
    PRIVATE
    searcher.cxx
)
target_link_libraries(
    ${target_name_4}
    PRIVATE
    libsearcher
    libparse
    libindex
    cxxopts
    pugixml
    picosha2
    replxx
    rapidcsv
)