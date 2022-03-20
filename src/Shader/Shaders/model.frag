// ============ GLSL version ============
#version 400 core

// ============ In data ============
uniform sampler2D texture_diffuse1;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
// uniform bool hdr;
uniform vec3 viewPos;
uniform vec3 sunPos;
uniform float near; 
uniform float far;
uniform bool render_depth;

// ============ Out data ============
layout (location = 0) out vec4 FragColor;
// layout (location = 1) out vec4 BrightColor;

  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
    vec3 lightColor = vec3(1.0);
    // if(hdr)
    // {
    //     lightColor = vec3(0.5);
    // }
    // else
    // {
    //     lightColor = vec3(0.2);
    // }

    vec3 lightPos = sunPos;

    vec3 objectColor = texture(texture_diffuse1, TexCoords).rgb;

    // *********************************************** mitigation ***************************************************
    //mitigation
    // float lightConst = 1.0f;
    // float lightLin = 0.35f;
    // float lightQuad = 0.44f;
    // float distance = length(lightPos - FragPos);
    // float mitigation = 1.0 / (lightConst + lightLin + lightQuad);

    // // *********************************************** diffuse light ***************************************************
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
    float ambiantStrength = 0.1;
    // if(hdr)
    // {
    //     ambiantStrength = 0.002;
    // }
    // else
    // {
    //     ambiantStrength = 0.01;
    // }

    vec3 ambiant = ambiantStrength * lightColor;

    // *********************************************** adding mitigation effect ***************************************************
    // ambiant *= mitigation;
    // diffuse *= mitigation;
    // specular *= mitigation;
    

    // float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    // if(brightness > 1.0)
    //     BrightColor = vec4(result, 1.0);
    // else
    //     BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    if(render_depth)
    {
        float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
        FragColor = vec4(vec3(depth), 1.0);
    }
    else
    {
        vec3 result = (ambiant + diffuse + specular) * objectColor;
        FragColor = vec4(result, 1.0);
    }
}