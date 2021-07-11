// Version du GLSL

#version 150 core


// Entr�e

in vec2 coordTexture;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 viewPos;
uniform vec3 atmoColor;
uniform vec3 camPosUpd;
uniform float phi;
uniform float theta;

uniform sampler2D texture;

// Fonction main

void main()
{
    // *********************************************** calculate png transparency ***************************************************
    vec4 alpha_color = texture2D(texture, coordTexture);
    if(alpha_color.r < 0.1)
    {
        discard;
    }
    
    vec3 lightColor = {1.0, 1.0, 1.0};
    vec3 lightPos = {0.1f, 0.0f, 0.0f};

    // *********************************************** light mitigation ***************************************************
    float lightConst = 1.0f;
    float lightLin = 0.22f;
    float lightQuad = 0.20f;
    float distance = length(lightPos - FragPos);
    float mitigation = 1.0 / (lightConst + lightLin + lightQuad);

    // *********************************************** diffuse light ***************************************************
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff;
    if(camPosUpd[1] < 0)
    {
        diff = max(dot(norm, -lightDir), 0.0);
    }
    else
    {
        diff = max(dot(norm, lightDir), 0.0);
    }

    vec3 diffuse = diff * lightColor;

    // *********************************************** specular light ***************************************************
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    vec3 specular = specularStrength * spec * lightColor;

    // *********************************************** ambiant light ***************************************************
    float ambiantStrength = 0.8;
    //float ambiantStrength;
    //if(camPosUpd[1] < 2 && camPosUpd[1] > -2)
    //{
        //ambiantStrength = 0.05;
    //}
    //else
    //{
        //ambiantStrength = 0.05;
    //}
    vec3 ambiant = ambiantStrength * lightColor;

    // *********************************************** calculate gaussian blur ***************************************************
    //float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
    //bool horizontal = true;

    //vec2 tex_offset = 1.0 / textureSize(texture, 0); // gets size of single texel
    //vec3 result1 = texture(texture, coordTexture).rgb * weight[0]; // current fragment's contribution
    //if(horizontal)
    //{
        //for(int i = 1; i < 5; ++i)
        //{
            //result1 += texture(texture, coordTexture + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            //result1 += texture(texture, coordTexture - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        //}
    //}
    //else
    //{
        //for(int i = 1; i < 5; ++i)
        //{
            //result1 += texture(texture, coordTexture + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            //result1 += texture(texture, coordTexture - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        //}
    //}

    //if(camPosUpd[1] < 3 && camPosUpd[1] > -3)
    //{
        //result1 = result1 * atmoColor;
    //}
    //else
    //{
        //result1 = ( diffuse + ambiant) * result1 * atmoColor;
    //}

    // *********************************************** add mitigation effect ***************************************************
    //ambiant *= mitigation;
    //diffuse *= mitigation;
    //specular *= mitigation;

    // *********************************************** bind texture unit to fragment coordinate with blur/bloom effect without transparency ***************************************************
    //gl_FragColor = vec4(result1, 1.0);

    // *********************************************** bind texture with color unit to fragment coordinate WITH transparency ***************************************************
    vec4 objectColor = texture(texture, coordTexture) * vec4(atmoColor, 1.0);
    vec3 result;

    float min_Transparency;
    if(camPosUpd[1] < 3 && camPosUpd[1] > -3)
    {
        result = vec3(objectColor.x, objectColor.y, objectColor.z);
        min_Transparency = 0.6;
    }
    else
    {
        result = (ambiant +  diffuse) * vec3(objectColor.x, objectColor.y, objectColor.z);
        min_Transparency = 0.715;
    }

    vec4 trans = max(vec4(0.0), ((vec4(result, 1.0)) - min_Transparency));

    gl_FragColor = trans;

    // *********************************************** only bind texture with color unit to fragment coordinate ***************************************************
    //vec4 objectColor = texture(texture, coordTexture);
    //vec3 result;
    //if(camPosUpd[1] < 3 && camPosUpd[1] > -3)
    //{
        //result = vec3(objectColor.x, objectColor.y, objectColor.z) * atmoColor;
    //}
    //else
    //{
        //result = ( diffuse + ambiant) * vec3(objectColor.x, objectColor.y, objectColor.z) * atmoColor;
    //}
    //gl_FragColor = vec4(result, 1.0);
    
}