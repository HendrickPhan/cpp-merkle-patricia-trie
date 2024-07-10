cmake_minimum_required(VERSION 3.13)
project(cpp_merkle_patricia_trie)

set(CMAKE_CXX_STANDARD 17)

# Set compiler flags (choose either -Os or -O3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finline-functions")

# Find Protobuf package
find_package(Protobuf REQUIRED)
find_package(absl REQUIRED)

# Include Protobuf directories
include_directories(${Protobuf_INCLUDE_DIRS})


set(Protobuf_PROTOC_EXECUTABLE /usr/bin/protoc)

# Generate the C++ sources from the .proto files
# Define the .proto files
set(PROTO_FILES
  proto/merkle_patricia_trie.proto
)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})


# Include directories
include_directories(include)
include_directories(3rdparty/keccak)
include_directories(3rdparty)
# List the source files explicitly
set(SOURCES
    src/main.cpp
    src/trie.cpp
    src/utils.cpp
    src/node.cpp
    src/hash_node.cpp
    src/value_node.cpp
    src/short_node.cpp
    src/full_node.cpp
    src/encoding.cpp
    src/hasher.cpp
    src/trie_reader.cpp
    src/logger.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
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
# Link Protobuf libraries
target_link_libraries(${PROJECT_NAME} 
  ${Protobuf_LIBRARIES}
  absl::log_internal_check_op
)
