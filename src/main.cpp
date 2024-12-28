#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Mandelbrot.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
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
    }

    // Clean up and exit
    glfwTerminate();
    return 0;
}