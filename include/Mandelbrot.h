#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "Shader.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Mandelbrot {
private:
    Shader& shader;
    GLuint quadVAO, quadVBO;

    float zoom = 1.0f;
    glm::vec2 offset = glm::vec2(-0.5f, 0.0f);
    int maxIterations = 500;

public:
    Mandelbrot(Shader& shader);
    ~Mandelbrot();

    void render(int width, int height);
    void zoomIn(float factor);
    void zoomOut(float factor);
    void pan(float dx, float dy);
    void setMaxIterations(int iterations);
};

#endif