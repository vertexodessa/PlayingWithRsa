cmake_minimum_required(VERSION 3.13)  # CMake version check
project(openssl_app)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard


set(CXXOPTS_BUILD_TESTS OFF)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/third_party/ProgramOptions.hxx")

set(TARGET openssl_app)
set(SOURCE_FILES main.cpp)


# openssl
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENSSL openssl)
pkg_search_module(OPENSSL openssl REQUIRED )

#find_package(cxxopts REQUIRED)

#find_package(openssl_mylib REQUIRED)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(${TARGET} ${SOURCE_FILES})

target_compile_options(${TARGET} PUBLIC -fno-exceptions -fdiagnostics-color=always)
target_link_libraries(${TARGET} PUBLIC ${OPENSSL_LIBRARIES} ProgramOptionsHxx openssl_mylib)
target_include_directories(${TARGET} PRIVATE ${OPENSSL_INCLUDE_DIRS} ${PROJECT_BINARY_DIR}/include)

add_custom_target(copy-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/app/assets
    ${CMAKE_BINARY_DIR}/app
    )
