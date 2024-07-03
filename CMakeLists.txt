cmake_minimum_required(VERSION 3.13)
project(cpp_merkle_patricia_trie)

set(CMAKE_CXX_STANDARD 17)

# Set compiler flags (choose either -Os or -O3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-functions")

# Include directories
include_directories(include)
include_directories(3rdparty/keccak)

# List the source files explicitly
set(SOURCES
    src/main.cpp
    src/trie.cpp
    src/utils.cpp
)

# Use file(GLOB ...) to collect keccak source files
file(GLOB KECCAK_SOURCES
    3rdparty/keccak/*.c
)

# Create library
add_library(${PROJECT_NAME}_lib STATIC
    ${SOURCES}
    ${KECCAK_SOURCES}
)

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
)

# Link libraries (if needed)
target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME}_lib
)
