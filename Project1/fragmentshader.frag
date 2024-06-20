#version 430 core

// Uniform inputs
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

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
uniform bool useTexture;
uniform vec3 objectColor;
uniform Material material;
uniform float textureScale;
void main()
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R locally
    vec3 R = reflect(-L, N);
    // White color
    vec3 whiteColor = vec3(1.0, 1.0, 1.0);
    // Compute the diffuse and specular components for each fragment
    // vec3 diffuse = max(dot(N, L), 0.0) * material.diffuse;
    vec3 diffuse;

    if (useTexture) {
        // Use texture color
        vec2 scaledUV = UV * textureScale;
        diffuse = abs(dot(N, L)) * texture(texsampler, scaledUV).rgb;

    } else {
        // Use object color
        diffuse = max(dot(N, L), 0.0) * objectColor;
    }
    // Use white color for ambient as well
    vec3 ambient = material.ambient * whiteColor;
    vec3 specular = pow(max(dot(R, V), 0.0), material.shininess) * material.specular;

    // Write final color to the framebuffer

    fragColor = vec4(ambient + diffuse + specular, 1.0);
}
