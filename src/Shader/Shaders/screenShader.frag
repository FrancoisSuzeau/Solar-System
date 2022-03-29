// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec2 TexCoords;
uniform sampler2D depth_texture;
uniform sampler2D screen_texture;
uniform float near;
uniform float far;
uniform bool render_depth;    
// uniform sampler2D bloom_texture;
// uniform bool bloom;
// uniform bool hdr;
// uniform float exposure;
// uniform float gamma;

// ============ Out data ============
layout (location = 0) out vec4 FragColor;

// required when using a perspective projection matrix
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
    vec3 fragment = texture(screen_texture, TexCoords).rgb;
    // vec3 bloom_text = texture(bloom_texture, TexCoords).rgb;

    // if(bloom)
    // {
    //     fragment += bloom_text;
    // }

    // vec3 toneMapped = vec3(1.0f) - exp(-fragment * exposure);

    // vec3 result = pow(toneMapped, vec3(1.0f / gamma));

    // FragColor = vec4(result, 1.0);

    // FragColor = vec4(fragment, 1.0);

    if(render_depth)
    {
        float depthValue = texture(depth_texture, TexCoords).r;
        FragColor = vec4(vec3(LinearizeDepth(depthValue) / far), 1.0);
    }
    else
    {
        FragColor = vec4(fragment, 1.0);
    }

    // float depthValue = texture(depth_texture, TexCoords).r;
    // FragColor = vec4(vec3(LinearizeDepth(depthValue) / far), 1.0);
     
}