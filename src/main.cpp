#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "Mandelbrot.hpp"
#include <iostream>
#include <filesystem>
#include <string>

Mandelbrot* mandelbrotPtr = nullptr;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset > 0) {
        mandelbrotPtr->zoomIn(1.1f);
    } else {
        mandelbrotPtr->zoomOut(1.1f);
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

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}