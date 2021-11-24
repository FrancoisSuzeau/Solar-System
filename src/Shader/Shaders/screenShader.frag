#version 330 core
layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D bloomTexture;
uniform bool bloom;
uniform bool hdr;
uniform float exposure;
uniform float gamma;


void main()
{
    // const float gamma = 2.2;
    vec3 fragment = texture(screenTexture, TexCoords).rgb;
    vec3 bloom_text = texture(bloomTexture, TexCoords).rgb;

    if(bloom)
    {
        fragment += bloom_text;
    }
    
    // float exposure = 0.8f;

    vec3 toneMapped = vec3(1.0f) - exp(-fragment * exposure);

    vec3 result = pow(toneMapped, vec3(1.0f / gamma));
    // FragColor.rgb = pow(toneMapped, vec3(1.0f / gamma));
    FragColor = vec4(result, 1.0);

    // const float gamma = 1.0;
    // vec3 hdrColor = texture(screenTexture, TexCoords).rgb;
    // // vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;

    // if(hdr)
    // {
    //     // if(bloom)
    //     // {
    //     //     hdrColor += bloomColor;
    //     // }
    //     vec3 result = vec3(1.0) - exp(-hdrColor * exposure);     
    //     result = pow(result, vec3(1.0 / gamma));
    //     FragColor = vec4(result, 1.0);
    // }
    // else
    // {
    //     vec3 textureScreen = texture(screenTexture, TexCoords).rgb;
    //     FragColor = vec4(textureScreen, 1.0);
    // }
}