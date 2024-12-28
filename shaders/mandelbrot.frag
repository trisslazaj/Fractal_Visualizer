#version 330 core

in vec2 fragCoord;
out vec4 FragColor;

uniform vec2 resolution; // Canvas resolution
uniform vec2 offset;     // Pan offset
uniform float zoom;      // Zoom level
uniform int maxIterations; // Maximum number of iterations

void main() {
    // Map pixel coordinates to the complex plane
    vec2 c = fragCoord * zoom + offset;

    vec2 z = vec2(0.0);
    int iteration = 0;

    while (dot(z, z) <= 4.0 && iteration < maxIterations) {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        iteration++;
    }

    // Normalize the iteration count to a colour
    float t = float(iteration) / float(maxIterations);
    vec3 color = vec3(t, t * 0.5, t * 0.8); // Simple gradient (replace later)
    FragColor = vec4(color, 1.0);
}