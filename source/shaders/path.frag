#version 430 core

uniform float uTime;
uniform bool uIsShortestPath;
out vec4 FragColor;

void main()
{
    float randomContinuous = 0.8 + 0.5 * sin(uTime * 2.0);
    vec3 color;

    // Reds for shortest path, magentas for longest path. 
    if (!uIsShortestPath) color = vec3(randomContinuous, 0.0, randomContinuous);
    else color = vec3(randomContinuous, 0.0, 0.0);

    FragColor = vec4(color, 1.0);
}