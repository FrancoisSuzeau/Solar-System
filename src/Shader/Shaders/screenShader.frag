// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec2 TexCoords;
uniform sampler2D screenTexture;
// uniform sampler2D bloomTexture;
// uniform bool bloom;
// uniform bool hdr;
// uniform float exposure;
// uniform float gamma;

// ============ Out data ============
layout (location = 0) out vec4 FragColor;


float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
    vec3 fragment = texture(screenTexture, TexCoords).rgb;
    // vec3 bloom_text = texture(bloomTexture, TexCoords).rgb;

    // if(bloom)
    // {
    //     fragment += bloom_text;
    // }

    // vec3 toneMapped = vec3(1.0f) - exp(-fragment * exposure);

    // vec3 result = pow(toneMapped, vec3(1.0f / gamma));

    // FragColor = vec4(result, 1.0);

    // FragColor = vec4(fragment, 1.0);

    float depth = LinearizeDepth(gl_FragCoord.z) / far;

    FragColor = vec4(vec3(depth), 1.0);
}