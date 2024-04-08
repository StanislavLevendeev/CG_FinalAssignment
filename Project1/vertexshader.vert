#version 430 core

struct Light
{
    vec3 position;
};

// Uniform inputs
uniform mat4 mv;
uniform mat4 projection;
uniform Light light;

// Per-vertex inputs
in vec3 position;
in vec3 normal;

// Outputs
out VS_OUT
{
   vec3 N;
   vec3 L;
   vec3 V;
} vs_out;

in vec2 uv;
out vec2 UV;

void main()
{
    // Calculate view-space coordinate
    vec4 P = mv * vec4(position, 1.0);

    // Calculate normal in view-space
    vs_out.N = mat3(mv) * normal;

    // Calculate light vector
    vs_out.L = light.position - P.xyz;

    // Calculate view vector;
    vs_out.V = -P.xyz;

    // Calculate the clip-space position of each vertex
    gl_Position = projection * P;
    UV = uv;
}
