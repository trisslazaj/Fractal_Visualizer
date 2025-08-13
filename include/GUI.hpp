#ifndef GUI_H
#define GUI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <functional>

class GUI {
private:
    bool showColorPanel = true;
    bool showParameterPanel = true;
    
    // Color controls
    int selectedPalette = 0;
    float colorScale = 0.05f;
    float colorOffset = 0.0f;
    bool smoothColoring = true;
    
    // Parameter controls
    int maxIterations = 500;
    float zoomSpeed = 1.1f;
    
    // Callbacks
    std::function<void(int)> onPaletteChanged;
    std::function<void(float)> onColorScaleChanged;
    std::function<void(float)> onColorOffsetChanged;
    std::function<void(bool)> onSmoothColoringChanged;
    std::function<void(int)> onMaxIterationsChanged;
    std::function<void(float)> onZoomSpeedChanged;
    std::function<void()> onResetView;

public:
    GUI(GLFWwindow* window);
    ~GUI();
    
    void beginFrame();
    void render();
    void endFrame();
    
    // Setters for callbacks
    void setPaletteChangedCallback(std::function<void(int)> callback) { onPaletteChanged = callback; }
    void setColorScaleChangedCallback(std::function<void(float)> callback) { onColorScaleChanged = callback; }
    void setColorOffsetChangedCallback(std::function<void(float)> callback) { onColorOffsetChanged = callback; }
    void setSmoothColoringChangedCallback(std::function<void(bool)> callback) { onSmoothColoringChanged = callback; }
    void setMaxIterationsChangedCallback(std::function<void(int)> callback) { onMaxIterationsChanged = callback; }
    void setZoomSpeedChangedCallback(std::function<void(float)> callback) { onZoomSpeedChanged = callback; }
    void setResetViewCallback(std::function<void()> callback) { onResetView = callback; }
    
    // Getters for current values
    int getSelectedPalette() const { return selectedPalette; }
    float getColorScale() const { return colorScale; }
    float getColorOffset() const { return colorOffset; }
    bool getSmoothColoring() const { return smoothColoring; }
    int getMaxIterations() const { return maxIterations; }
    float getZoomSpeed() const { return zoomSpeed; }
};

#endif
