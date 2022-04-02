// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec2 TexCoords;
uniform sampler2D screen_texture;  
// uniform sampler2D bloom_texture;
// uniform bool bloom;
// uniform bool hdr;
// uniform float exposure;
// uniform float gamma;

// ============ Out data ============
layout (location = 0) out vec4 FragColor;

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

    FragColor = vec4(fragment, 1.0);
     
}