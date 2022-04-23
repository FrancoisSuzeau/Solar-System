// ============ GLSL version ============
#version 400 core

// ============ In data ============
in vec2 TexCoords;
uniform sampler2D screen_texture;  
uniform sampler2D bloom_texture;
uniform bool bloom;

// ============ Out data ============
layout (location = 0) out vec4 FragColor;

void main()
{
    vec3 fragment = texture(screen_texture, TexCoords).rgb;
    vec3 bloom_text = texture(bloom_texture, TexCoords).rgb;

    // fragment += bloom_text;

    if(bloom)
    {
        fragment += bloom_text;
    }

    FragColor = vec4(fragment, 1.0);
     
}