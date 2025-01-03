#version 330 core

uniform float planeWidth;
uniform float planeHeight;
uniform vec2  offset;
uniform vec2 resolution;
uniform int maxIterations;

out vec4 FragColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution;

    uv -= 0.5;

    float x = uv.x * planeWidth;
    float y = uv.y * planeHeight;

    vec2 c = vec2(x + offset.x, y + offset.y);

    vec2 z = vec2(0.0);
    int iteration = 0;
    while (dot(z, z) <= 4.0 && iteration < maxIterations)
    {
        float zx = z.x * z.x - z.y * z.y + c.x;
        float zy = 2.0 * z.x * z.y + c.y;
        z = vec2(zx, zy);
        iteration++;
    }

    float t = float(iteration) / float(maxIterations);
    vec3 color = vec3(t, t*0.5, t*0.8);
    FragColor = vec4(color, 1.0);

    return;
}