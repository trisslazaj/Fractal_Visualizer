#version 330 core

// Input vertex position (from VBO, attribute location 0)
layout (location = 0) in vec2 aPos;

// Output to the fragment shader
out vec2 fragCoord;

void main() {
    // Pass the position to the fragment shader (normalized device coordinates)
    fragCoord = aPos;

    // Set the vertex position in clip-space
    gl_Position = vec4(aPos, 0.0, 1.0);
}