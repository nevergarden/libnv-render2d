include_directories(include)
add_library(nv-render2d SHARED nv_render2d.c ./third_party/glad/src/glad.c)
set_target_properties(nv-render2d PROPERTIES
  VERSION 0.0.1
  SOVERSION 0
)
install(
  TARGETS nv-render2d
)
