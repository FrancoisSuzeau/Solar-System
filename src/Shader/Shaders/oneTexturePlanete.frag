#version 330 core
in vec4 texCoords;
uniform vec3 viewPos;
uniform vec3 sunPos;
in vec3 Normal;
in vec3 FragPos;

uniform bool hdr;
uniform bool has_normal;

struct Material {
    sampler2D texture0;
    sampler2D normalMap;
    int shininess;
};

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in VS_OUT {
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform Material material;

void main(void) {

    // *********************************************** calculate spherical fragment coordonate ***************************************************
    vec2 longitudeLatitude = vec2((atan(texCoords.y, texCoords.x) / 3.1415926 + 1.0) * 0.5,
                                  (asin(texCoords.z) / 3.1415926 + 0.5));
        // processing of the texture coordinates;
        // this is unnecessary if correct texture coordinates are specified by the application

    // look up the color of the texture image specified by the uniform "texture0"
        // at the position specified by "longitudeLatitude.x" and
        // "longitudeLatitude.y" and return it in "gl_FragColor"


    vec3 lightColor;
    if(hdr)
    {
        lightColor = vec3(0.4);
    }
    else
    {
        lightColor = vec3(0.2);
    }

    // vec3 lightPos = vec3(0.1f, 0.0f, 0.0f);
    vec3 lightPos = sunPos;

    vec3 objectColor;
    vec3 norm;
    vec3 lightDir;
    vec3 viewDir;
    vec2 texCoord = longitudeLatitude;

    if(has_normal)
    {
        norm = texture(material.normalMap, longitudeLatitude).rgb;
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

    objectColor = texture(material.texture0, texCoord).rgb;
    
    // *********************************************** mitigation ***************************************************
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
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularStrength * spec * lightColor;

    // *********************************************** ambiant light ***************************************************
    float ambiantStrength;
    

    if(hdr)
    {
        ambiantStrength = 0.0001;
    }
    else
    {
        ambiantStrength = 0.001;
    }

    vec3 ambiant = ambiantStrength * lightColor;

    // *********************************************** adding mitigation effect ***************************************************
    ambiant *= mitigation;
    diffuse *= mitigation;
    specular *= mitigation;

    // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    vec3 result = (ambiant + diffuse + specular) * objectColor;

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    FragColor = vec4(result, 1.0);
        
}