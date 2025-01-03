#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Mandelbrot.h"
#include <iostream>

// Global reference for scroll callback
Mandelbrot* mandelbrotPtr = nullptr;

// Scroll callback for zoom in/out
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset > 0) {
        // Zoom in by a factor of 1.1
        mandelbrotPtr->zoomIn(1.1f);
    } else {
        // Zoom out by a factor of 1.1
        mandelbrotPtr->zoomOut(1.1f);
    }
}

int main()
{
    // 1) Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2) Create the window
    GLFWwindow* window = glfwCreateWindow(1280, 960, "Mandelbrot Set", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 3) Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 4) Create and load the shader
    Shader shader("../shaders/mandelbrot.vert", "../shaders/mandelbrot.frag");

    // 5) Create Mandelbrot object
    Mandelbrot mandelbrot(shader);
    mandelbrotPtr = &mandelbrot;

    // 6) Set scroll callback for zoom
    glfwSetScrollCallback(window, scroll_callback);

    // Variables for mouse-panning
    bool mousePressed = false;
    double lastX = 0.0, lastY = 0.0;

    // 7) Main render loop
    while (!glfwWindowShouldClose(window))
    {
        // A) Query the *actual* framebuffer size each frame
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

        // B) Update the viewport to match the entire framebuffer
        glViewport(0, 0, fbWidth, fbHeight);

        // C) Clear the screen
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // D) Render the Mandelbrot
        mandelbrot.render(fbWidth, fbHeight);

        // E) Handle mouse input for panning
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

        // F) Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 8) Clean up
    glfwTerminate();
    return 0;
}