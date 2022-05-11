find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/lib/include)
add_executable(draw_quad main.c)
target_link_libraries(draw_quad PRIVATE nv-render2d ${GLUT_LIBRARIES})
