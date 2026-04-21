cmake_minimum_required(VERSION 3.10)
project(problem_100)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(code main.cpp)

# Optimize for speed and enable reasonable warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Avoid static linking for broader compatibility on OJ runners
    target_compile_options(code PRIVATE -O2 -pipe -Wall -Wextra -Wconversion -Wshadow)
endif()
