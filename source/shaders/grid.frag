#version 430 core

uniform float uTime;
uniform float uGridSize;
uniform vec2 uResolution;

out vec4 FragColor;

float random (vec2 uv) // Found this on some Stack Overflow thread
{
    float minVal = 0.33;
    float maxVal = 1.0;
    float r = fract(sin(dot(uv.xy, vec2(12.9898,78.233))) * 43758.5453123);
    return minVal + r * (maxVal - minVal);
}

vec3 random_color () 
{
    vec2 uv = (gl_FragCoord.xy * uGridSize) / 16.0;
    float R = random(floor(uv * 1.0));
    float G = random(floor(uv * 1.1));
    float B = random(floor(uv * 0.9));
    return vec3(R, G, B);
}

float DiscreteTimeUpdate(float updatesPerSecond) 
{
    return floor(uTime * updatesPerSecond);
}

void main()
{
    //vec3 color = random_color();
    //vec3 color = vec3(0.0, 0.68, 0.0); // hacker green

    float cellSize = (min(uResolution.x, uResolution.y) / uGridSize) * 32.0;
    vec2 uv = floor(gl_FragCoord.xy / cellSize);

    float randomDiscrete = random(uv + DiscreteTimeUpdate(4.0));
    float randomContinuous = 0.75 + 0.5 * sin(uTime + random(floor(uv)) * 10.0);

    //vec3 color = vec3(0.0, randomDiscrete, 0.0); // Random greens only (Discrete)
    vec3 color = vec3(0.0, randomContinuous, 0.0); // Random greens only (Continuous)
    
    float randomContinuousR = 0.7 + 0.5 * sin(uTime * 5.0 + random(floor(uv)) * 100.0);
    float randomContinuousG = 0.7 + 0.5 * sin(uTime * 2.5 + random(floor(uv)) * 10.0);
    float randomContinuousB = 0.7 + 0.5 * sin(uTime * 3.75 + random(floor(uv)) * 50.0);

    float randomDiscreteR = random(uv + DiscreteTimeUpdate(3.0));
    float randomDiscreteG = random(uv + DiscreteTimeUpdate(4.0));
    float randomDiscreteB = random(uv + DiscreteTimeUpdate(6.0));
    
    //vec3 color = vec3(randomDiscreteR, randomContinuousG, randomDiscreteB); // Discrete RGB
    //vec3 color = vec3(randomContinuousR, randomContinuousG, randomContinuousB); // Continuous RGB

    FragColor = vec4(color, 1.0);
}