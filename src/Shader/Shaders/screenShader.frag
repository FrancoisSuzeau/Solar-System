#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform bool hdr;
uniform float exposure;


void main()
{
    //vec3 textureScreen = texture(screenTexture, TexCoords).rgb;
    //FragColor = vec4(textureScreen, 1.0);

    const float gamma = 1.0;
    vec3 hdrColor = texture(screenTexture, TexCoords).rgb;
    if(hdr)
    {

        // exposure
        vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
        // also gamma correct while we're at it       
        result = pow(result, vec3(1.0 / gamma));
        FragColor = vec4(result, 1.0);
    }
    else
    {
        vec3 textureScreen = texture(screenTexture, TexCoords).rgb;
        FragColor = vec4(textureScreen, 1.0);
    }
}