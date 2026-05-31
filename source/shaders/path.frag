#version 430 core

uniform float uTime;
uniform bool uIsShortestPath;
out vec4 FragColor;

void main()
{
    float randomContinuous = 0.8 + 0.5 * sin(uTime);
    vec3 color;

    // Reds for shortest path, blues for longest path. 
    if (uIsShortestPath) color = vec3(randomContinuous, 0.0, 0.0);
    else color = vec3(randomContinuous, 0.0, randomContinuous);

    FragColor = vec4(color, 1.0);
}