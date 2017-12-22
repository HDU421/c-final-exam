include_directories(${PROJECT_SOURCE_DIR}/lib)

set(MAIN_SOURCE main.c)

add_executable(main ${MAIN_SOURCE})
target_link_libraries(main hotel)
