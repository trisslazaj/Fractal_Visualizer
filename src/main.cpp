#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Mandelbrot.h"

// Global Mandelbrot reference for the scroll callback
Mandelbrot* mandelbrotPtr = nullptr;

// Callback to adjust viewport when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Scroll callback for zooming
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        mandelbrotPtr->zoomIn(1.1f); // Zoom in
    } else {
        mandelbrotPtr->zoomOut(1.1f); // Zoom out
    }
}

int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mandelbrot Set", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    // Set the viewport and callback for window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, 800, 600);

    // Initialize the shaders and Mandelbrot class
    Shader shader("../shaders/mandelbrot.vert", "../shaders/mandelbrot.frag");
    Mandelbrot mandelbrot(shader);
    mandelbrotPtr = &mandelbrot; // Assign global pointer for callback access

    // Set the scroll callback
    glfwSetScrollCallback(window, scroll_callback);

    // Variables to track mouse movement for panning
    double lastX = 0.0, lastY = 0.0;
    bool mousePressed = false;

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Get window dimensions
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // Render the Mandelbrot set
        mandelbrot.render(width, height);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Handle panning inputs
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (!mousePressed) {
                // Record the initial mouse position when the button is pressed
                glfwGetCursorPos(window, &lastX, &lastY);
                mousePressed = true;
            } else {
                // Calculate panning offset
                double currentX, currentY;
                glfwGetCursorPos(window, &currentX, &currentY);

                double dx = currentX - lastX;
                double dy = currentY - lastY;

                // Pan the fractal
                mandelbrot.pan(dx * 0.01f, -dy * 0.01f);

                // Update last cursor position
                lastX = currentX;
                lastY = currentY;
            }
        } else {
            mousePressed = false; // Reset mouse state when the button is released
        }
    }

    // Clean up and exit
    glfwTerminate();
    return 0;
}