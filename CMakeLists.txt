cmake_minimum_required(VERSION 3.10)
project(SQLInterpreter CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define the executable for the main application/example
add_executable(sql_interpreter_example examples/main.cpp)

# Define the library for the interpreter core logic
add_library(sql_interpreter_core
    src/lexer/token.cpp
    src/lexer/lexer.cpp
    # Add other .cpp files from src/ here as they are created
    # e.g.:
    # src/parser/parser.cpp
    # src/ast/ast_node.cpp # If it had a .cpp
    # src/common/error.cpp # If it had a .cpp
    # src/interpreter.cpp
)

# Specify include directories for the library and executable
# This allows #include <token.h> instead of #include <lexer/token.h>
# if you move headers to the include/sql_interpreter directory
# For now, we'll use relative paths from src files.

target_include_directories(sql_interpreter_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ast
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common
)

target_include_directories(sql_interpreter_example PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src # To find includes like "lexer/token.h" from main.cpp
)

# Link the example executable against the interpreter library
target_link_libraries(sql_interpreter_example PRIVATE sql_interpreter_core)

# Catch2 integration
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# Enable testing
enable_testing()


add_executable(lexer_test tests/lexer_test.cpp)
target_include_directories(lexer_test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(lexer_test PRIVATE sql_interpreter_core Catch2::Catch2WithMain)

# Install rules (optional)
# install(TARGETS sql_interpreter_example DESTINATION bin)
# install(TARGETS sql_interpreter_core DESTINATION lib)
# install(DIRECTORY include/sql_interpreter/ DESTINATION include/sql_interpreter)


# --- Instructions for building ---
# 1. Create a build directory: mkdir build && cd build
# 2. Configure CMake: cmake ..
# 3. Build the project: make (or cmake --build .)
# 4. Run the example: ./sql_interpreter_example (from the build directory)
