#version 330 core

struct BasicLight {
    vec3 position;
    vec3 color;
    float intensity;
    float radius;
};

in vec3 Color;

out vec4 fragColor;

#define MAX_LIGHTS 4
uniform BasicLight lights[MAX_LIGHTS];

void main() 
{
    fragColor = vec4(Color, 1.0);
}