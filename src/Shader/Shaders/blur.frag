#version 330 core
layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform bool horizontal;

const int radius = 6;

// float spreadBlur = 1.0f;

uniform float weight[5] = float[] (0.2270270270, 0.1945945945, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
    // float x = 0.0f;
    // for(int i = 0; i < radius; i++)
    // {
    //     if(spreadBlur <= 2.0f)
    //     {
    //         x += 3.0f / radius;
    //     }
    //     else
    //     {
    //         x += 6.0f / radius;
    //     }

    //     weight[i] = exp(-0.5f * pow(x / spreadBlur, 2.0f)) / (spreadBlur * sqrt(2 * 3.14159265f));
    // }

    vec2 tex_offset = 1.0f / textureSize(screenTexture, 0);
    vec3 result = texture(screenTexture, TexCoords).rgb * weight[0];

    if(horizontal)
    {
        for(int i = 1; i < 5; i++)
        {
            result += texture(screenTexture, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(screenTexture, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; i++)
        {
            result += texture(screenTexture, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(screenTexture, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }

    FragColor = vec4(result, 1.0);
}