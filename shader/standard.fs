struct BasicLight {
    vec3 position;
    vec3 color;
    float intensity;
    float radius;
};

out vec4 fragColor;

const int MAX_LIGHTS = 4;
uniform BasicLight lights[MAX_LIGHTS];

void main() {
    
}