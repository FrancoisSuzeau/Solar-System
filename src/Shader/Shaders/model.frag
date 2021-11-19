#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
uniform bool hdr;
uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;

void main()
{
    vec3 lightColor;
    if(hdr)
    {
        lightColor = vec3(0.3, 0.3, 0.3);
    }
    else
    {
        lightColor = vec3(1.0, 1.0, 1.0);
    }

    vec3 lightPos = vec3(0.1f, 0.0f, 0.0f);

    vec3 objectColor = texture(texture_diffuse1, TexCoords).rgb;

    // *********************************************** diffuse light ***************************************************
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // *********************************************** specular light ***************************************************
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = specularStrength * spec * lightColor;

    // *********************************************** ambiant light ***************************************************
    float ambiantStrength;
    if(hdr)
    {
        ambiantStrength = 0.008;
    }
    else
    {
        ambiantStrength = 0.1;
    }

    vec3 ambiant = ambiantStrength * lightColor;
    vec3 result = (ambiant + diffuse + specular) * objectColor;
    
    FragColor = vec4(result, 1.0);
}