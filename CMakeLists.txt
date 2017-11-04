cmake_minimum_required(VERSION 3.8)
project(OftaSys)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES apps/main.c src/imagemutils.c include/imagemutils.h src/excecoes.c include/excecoes.h src/filtroutils.c include/filtroutils.h)
add_executable(OftaSys ${SOURCE_FILES})
target_link_libraries(OftaSys m)