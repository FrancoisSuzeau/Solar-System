#version 330 core

uniform vec3 viewPos;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 atmoColor;

uniform bool hdr;



layout (location = 0) out vec4 FragColor;
void main()
{
    vec3 objectColor = atmoColor;;

    vec3 lightColor;
    if(hdr)
    {
        lightColor = vec3(0.15, 0.15, 0.15);
    }
    else
    {
        lightColor = vec3(0.5, 0.5, 0.5);
    }

    vec3 lightPos = vec3(0.1f, 0.0f, 0.0f);

    // *********************************************** mitigation ***************************************************
    float lightConst = 1.0f;
    float lightLin = 0.35f;
    float lightQuad = 0.44f;
    float distance = length(lightPos - FragPos);
    float mitigation = 1.0 / (lightConst + lightLin + lightQuad);

    // *********************************************** diffuse light ***************************************************
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * objectColor;

    // *********************************************** specular light ***************************************************
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    vec3 specular = specularStrength * spec * lightColor;

    // *********************************************** ambiant light ***************************************************
    float ambiantStrength;
    

    if(hdr)
    {
        ambiantStrength = 0.001;
    }
    else
    {
        ambiantStrength = 0.0001;
    }

    float min_Transparency;
    //vec4 trans = max(vec4(0.0), ((vec4(objectColor, 1.0)) - min_Transparency));
    
    if(hdr)
    {
        min_Transparency = 0.01;
    }
    else
    {
        min_Transparency = 0.001;
    }

    vec3 ambiant = ambiantStrength * lightColor * objectColor;

    // *********************************************** adding mitigation effect ***************************************************
    //ambiant *= mitigation;
    //diffuse *= mitigation;
    //specular *= mitigation;

    // *********************************************** adding diffuse/ambiant light to fragment ***************************************************
    vec3 result = (ambiant + diffuse);

    float trans_strenght;
    if(hdr)
    {
        trans_strenght = 0.8;
    }
    else
    {
        trans_strenght = 0.5;
    }
    vec4 trans = max(vec4(0.0), ((vec4(result, trans_strenght)) - min_Transparency));

    // float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    // if(brightness > 1.0)
    //     BrightColor = vec4(result, 1.0);
    // else
    //     BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    FragColor = trans;

   

    

    //FragColor = trans;
}