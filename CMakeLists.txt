cmake_minimum_required(VERSION 3.16)

include(cmake/CPM.cmake)

project(glfw-test VERSION 1.0.0 LANGUAGES C CXX)
file(GLOB SOURCES "src/*.cpp" "src/*.hpp" "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

CPMAddPackage(
    NAME GLFW
    GITHUB_REPOSITORY glfw/glfw
    GIT_TAG 3.3.2
    OPTIONS
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
)
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PRIVATE include)