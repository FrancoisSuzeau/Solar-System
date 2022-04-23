// ============ GLSL version ============
#version 400 core

// ============ In data ============
uniform float oppacity;
uniform vec3 viewPos;
uniform vec3 sunPos;
uniform float far_plane;
uniform bool shadows;
// uniform bool hdr;
// uniform bool has_normal;
struct Material {
    sampler2D surface;
    samplerCube depthMap;
    sampler2D cloud;
    sampler2D normalMap;
    int shininess;
    float light_strength;
};
uniform Material material;
in VS_OUT {
    vec3 Normal;
    vec3 FragPos;
    vec4 texCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

// ============ Out data ============
layout (location = 1) out vec4 BrightColor;
layout (location = 0) out vec4 FragColor;

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
        float closestDepth = texture(material.depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);

    return shadow;
}

void main(void) {

    // *********************************************** calculate spherical fragment coordonate ***************************************************
    vec2 longitudeLatitude = vec2((atan(fs_in.texCoords.y, fs_in.texCoords.x) / 3.1415926 + 1.0) * 0.5,
                                  (asin(fs_in.texCoords.z) / 3.1415926 + 0.5));
        // processing of the texture coordinates;
        // this is unnecessary if correct texture coordinates are specified by the application
    
        // look up the color of the texture image specified by the uniform "surface"
        // at the position specified by "longitudeLatitude.x" and
        // "longitudeLatitude.y" and return it in "gl_FragColor"

    vec3 lightColor = vec3(material.light_strength);
    vec3 lightPos = sunPos;

    vec3 objectColor;
    vec3 norm;
    vec3 lightDir;
    vec3 viewDir;
    vec2 texCoord = longitudeLatitude;

    // if(has_normal)
    // {
    //     norm = texture(material.normalMap, longitudeLatitude).rgb;
    //     norm = normalize(norm * 2.0 - 1.0);
    //     lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    //     viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    // }
    // else
    // {
    //     norm = normalize(Normal);
    //     lightDir = normalize(lightPos - FragPos);
    //     viewDir = normalize(viewPos - FragPos);
    // }

    norm = texture(material.normalMap, longitudeLatitude).rgb;
    norm = normalize(norm * 2.0 - 1.0);
    lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);

    vec4 cloud_text = texture(material.cloud, texCoord);
    vec4 surface_text = texture(material.surface, texCoord);

    objectColor = mix(cloud_text, surface_text, oppacity).rgb;

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

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = 0.0;
    spec = pow(max(dot(norm, halfwayDir), 0.0),  material.shininess);
    vec3 specular = spec * lightColor * specularStrength;

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
    float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;
    vec3 result = (ambiant + (1.0 - shadow) * (diffuse + specular)) * objectColor;
    FragColor = vec4(result, 1.0);

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
}