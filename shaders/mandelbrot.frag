#version 330 core

precision highp float; // Use high precision for calculations
in vec2 fragCoord;
out vec4 FragColor;

uniform vec2 resolution; 
uniform vec2 offset;
uniform float zoom;
uniform int maxIterations;

void main() {
    vec2 c = (fragCoord - vec2(0.5)) * vec2(resolution.x / resolution.y, 1.0) * zoom + offset;

    vec2 z = vec2(0.0);
    int iteration = 0;

    while (dot(z, z) <= 4.0 && iteration < maxIterations) {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        iteration++;
    }

    float t = float(iteration) / float(maxIterations);
    vec3 color = vec3(t, t * 0.5, t * 0.8);
    FragColor = vec4(color, 1.0);
}