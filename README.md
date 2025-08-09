# Dynamic Fractal Visualizer

A dynamic fractal visualization tool written in C++ using the OpenGL library. This project generates and renders fractals such as the Mandelbrot set with real-time interaction, zooming, panning, and customizable rendering options.

## Features

- Real-time rendering of fractals (e.g., Mandelbrot set, Julia set).
- Interactive zoom and pan functionality.
- High-resolution rendering for intricate fractal details.
- Dynamic parameter adjustments (e.g., colour schemes, iteration limits).
- Smooth animations and user-friendly interface.

## Getting Started

### Prerequisites

To run this project, you need:

- A modern C++ compiler (e.g., GCC, Clang, or MSVC) with C++17 support.
- OpenGL libraries (version 3.3 or higher recommended).
- A build system such as `CMake` or `Make`.
- GLFW library for window and input management.
- GLAD library for OpenGL function loading.
- Any other dependencies (to be added as the project progresses).

## Build Instructions (explicit, step-by-step)

The project uses CMake and fetches GLFW/GLM automatically (no manual install required for those). GLAD is vendored.

### Windows (Visual Studio 2022 Build Tools)

1) Install tools (once):

```powershell
winget install Kitware.CMake
winget install Git.Git
winget install Microsoft.VisualStudio.2022.BuildTools
# Then open Visual Studio Installer and ensure "Desktop development with C++" workload is installed
```

2) Open the correct developer shell (important):

- Start menu → Visual Studio 2022 → x64 Native Tools Command Prompt for VS 2022
  (This preloads MSVC, NMake, and the SDKs.)

3) Configure + build (choose ONE of the following generators):

- NMake (simple, single-config):
```cmd
cd C:\Users\tani\Fractal_Visualizer
cmake -S . -B build_nmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build_nmake
```

- Visual Studio solution (multi-config):
```cmd
cd C:\Users\tani\Fractal_Visualizer
cmake -S . -B build_vs -G "Visual Studio 17 2022" -A x64
cmake --build build_vs --config Release
```

4) Run:

```cmd
build_nmake\bin\fractal_visualizer.exe
:: or
build_vs\bin\fractal_visualizer.exe
```

Notes:
- If you see "generator mismatch" errors, use a fresh build directory (e.g., `build_nmake2`).
- If `cl`/`nmake` are not found, you’re not in a proper developer shell.

### macOS

```bash
brew install cmake git
git clone <this repo>
cd Fractal_Visualizer
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/bin/fractal_visualizer
```

### Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install -y build-essential cmake git xorg-dev libglu1-mesa-dev
git clone <this repo>
cd Fractal_Visualizer
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/bin/fractal_visualizer
```

## Runtime

- Zoom: mouse wheel
- Pan: left mouse drag

Resources (`shaders/`) are copied next to the build directory automatically. Running from the repo root or from the `bin/` folder both work.