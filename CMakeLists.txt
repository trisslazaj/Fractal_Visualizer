cmake_minimum_required(VERSION 3.14)
project(FractalVisualizer)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Allow legacy subprojects (e.g., older GLM releases) to configure under CMake 4.x
# by raising the minimum policy compatibility to 3.5 as suggested by CMake diagnostics.
if(NOT DEFINED CMAKE_POLICY_VERSION_MINIMUM)
  set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
endif()

# Silence OpenGL deprecation warnings on macOS
if(APPLE)
  add_definitions(-DGL_SILENCE_DEPRECATION)
endif()

# Dependencies
find_package(OpenGL REQUIRED)

# Try to find GLFW via package manager; fallback to FetchContent
find_package(glfw3 CONFIG QUIET)
if(NOT glfw3_FOUND)
  find_package(GLFW3 QUIET)
endif()

if(NOT TARGET glfw AND NOT TARGET glfw3::glfw AND NOT TARGET GLFW::GLFW)
  include(FetchContent)
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
  )
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(glfw)
endif()

# Determine GLFW target name
set(GLFW_TARGET "")
if(TARGET glfw)
  set(GLFW_TARGET glfw)
elseif(TARGET glfw3::glfw)
  set(GLFW_TARGET glfw3::glfw)
elseif(TARGET GLFW::GLFW)
  set(GLFW_TARGET GLFW::GLFW)
endif()
if(GLFW_TARGET STREQUAL "")
  message(FATAL_ERROR "GLFW not found and could not be fetched.")
endif()

# GLM: try find, else fetch
find_package(glm CONFIG QUIET)
if(NOT TARGET glm::glm)
  include(FetchContent)
  FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
  )
  FetchContent_MakeAvailable(glm)
endif()

# GLAD from local source
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Executable
add_executable(fractal_visualizer
  src/main.cpp
  src/Mandelbrot.cpp
  src/Shader.cpp
)

target_include_directories(fractal_visualizer PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(fractal_visualizer
  PRIVATE
    OpenGL::GL
    ${GLFW_TARGET}
    glad
    glm::glm
)

# Output directory for the built executable
set_target_properties(fractal_visualizer PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Ensure consistent output dir for multi-config generators (e.g., Visual Studio)
foreach(cfg IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
  set_target_properties(fractal_visualizer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/bin)
endforeach()

# Copy shaders next to build tree (so ../shaders from bin works)
add_custom_command(TARGET fractal_visualizer POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/shaders
          ${CMAKE_BINARY_DIR}/shaders
)