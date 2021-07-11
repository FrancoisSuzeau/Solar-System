// Version du GLSL

#version 150 core


// Entr�e

in vec2 coordTexture;
uniform vec3 atmoColor;

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

    // *********************************************** bind texture unit to fragment coordinate with blur/bloom effect without transparency ***************************************************
    //gl_FragColor = vec4(result1, 1.0);

    // *********************************************** bind texture with color unit to fragment coordinate WITH transparency ***************************************************
    
    float min_Transparency = 0.6;
    vec4 trans = max(vec4(0.0), ((texture(texture, coordTexture) * vec4(atmoColor, 1.0)) - min_Transparency));

    gl_FragColor = trans;
    
}