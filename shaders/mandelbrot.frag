#version 330 core

uniform vec2 resolution;
uniform float planeWidth;
uniform float planeHeight;
uniform vec2 offset;
uniform int maxIterations;

out vec4 FragColor;

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
        float log_zn = 0.5 * log(dot(z,z));
        float nu = log(log_zn / log(2.0)) / log(2.0);
        float smoothIter = float(iteration) + 1.0 - nu;

        float t = 0.05 * smoothIter;

        float r = 0.5 + 0.3 * sin(t);
        float g = 0.5 + 0.3 * sin(t + 2.0944); 
        float b = 0.6 + 0.2 * sin(t + 4.1888);

        FragColor = vec4(r, g, b, 1.0);
    }
}