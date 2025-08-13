#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "Shader.hpp"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Mandelbrot {
private:
    Shader& shader;
    GLuint quadVAO, quadVBO;

    float zoom = 1.0f;
    float zoomSpeed = 1.1f;

    float basePlaneWidth  = 3.0f;
    float basePlaneHeight = 2.0f;

    glm::vec2 offset = glm::vec2(-0.5f, 0.0f);
    
    int maxIterations = 500;
    float minZoom = 0.000001f;
    float maxZoom = 100000.0f;
    
    // Color parameters
    int colorPalette = 0;
    float colorScale = 0.05f;
    float colorOffset = 0.0f;
    bool smoothColoring = true;

public:
    Mandelbrot(Shader& shader);
    ~Mandelbrot();

    void render(int width, int height);
    void zoomIn(float factor);
    void zoomOut(float factor);
    void pan(double dxPixels, double dyPixels, int screenW, int screenH);
    void setMaxIterations(int iterations);
    
    // Color control methods
    void setColorPalette(int palette);
    void setColorScale(float scale);
    void setColorOffset(float offset);
    void setSmoothColoring(bool smooth);
    void setZoomSpeed(float speed);
    
    // Getters
    float getZoomSpeed() const { return zoomSpeed; }
    
    // Reset view
    void resetView();

private:
    void updateUniforms();
};

#endif