#include "Mandelbrot.h"
#include <glm/gtc/type_ptr.hpp>

Mandelbrot::Mandelbrot(Shader& shader) : shader(shader) {
    // Define the quad for rendering (two triangles forming a rectangle)
    float vertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // Unbind VAO
}

Mandelbrot::~Mandelbrot() {
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
}

void Mandelbrot::render(int width, int height) {
    shader.use();
    glBindVertexArray(quadVAO);

    // Pass uniforms to the fragment shader
    glUniform2f(glGetUniformLocation(shader.ID, "resolution"), (float)width, (float)height);
    glUniform2f(glGetUniformLocation(shader.ID, "offset"), offset.x, offset.y);
    glUniform1f(glGetUniformLocation(shader.ID, "zoom"), zoom);
    glUniform1i(glGetUniformLocation(shader.ID, "maxIterations"), maxIterations);

    // Draw the screen quad
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0); // Unbind VAO
}

void Mandelbrot::zoomIn(float factor) {
    zoom *= factor;
}

void Mandelbrot::zoomOut(float factor) {
    zoom /= factor;
}

void Mandelbrot::pan(float dx, float dy) {
    offset += glm::vec2(dx / zoom, dy / zoom);
}

void Mandelbrot::setMaxIterations(int iterations) {
    maxIterations = iterations;
}