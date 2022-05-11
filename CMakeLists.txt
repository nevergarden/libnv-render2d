cmake_minimum_required(VERSION 3.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(INSTALL_PKGCONFIG_DIR "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")

project(libnv-render2d
  LANGUAGES C
  HOMEPAGE_URL "https://github.com/nevergarden/libnv-render2d"
  DESCRIPTION "A tiny 2d opengl renderer."
  VERSION 0.0.1
)

add_subdirectory(lib)
add_subdirectory(example/draw_quad)
