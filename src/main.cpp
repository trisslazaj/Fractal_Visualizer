#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "Mandelbrot.hpp"
#include "GUI.hpp"
#include <iostream>
#include <filesystem>
#include <string>

Mandelbrot* mandelbrotPtr = nullptr;
GUI* guiPtr = nullptr;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset > 0) {
        mandelbrotPtr->zoomIn(mandelbrotPtr->getZoomSpeed());
    } else {
        mandelbrotPtr->zoomOut(mandelbrotPtr->getZoomSpeed());
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 960, "Mandelbrot Set", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    auto resolvePath = [](const std::string& pathFromBin, const std::string& pathFromRepo) {
        namespace fs = std::filesystem;
        if (fs::exists(pathFromBin)) return pathFromBin;
        if (fs::exists(pathFromRepo)) return pathFromRepo;
        return pathFromBin; // fallback
    };

    const std::string vertPath = resolvePath("../shaders/mandelbrot.vert", "shaders/mandelbrot.vert");
    const std::string fragPath = resolvePath("../shaders/mandelbrot.frag", "shaders/mandelbrot.frag");

    Shader shader(vertPath.c_str(), fragPath.c_str());

    Mandelbrot mandelbrot(shader);
    mandelbrotPtr = &mandelbrot;

    GUI gui(window);
    guiPtr = &gui;

    // Set up GUI callbacks
    gui.setPaletteChangedCallback([&mandelbrot](int palette) {
        mandelbrot.setColorPalette(palette);
    });
    
    gui.setColorScaleChangedCallback([&mandelbrot](float scale) {
        mandelbrot.setColorScale(scale);
    });
    
    gui.setColorOffsetChangedCallback([&mandelbrot](float offset) {
        mandelbrot.setColorOffset(offset);
    });
    
    gui.setSmoothColoringChangedCallback([&mandelbrot](bool smooth) {
        mandelbrot.setSmoothColoring(smooth);
    });
    
    gui.setMaxIterationsChangedCallback([&mandelbrot](int iterations) {
        mandelbrot.setMaxIterations(iterations);
    });
    
    gui.setZoomSpeedChangedCallback([&mandelbrot](float speed) {
        mandelbrot.setZoomSpeed(speed);
    });
    
    gui.setResetViewCallback([&mandelbrot]() {
        mandelbrot.resetView();
    });

    glfwSetScrollCallback(window, scroll_callback);

    bool mousePressed = false;
    double lastX = 0.0, lastY = 0.0;

    while (!glfwWindowShouldClose(window))
    {
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

        glViewport(0, 0, fbWidth, fbHeight);

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mandelbrot.render(fbWidth, fbHeight);

        // Handle mouse input (only when not interacting with GUI)
        if (!ImGui::GetIO().WantCaptureMouse) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                if (!mousePressed) {
                    glfwGetCursorPos(window, &lastX, &lastY);
                    mousePressed = true;
                } else {
                    double currentX, currentY;
                    glfwGetCursorPos(window, &currentX, &currentY);

                    double dx = currentX - lastX;
                    double dy = currentY - lastY;

                    mandelbrot.pan(dx, dy, fbWidth, fbHeight);

                    lastX = currentX;
                    lastY = currentY;
                }
            }
            else {
                mousePressed = false;
            }
        }

        // Render GUI
        gui.beginFrame();
        gui.render();
        gui.endFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}