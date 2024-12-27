cmake_minimum_required(VERSION 3.10)
project(FractalVisualizer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Silence OpenGL deprecation warnings on macOS
add_definitions(-DGL_SILENCE_DEPRECATION)

# Add the executable
add_executable(fractal_visualizer src/main.cpp)

# Include directories for glad and GLFW
include_directories(
    ${CMAKE_SOURCE_DIR}/include  # Glad header files
    /opt/homebrew/include        # GLFW headers
)

# Link directories for libraries
link_directories(
    /opt/homebrew/lib            # GLFW library directory
)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(fractal_visualizer OpenGL::GL)

# Add glad as a library
add_library(glad src/glad.c)
target_link_libraries(glad OpenGL::GL)

# Link glad and GLFW to the executable
target_link_libraries(fractal_visualizer glad /opt/homebrew/lib/libglfw.dylib)

# Optional: Set the output directory for the built executable
set_target_properties(fractal_visualizer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Optional: Add debug information
set(CMAKE_BUILD_TYPE Debug)