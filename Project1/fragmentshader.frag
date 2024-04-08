#version 430 core

// Uniform inputs
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;
// Inputs from vertexshader
in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} fs_in;

// Output color
out vec4 fragColor;
in vec2 UV;
uniform sampler2D texsampler;
void main()
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R locally
    vec3 R = reflect(-L, N);

    // Compute the diffuse and specular components for each fragment
    // vec3 diffuse = max(dot(N, L), 0.0) * material.diffuse;
    vec3 diffuse = max(dot(N, L), 0.0) * texture2D(texsampler, UV).rgb;

    vec3 specular = pow(max(dot(R, V), 0.0), material.shininess) * material.specular;

    // Write final color to the framebuffer

    fragColor = vec4(material.ambient + diffuse + specular, 1.0);
}
