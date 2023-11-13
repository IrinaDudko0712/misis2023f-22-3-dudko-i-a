cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(map)
SET(VTK_DIR "C:/dev/vcpkg/vcpkg/installed/x64-windows/include/vtk-9.2" CACHE PATH "VTK directory override" FORCE)
find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  FiltersSources
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR " map: Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(map MACOSX_BUNDLE map.cxx )
  target_link_libraries(map PRIVATE ${VTK_LIBRARIES}
)
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS  map
  MODULES ${VTK_LIBRARIES}
)
find_package(Threads)