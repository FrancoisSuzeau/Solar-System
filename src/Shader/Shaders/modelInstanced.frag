#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
uniform bool hdr;
uniform bool has_normal;

uniform vec3 viewPos;
uniform vec3 sunPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D normalMap;

in VS_OUT {
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

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

    // vec3 lightPos = vec3(0.1f, 0.0f, 0.0f);
    vec3 lightPos = sunPos;

    vec3 norm;
    vec3 lightDir;
    vec3 viewDir;
    vec2 texCoord = TexCoords;

    if(has_normal)
    {
        norm = texture(normalMap, TexCoords).rgb;
        norm = normalize(norm * 2.0 - 1.0);
        lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
        viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
        
    }
    else
    {
        norm = normalize(Normal);
        lightDir = normalize(lightPos - FragPos);
        viewDir = normalize(viewPos - FragPos);
    }

    vec3 objectColor = texture(texture_diffuse1, texCoord).rgb;

    // *********************************************** mitigation ***************************************************
    //mitigation
    float lightConst = 1.0f;
    float lightLin = 0.35f;
    float lightQuad = 0.44f;
    float distance = length(lightPos - FragPos);
    float mitigation = 1.0 / (lightConst + lightLin + lightQuad);

    // *********************************************** diffuse light ***************************************************
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // *********************************************** specular light ***************************************************
    float specularStrength = 0.5;
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

    // *********************************************** adding mitigation effect ***************************************************
    ambiant *= mitigation;
    diffuse *= mitigation;
    specular *= mitigation;
    
    vec3 result = (ambiant + diffuse + specular) * objectColor;
    
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    FragColor = vec4(result, 1.0);
}