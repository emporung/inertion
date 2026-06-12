cmake_minimum_required(VERSION 3.10)
project(InertiaProject)

set(EIGEN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(GLUT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/freeglut/include")
set(GLUT_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/external/freeglut/lib/libfreeglut.a")

add_executable(inertia src/main.cpp src/inertia.cpp)
target_include_directories(inertia PRIVATE ${EIGEN_INCLUDE_DIR})

add_executable(visualize src/visualize.cpp)
target_include_directories(visualize PRIVATE ${GLUT_INCLUDE_DIR})
target_link_libraries(visualize ${GLUT_LIBRARY} opengl32 glu32 winmm gdi32)

# ========== Тесты ==========
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_deps/doctest-src"  # явный путь
)
FetchContent_MakeAvailable(doctest)
add_executable(tests tests/test_main.cpp src/inertia.cpp)
target_link_libraries(tests doctest)
target_include_directories(tests PRIVATE ${EIGEN_INCLUDE_DIR})

enable_testing()
add_test(NAME tests COMMAND tests)