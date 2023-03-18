cmake_minimum_required(VERSION 3.16)
project(gunslinger CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(WARNINGS_AS_ERRORS OFF)
set(BUILD_SHARED_LIBS OFF)

# if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
#     add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion)
#     add_compile_options("$<$<CONFIG:DEBUG>:-fsanitize=address,undefined>")
# 	add_compile_options(-o ../bin/testProgram.exe)
#     add_link_options("$<$<CONFIG:DEBUG>:-fsanitize=address,undefined>")
# endif()

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories("src/include")
file(GLOB SOURCES "src/*.cpp")
add_executable(gunslinger ${SOURCES})

target_link_libraries(gunslinger PRIVATE sfml-graphics)
target_compile_definitions(gunslinger PRIVATE FONT_PATH="${CMAKE_SOURCE_DIR}/data")