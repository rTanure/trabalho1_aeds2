cmake_minimum_required(VERSION 3.28)
project(trabalho1_aeds2 C)

set(CMAKE_C_STANDARD 11)

add_executable(
        trabalho1_aeds2
        main.c
        employee.c
        employee.h
        menu.c
        menu.h
        utils.c
        utils.h
        intercalacaoBasica.c
        intercalacaoBasica.h
        classificacaoInterna.h
        classificacaoInterna.c
)
