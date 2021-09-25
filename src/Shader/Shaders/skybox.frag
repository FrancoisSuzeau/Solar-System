#version 330 core

in vec3 TexCoords;

out vec4 FragColor;

uniform samplerCube skybox;
uniform bool hdr;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    // *********************************************** ambiant light ***************************************************
    float ambiantStrength = 0.3;
    vec3 ambiant = ambiantStrength * lightColor;

    vec3 objectColor = texture(skybox, TexCoords).rgb;
    // vec3 objectColor = vec3(1.0);

    // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    if(hdr)
    {
        vec3 result = (ambiant) * objectColor;
        FragColor = vec4(result, 1.0);
    }
    else
    {
        FragColor = vec4(objectColor, 1.0);
    }
    

    
}