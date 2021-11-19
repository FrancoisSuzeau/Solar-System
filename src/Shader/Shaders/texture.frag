// Version du GLSL

#version 330 core


// Entr�e

in vec2 coordTexture;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 viewPos;

uniform bool hdr;


// Uniform

uniform sampler2D texture0;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


// Fonction main

void main()
{
    // *********************************************** calculate png transparency ***************************************************
    vec4 alpha_color = texture2D(texture0, coordTexture);
    if(alpha_color.r < 0.1)
    {
        discard;
    }

    vec3 lightColor;
    if(hdr)
    {
        lightColor = vec3(0.3, 0.3, 0.3);
    }
    else
    {
        lightColor = vec3(1.0, 1.0, 1.0);
    }
    vec3 lightPos = vec3(1.0f, 0.0f, 0.0f);
    
    // *********************************************** light mitigation ***************************************************
    float lightConst = 1.0f;
    float lightLin = 0.22f;
    float lightQuad = 0.20f;
    float distance = length(lightPos - FragPos);
    float mitigation = 1.0 / (lightConst + lightLin + lightQuad);

    // *********************************************** diffuse light ***************************************************
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // *********************************************** specular light ***************************************************
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
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

    // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    
    ambiant *= mitigation;
    diffuse *= mitigation;
    specular *= mitigation;

    vec3 objectColor = texture(texture0, coordTexture).rgb;
    vec3 result = (ambiant + diffuse + specular) * objectColor;

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    FragColor = vec4(result, 1.0);
    
}
