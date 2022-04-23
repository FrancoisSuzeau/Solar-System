// ============ GLSL version ============
#version 400 core

// ============ In data ============
in VS_OUT {
    vec3 Normal;
    vec3 FragPos;
    vec2 coordTexture;
} fs_in;

uniform sampler2D diffuseTexture;
uniform samplerCube depthMap;
uniform vec3 viewPos;
uniform vec3 sunPos;
uniform float far_plane;
uniform bool shadows;
uniform int shininess;

// ============ Out data ============
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float ShadowCalculation(vec3 fragPos)
{
    vec3 fragToLight = fragPos - sunPos;
    float currentDepth = length(fragToLight);
    float shadow = 0.0;
    float bias = 0.85;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
    return shadow;
}

void main()
{
    // *********************************************** calculate png transparency ***************************************************
    vec4 alpha_color = texture2D(diffuseTexture, fs_in.coordTexture);
    if(alpha_color.a < 0.1)
    {
        discard;
    }

    vec3 lightColor = vec3(1.0);
    // if(hdr)
    // {
    //     lightColor = vec3(0.4);
    // }
    // else
    // {
    //     lightColor = vec3(0.2);
    // }
    // vec3 lightPos = vec3(1.0f, 0.0f, 0.0f);
    vec3 lightPos = sunPos;

    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir;
    vec3 viewDir;
    
    
    // // *********************************************** light mitigation ***************************************************
    // float lightConst = 1.0f;
    // float lightLin = 0.22f;
    // float lightQuad = 0.20f;
    // float distance = length(lightPos - FragPos);
    // float mitigation = 1.0 / (lightConst + lightLin + lightQuad);

    // // *********************************************** diffuse light ***************************************************
    
    lightDir = normalize(lightPos - fs_in.FragPos);

    // // *********************************************** specular light ***************************************************
    vec3 reflectDir = reflect(-lightDir, norm);
    viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = 0.0;
    spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec3 specular = spec * lightColor;

    // // *********************************************** ambiant light ***************************************************
    float ambiantStrength = 0.6;
    vec3 ambiant = ambiantStrength * lightColor;

    // // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    
    // ambiant *= mitigation;
    // specular *= mitigation;

    vec2 texCoord = fs_in.coordTexture;

    vec3 objectColor = texture(diffuseTexture, texCoord).rgb;
    float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;
    vec3 result = ambiant - shadow;
    result *= objectColor;

    FragColor = vec4(result, 1.0);

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0); 
}
