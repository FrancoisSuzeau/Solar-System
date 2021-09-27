#version 330 core

uniform vec3 atmoColor;

uniform bool hdr;



layout (location = 0) out vec4 FragColor;
void main()
{
    vec3 objectColor = atmoColor;

    float min_Transparency;
    
    if(hdr)
    {
        min_Transparency = 0.5;
    }
    else
    {
        min_Transparency = 0.001;
    }

    float trans_strenght;
    if(hdr)
    {
        trans_strenght = 1.0;
    }
    else
    {
        trans_strenght = 0.5;
    }
    vec4 trans = max(vec4(0.0), ((vec4(objectColor, trans_strenght)) - min_Transparency));
    
    FragColor = trans;

}