#include "Mandelbrot.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include <iostream>  

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

void Mandelbrot::render(int width, int height)
{
    // Use the shader
    shader.use();

    // Bind VAO, etc.
    glBindVertexArray(quadVAO);

    // Pass resolution to the fragment shader
    glUniform2f(glGetUniformLocation(shader.ID, "resolution"),
                static_cast<float>(width),
                static_cast<float>(height));

    // Pass planeWidth, planeHeight, offset, etc. 
    float planeWidth  = basePlaneWidth / zoom;   // example
    float planeHeight = basePlaneHeight / zoom;  // example

    glUniform1f(glGetUniformLocation(shader.ID, "planeWidth"),  planeWidth);
    glUniform1f(glGetUniformLocation(shader.ID, "planeHeight"), planeHeight);

    glUniform2f(glGetUniformLocation(shader.ID, "offset"),
                offset.x, offset.y);

    glUniform1i(glGetUniformLocation(shader.ID, "maxIterations"), maxIterations);
    
    // Pass color uniforms
    glUniform1i(glGetUniformLocation(shader.ID, "colorPalette"), colorPalette);
    glUniform1f(glGetUniformLocation(shader.ID, "colorScale"), colorScale);
    glUniform1f(glGetUniformLocation(shader.ID, "colorOffset"), colorOffset);
    glUniform1i(glGetUniformLocation(shader.ID, "smoothColoring"), smoothColoring ? 1 : 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}

void Mandelbrot::zoomIn(float factor) {
    float k = 0.01f;
    float scaledFactor = 1.0f + 
        (factor - 1.0f) / (1.0f + k * (zoom - 1.0f));

    zoom *= scaledFactor;
    if (zoom > maxZoom) {
        zoom = maxZoom;
    }
}

void Mandelbrot::zoomOut(float factor) {
    float k = 0.01f;
    float scaledFactor = 1.0f + 
        (factor - 1.0f) / (1.0f + k * (zoom - 1.0f));

    zoom /= scaledFactor;
    if (zoom < minZoom) {
        zoom = minZoom;
    }
}

void Mandelbrot::pan(double dxPixels, double dyPixels, int screenW, int screenH)
{
    // 1) Figure out how wide/tall the fractal plane is at this zoom
    float planeWidth  = basePlaneWidth  / zoom;
    float planeHeight = basePlaneHeight / zoom;

    // 2) Convert the mouse delta in pixels to fraction of the screen
    double fracX = dxPixels / (double)screenW;
    double fracY = dyPixels / (double)screenH;

    // 3) Now convert that fraction to fractal-plane coords
    //    e.g. dragging full screen width => shift entire planeWidth
    float shiftX = (float)fracX * planeWidth;
    float shiftY = (float)fracY * planeHeight;

    // 4) Update offset
    // Typically "drag right" means offset.x *decreases*, 
    // but pick the sign convention you prefer:
    offset.x -= shiftX;  
    offset.y += shiftY; 
}

void Mandelbrot::setMaxIterations(int iterations) {
    maxIterations = std::max(iterations, 1);
}

void Mandelbrot::setColorPalette(int palette) {
    colorPalette = std::max(0, std::min(palette, 5)); // Clamp to 0-5
}

void Mandelbrot::setColorScale(float scale) {
    colorScale = std::max(0.001f, std::min(scale, 0.5f)); // Clamp to reasonable range
}

void Mandelbrot::setColorOffset(float offset) {
    colorOffset = offset; // No clamping needed
}

void Mandelbrot::setSmoothColoring(bool smooth) {
    smoothColoring = smooth;
}

void Mandelbrot::setZoomSpeed(float speed) {
    zoomSpeed = std::max(1.01f, std::min(speed, 2.0f)); // Clamp to reasonable range
}

void Mandelbrot::resetView() {
    zoom = 1.0f;
    offset = glm::vec2(-0.5f, 0.0f);
    maxIterations = 500;
    colorPalette = 0;
    colorScale = 0.05f;
    colorOffset = 0.0f;
    smoothColoring = true;
    zoomSpeed = 1.1f;
}