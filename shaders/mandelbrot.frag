#version 330 core

uniform vec2 resolution;
uniform float planeWidth;
uniform float planeHeight;
uniform vec2 offset;
uniform int maxIterations;

// Color control uniforms
uniform int colorPalette;
uniform float colorScale;
uniform float colorOffset;
uniform bool smoothColoring;

out vec4 FragColor;

// Color palette functions
vec3 paletteSineWave(float t) {
    float r = 0.5 + 0.3 * sin(t);
    float g = 0.5 + 0.3 * sin(t + 2.0944); // 2π/3
    float b = 0.6 + 0.2 * sin(t + 4.1888); // 4π/3
    return vec3(r, g, b);
}

vec3 paletteGrayscale(float t) {
    float intensity = 0.5 + 0.5 * sin(t);
    return vec3(intensity);
}

vec3 paletteRainbow(float t) {
    float r = 0.5 + 0.5 * sin(t);
    float g = 0.5 + 0.5 * sin(t + 2.0944);
    float b = 0.5 + 0.5 * sin(t + 4.1888);
    return vec3(r, g, b);
}

vec3 paletteBlueOrange(float t) {
    float r = 0.5 + 0.5 * sin(t);
    float g = 0.3 + 0.3 * sin(t + 1.5708); // π/2
    float b = 0.8 + 0.2 * sin(t + 3.1416); // π
    return vec3(r, g, b);
}

vec3 paletteFire(float t) {
    float r = 0.8 + 0.2 * sin(t);
    float g = 0.3 + 0.3 * sin(t + 1.5708);
    float b = 0.1 + 0.1 * sin(t + 3.1416);
    return vec3(r, g, b);
}

vec3 paletteOcean(float t) {
    float r = 0.1 + 0.1 * sin(t);
    float g = 0.4 + 0.4 * sin(t + 1.5708);
    float b = 0.8 + 0.2 * sin(t + 3.1416);
    return vec3(r, g, b);
}

vec3 getColor(float t) {
    t = t * colorScale + colorOffset;
    
    switch(colorPalette) {
        case 0: return paletteSineWave(t);
        case 1: return paletteGrayscale(t);
        case 2: return paletteRainbow(t);
        case 3: return paletteBlueOrange(t);
        case 4: return paletteFire(t);
        case 5: return paletteOcean(t);
        default: return paletteSineWave(t);
    }
}

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution; 
    uv -= 0.5;

    float x = uv.x * planeWidth  + offset.x;
    float y = uv.y * planeHeight + offset.y;

    vec2 z = vec2(0.0);
    int iteration = 0;
    while (dot(z,z) <= 4.0 && iteration < maxIterations)
    {
        float zx = z.x*z.x - z.y*z.y + x;
        float zy = 2.0*z.x*z.y + y;
        z = vec2(zx, zy);
        iteration++;
    }

    if (iteration == maxIterations) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else {
        float t;
        if (smoothColoring) {
            float log_zn = 0.5 * log(dot(z,z));
            float nu = log(log_zn / log(2.0)) / log(2.0);
            float smoothIter = float(iteration) + 1.0 - nu;
            t = smoothIter;
        } else {
            t = float(iteration);
        }
        
        vec3 color = getColor(t);
        FragColor = vec4(color, 1.0);
    }
}