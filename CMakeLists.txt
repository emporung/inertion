cmake_minimum_required(VERSION 3.10)
project(InertiaProject)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.12)
    cmake_policy(SET CMP0077 NEW)
endif()
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)


FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG 3.4.0
)

FetchContent_MakeAvailable(eigen)


FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)


FetchContent_Declare(
    freeglut
    GIT_REPOSITORY https://github.com/freeglut/freeglut.git
    GIT_TAG v3.4.0
)
set(FREEGLUT_BUILD_SHARED_LIBS ON)
set(FREEGLUT_BUILD_STATIC_LIBS OFF)
FetchContent_MakeAvailable(freeglut)


add_executable(inertia src/main.cpp src/inertia.cpp)
target_link_libraries(inertia Eigen3::Eigen)


add_executable(visualize src/visualize.cpp)
target_link_libraries(visualize freeglut opengl32 glu32 winmm gdi32)
target_include_directories(visualize PRIVATE ${freeglut_SOURCE_DIR}/include)

add_executable(tests tests/test_main.cpp src/inertia.cpp)
target_link_libraries(tests doctest Eigen3::Eigen)
enable_testing()
add_test(NAME tests COMMAND tests)

add_custom_command(TARGET visualize POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:freeglut>
        $<TARGET_FILE_DIR:visualize>
) 