#version 330 core

in vec3 TexCoords;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform samplerCube skybox;
uniform bool hdr;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    // *********************************************** ambiant light ***************************************************
    float ambiantStrength;
    

    vec3 objectColor = texture(skybox, TexCoords).rgb;

    // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    if(hdr)
    {
        ambiantStrength = 0.25;
    }
    else
    {
        ambiantStrength = 1.0;
    }
    
    vec3 ambiant = ambiantStrength * lightColor;

    vec3 result = ambiant * objectColor;

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    
    FragColor = vec4(result, 1.0);
}