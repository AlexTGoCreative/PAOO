# Proiect PAOO - Demonstrare Concepte OOP in C++
cmake_minimum_required(VERSION 3.10)
project(PAOO_Project VERSION 1.0)

# Setare standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directoare pentru include files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Colectare fisiere sursa
file(GLOB SOURCES "src/*.cpp")

# Executabil
add_executable(paoo_demo ${SOURCES})

# Optiuni de compilare
if(MSVC)
    target_compile_options(paoo_demo PRIVATE /W4)
else()
    target_compile_options(paoo_demo PRIVATE -Wall -Wextra -pedantic)
endif()
