#include "Mandelbrot.h"
#include <glm/gtc/type_ptr.hpp>
#include <algorithm> // For std::max

Mandelbrot::Mandelbrot(Shader& shader) : shader(shader) {
    // Define the quad for rendering (two triangles forming a rectangle)
    float vertices[] = {
        -1.0f, -1.0f, // Bottom-left
         1.0f, -1.0f, // Bottom-right
        -1.0f,  1.0f, // Top-left
         1.0f,  1.0f  // Top-right
    };

    // Generate and bind VAO and VBO
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
    shader.use(); // Use the shader program
    glBindVertexArray(quadVAO);

    // Pass uniforms to the fragment shader
    glUniform2f(glGetUniformLocation(shader.ID, "resolution"), static_cast<float>(width), static_cast<float>(height));
    glUniform2f(glGetUniformLocation(shader.ID, "offset"), offset.x, offset.y);
    glUniform1f(glGetUniformLocation(shader.ID, "zoom"), zoom);
    glUniform1i(glGetUniformLocation(shader.ID, "maxIterations"), maxIterations);

    // Draw the screen quad
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0); // Unbind VAO
}

void Mandelbrot::zoomIn(float factor) {
    zoom *= 1.0f + (factor * 0.1f); // Reduce sensitivity by applying smaller increments
}

void Mandelbrot::zoomOut(float factor) {
    zoom /= 1.0f + (factor * 0.1f); // Reduce sensitivity
}

void Mandelbrot::pan(float dx, float dy) {
    offset += glm::vec2(dx / (zoom * 5.0f), dy / (zoom * 5.0f)); // Adjust divisor for smoother panning
}

void Mandelbrot::setMaxIterations(int iterations) {
    maxIterations = std::max(iterations, 1); // Ensure at least 1 iteration
}