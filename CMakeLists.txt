cmake_minimum_required(VERSION 3.10)
project(assignment2 C)

set(CMAKE_C_STANDARD 99)

# Add executable
add_executable(Pokedex
        Pokedex.c
        Pokemon.c
        Pokemon.h
        Defs.h
)

# Optional: Add compiler warnings
target_compile_options(Pokedex PRIVATE -Wall -Wextra)
