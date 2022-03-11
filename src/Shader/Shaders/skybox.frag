#version 400 core

in vec3 TexCoords;

layout (location = 0) out vec4 FragColor;
// layout (location = 1) out vec4 BrightColor;

uniform samplerCube skybox;
// uniform bool hdr;

void main()
{
    

    // *********************************************** ambiant light ***************************************************
    float ambiantStrength;
    

    vec3 objectColor = texture(skybox, TexCoords).rgb;

    // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    // vec3 lightColor;
    // if(hdr)
    // {
    //     lightColor = vec3(1.0);
    //     ambiantStrength = 0.4;
    // }
    // else
    // {
    //     lightColor = vec3(2.0);
    //     ambiantStrength = 0.09;
    // }
    
    // vec3 ambiant = ambiantStrength * lightColor;

    // vec3 result = ambiant * objectColor;
    vec3 result = objectColor;

    // float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    // if(brightness > 2.0)
    //     BrightColor = vec4(result, 1.0);
    // else
    //     BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    FragColor = vec4(result, 1.0);
}