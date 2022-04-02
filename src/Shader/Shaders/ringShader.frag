// ============ GLSL version ============
#version 400 core

// ============ In data ============
in VS_OUT {
    vec3 Normal;
    vec3 FragPos;
    vec2 coordTexture;
    vec4 FragPosLightSpace;
//     vec3 TangentLightPos;
//     vec3 TangentViewPos;
//     vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;
// in vec3 Normal;
// in vec3 FragPos;
uniform vec3 viewPos;
uniform vec3 sunPos;
// uniform bool hdr;
// uniform bool has_normal;
// uniform bool has_disp;
// uniform sampler2D normalMap;
// uniform sampler2D depthMap;
// uniform float heightScale;

// ============ Out data ============
layout (location = 0) out vec4 FragColor;
// layout (location = 1) out vec4 BrightColor;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(sunPos - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005);
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow+= currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if(projCoords.z > 1.0)
    {
        shadow = 0.0;
    }
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
    // float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    // return shadow;
}

// vec2 parallaxMapping(vec2 texCoord, vec3 viewDir)
// {
//     // number of depth layers
//     const float minLayers = 8;
//     const float maxLayers = 32;
//     float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
//     // calculate the size of each layer
//     float layerDepth = 1.0 / numLayers;
//     // depth of current layer
//     float currentLayerDepth = 0.0;
//     // the amount to shift the texture coordinates per layer (from vector P)
//     // vec2 P = vec2(0.0);
//     // if(heightScale != 0.0)
//     // {
//     //     P = viewDir.xy / viewDir.z * heightScale; 
//     // }
//     vec2 P = viewDir.xy / viewDir.z * heightScale;
//     vec2 deltaTexCoords = P / numLayers;
  
//     // get initial values
//     vec2  currentTexCoords     = texCoord;
//     float currentDepthMapValue = texture(depthMap, currentTexCoords).r;
      
//     while(currentLayerDepth < currentDepthMapValue)
//     {
//         // shift texture coordinates along direction of P
//         currentTexCoords -= deltaTexCoords;
//         // get depthmap value at current texture coordinates
//         currentDepthMapValue = texture(depthMap, currentTexCoords).r;  
//         // get depth of next layer
//         currentLayerDepth += layerDepth;  
//     }
    
//     // get texture coordinates before collision (reverse operations)
//     vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

//     // get depth after and before collision for linear interpolation
//     float afterDepth  = currentDepthMapValue - currentLayerDepth;
//     float beforeDepth = texture(depthMap, prevTexCoords).r - currentLayerDepth + layerDepth;
 
//     // interpolation of texture coordinates
//     float weight = afterDepth / (afterDepth - beforeDepth);
//     vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

//     return finalTexCoords;   
// }

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
    
    // if(has_normal)
    // {
    //     norm = texture(normalMap, coordTexture).rgb;
    //     norm = normalize(norm * 2.0 - 1.0);
    //     lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    //     viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    //     if(has_disp)
    //     {
    //         texCoord = parallaxMapping(texCoord, viewDir);
    //     }
    // }
    // else
    // {
    //     norm = normalize(Normal);
    //     lightDir = normalize(lightPos - FragPos);
    //     viewDir = normalize(viewPos - FragPos);
    // }
    
    
    // // *********************************************** light mitigation ***************************************************
    // float lightConst = 1.0f;
    // float lightLin = 0.22f;
    // float lightQuad = 0.20f;
    // float distance = length(lightPos - FragPos);
    // float mitigation = 1.0 / (lightConst + lightLin + lightQuad);

    // // *********************************************** diffuse light ***************************************************
    
    lightDir = normalize(lightPos - fs_in.FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // // *********************************************** specular light ***************************************************
    // float specularStrength = 0.5;
    vec3 reflectDir = reflect(-lightDir, norm);
    viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = 0.0;
    spec = pow(max(dot(norm, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // vec3 specular = specularStrength * spec * lightColor;

    // // *********************************************** ambiant light ***************************************************
    float ambiantStrength = 0.8;
    

    // if(hdr)
    // {
    //     ambiantStrength = 0.008;
    // }
    // else
    // {
    //     ambiantStrength = 0.01;
    // }

    vec3 ambiant = ambiantStrength * lightColor;

    // // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    
    // ambiant *= mitigation;
    // diffuse *= mitigation;
    // specular *= mitigation;

    vec2 texCoord = fs_in.coordTexture;

    vec3 objectColor = texture(diffuseTexture, texCoord).rgb;
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
    vec3 result = ambiant  - shadow;
    result *= objectColor;
    FragColor = vec4(result, 1.0);
    // vec3 result = (ambiant + diffuse + specular) * objectColor;

    // float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    // if(brightness > 1.0)
    //     BrightColor = vec4(result, 1.0);
    // else
    //     BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    // FragColor = vec4(result, 1.0);
    
}