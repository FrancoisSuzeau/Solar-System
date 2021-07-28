#version 330 core

in vec3 TexCoords;

out vec4 FragColor;

uniform samplerCube skybox;

void main()
{
    vec3 lightColor = {1.0, 1.0, 1.0};

    // *********************************************** ambiant light ***************************************************
    float ambiantStrength = 0.09;
    vec3 ambiant = ambiantStrength * lightColor;

    vec3 objectColor = texture(skybox, TexCoords).rgb;

    // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    vec3 result = (ambiant) * objectColor;
    FragColor = vec4(result, 1.0);

    //gl_FragColor = texture(skybox, TexCoords);
}