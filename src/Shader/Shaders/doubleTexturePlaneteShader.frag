// ============ GLSL version ============
#version 400 core

// ============ In data ============
uniform float oppacity;
uniform vec3 viewPos;
uniform vec3 sunPos;
// uniform bool hdr;
// uniform bool has_normal;
// uniform bool has_disp;
// uniform float heightScale;
struct Material {
    sampler2D texture0;
    sampler2D shadowMap;
    sampler2D texture1;
    // sampler2D normalMap;
    // sampler2D dispMap;
    int shininess;
};
uniform Material material;
in VS_OUT {
    vec3 Normal;
    vec3 FragPos;
    vec4 texCoords;
    vec4 FragPosLightSpace;
//     vec3 TangentLightPos;
//     vec3 TangentViewPos;
//     vec3 TangentFragPos;
} fs_in;

// ============ Out data ============
// layout (location = 1) out vec4 BrightColor;
layout (location = 0) out vec4 FragColor;

// in VS_OUT {
//     vec3 TangentLightPos;
//     vec3 TangentViewPos;
//     vec3 TangentFragPos;
// } fs_in; 


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
//     float currentDepthMapValue = texture(material.dispMap, currentTexCoords).r;
      
//     while(currentLayerDepth < currentDepthMapValue)
//     {
//         // shift texture coordinates along direction of P
//         currentTexCoords -= deltaTexCoords;
//         // get depthmap value at current texture coordinates
//         currentDepthMapValue = texture(material.dispMap, currentTexCoords).r;  
//         // get depth of next layer
//         currentLayerDepth += layerDepth;  
//     }
    
//     // get texture coordinates before collision (reverse operations)
//     vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

//     // get depth after and before collision for linear interpolation
//     float afterDepth  = currentDepthMapValue - currentLayerDepth;
//     float beforeDepth = texture(material.dispMap, prevTexCoords).r - currentLayerDepth + layerDepth;
 
//     // interpolation of texture coordinates
//     float weight = afterDepth / (afterDepth - beforeDepth);
//     vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

//     return finalTexCoords; 

//     // float height =  texture(material.dispMap, texCoord).r;     
//     // return texCoord - viewDir.xy * (height * heightScale);  
// }

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(material.shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main(void) {

    // *********************************************** calculate spherical fragment coordonate ***************************************************
    vec2 longitudeLatitude = vec2((atan(fs_in.texCoords.y, fs_in.texCoords.x) / 3.1415926 + 1.0) * 0.5,
                                  (asin(fs_in.texCoords.z) / 3.1415926 + 0.5));
        // processing of the texture coordinates;
        // this is unnecessary if correct texture coordinates are specified by the application
    
        // look up the color of the texture image specified by the uniform "texture0"
        // at the position specified by "longitudeLatitude.x" and
        // "longitudeLatitude.y" and return it in "gl_FragColor"

    

    vec3 lightColor = vec3(1.0);
    vec3 lightPos = sunPos;

    // vec3 objectColor;
    // vec3 norm;
    // vec3 lightDir;
    // vec3 viewDir;
    vec2 texCoord = longitudeLatitude;

    // if(has_normal)
    // {
    //     norm = texture(material.normalMap, longitudeLatitude).rgb;
    //     norm = normalize(norm * 2.0 - 1.0);
    //     lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    //     viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    //     if(has_disp)
    //     {
    //         texCoord = parallaxMapping(texCoord, viewDir);
    //     }
    //     // if(texCoord.x > 1.0 || texCoord.y > 1.0 || texCoord.x < 0.0 || texCoord.y < 0.0)
    //     // {
    //     //     discard;
    //     // }
    // }
    // else
    // {
    //     norm = normalize(Normal);
    //     lightDir = normalize(lightPos - FragPos);
    //     viewDir = normalize(viewPos - FragPos);
    // }

    vec4 cloud_text = texture(material.texture1, texCoord);
    vec4 surface_text = texture(material.texture0, texCoord);

    vec3 objectColor = mix(cloud_text, surface_text, oppacity).rgb;
    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    // // *********************************************** mitigation ***************************************************
    // //mitigation
    // float lightConst = 1.0f;
    // float lightLin = 0.35f;
    // float lightQuad = 0.44f;
    // float distance = length(lightPos - FragPos);
    // float mitigation = 1.0 / (lightConst + lightLin + lightQuad);

    // // *********************************************** diffuse light ***************************************************
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // // *********************************************** specular light ***************************************************
    float specularStrength = 0.5;

    vec3 reflectDir = reflect(-lightDir, norm);
     vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = 0.0;
    spec = pow(max(dot(norm, halfwayDir), 0.0),  material.shininess);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = specularStrength * spec * lightColor;
    vec3 specular = spec * lightColor;

    // // *********************************************** ambiant light ***************************************************
    float ambiantStrength = 0.01;
    

    // if(hdr)
    // {
    //     ambiantStrength = 0.0001;
    // }
    // else
    // {
    //     ambiantStrength = 0.01;
    // }

    vec3 ambiant = ambiantStrength * lightColor;

    // // *********************************************** adding mitigation effect ***************************************************
    // ambiant *= mitigation;
    // diffuse *= mitigation;
    // specular *= mitigation;

    // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    
    // vec3 result = (ambiant + diffuse + specular) * objectColor;
    // FragColor = vec4(result, 1.0);
    // float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    // if(brightness > 1.0)
    //     BrightColor = vec4(result, 1.0);
    // else
    //     BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
    // vec3 result = (ambiant + diffuse + specular) * objectColor;
    vec3 result = (ambiant + (1.0 - shadow) * (diffuse + specular)) * objectColor;
    FragColor = vec4(result, 1.0);
}