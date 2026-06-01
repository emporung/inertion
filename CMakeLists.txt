cmake_minimum_required(VERSION 3.10)
project(InertiaProject)

set(EIGEN_INCLUDE_DIR "C:/eigen/eigen-master")

# Путь к freeglut
set(GLUT_INCLUDE_DIR "C:/glut/include")
set(GLUT_LIBRARY "C:/glut/lib/libfreeglut.a")

# Консольная версия (inertia)
add_executable(inertia 
    src/main.cpp
    src/inertia.cpp
)

target_include_directories(inertia PRIVATE 
    ${EIGEN_INCLUDE_DIR}
)

# Графическая версия (visualize)
add_executable(visualize src/visualize.cpp)

target_include_directories(visualize PRIVATE 
    ${GLUT_INCLUDE_DIR}
)

target_link_libraries(visualize 
    ${GLUT_LIBRARY}
    opengl32
    glu32
)