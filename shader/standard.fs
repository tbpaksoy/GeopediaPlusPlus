#version 330 core

struct BasicLight {
    vec3 position;
    vec3 color;
    float intensity;
    float radius;
};

in vec3 Color;
in vec3 FragPos;

out vec4 fragColor;

#define MAX_LIGHTS 4
uniform BasicLight lights[MAX_LIGHTS];
uniform bool useLighting;

void main() 
{
    if (useLighting)
    {
    float light = 0.0;
        for (int i = 0; i < MAX_LIGHTS; i++) 
        {
            float dist = distance(FragPos, lights[i].position);
            if (dist < lights[i].radius) 
            {
                light += lights[i].intensity * (1.0 - (dist / lights[i].radius));
            }
        }
        fragColor = vec4(Color * light, 1.0);
    }
    else
    {
        fragColor = vec4(Color, 1.0);
    }
}