#version 330 core

layout (location = 0) in vec2 aPos;

out vec2 fragCoord;

void main() {
    fragCoord = aPos; // Pass the position to the fragment shader
    gl_Position = vec4(aPos, 0.0, 1.0); // Convert to clip-space
}