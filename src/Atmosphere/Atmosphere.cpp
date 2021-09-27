/*
AUTHOR : SUZEAU François

DATE : 05/07/2021

MODULE : Atmosphere

NAMEFILE : Atmosphere.cpp

PURPOSE : class Atmosphere
*/

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Atmosphere.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Atmosphere::Atmosphere(float size, std::string const name)
{

    name_planete_host = name;
    m_size = size;
    
    if(name == "Earth")
    {
        m_color_atmo = vec3(147.0/255.0, 188.0/255.0, 251.0/255.0); //autre bleu clair
    }
    else if(name == "Venus")
    {
        m_color_atmo = vec3(1.0, 1.0, 224.0/255.0);
    }
    else if (name == "Mars")
    {
        m_color_atmo = vec3(1.0, 178.0/255.0, 86.0/255.0);
    }
    else if (name == "Jupiter")
    {
        // m_color_atmo = vec3(215.0/255.0, 184.0/255.0, 148.0/255.0);
        m_color_atmo = vec3(233.0/255.0, 219.0/255.0, 171.0/255.0);
    }
    else if (name == "Saturn")
    {
        m_color_atmo = vec3(233.0/255.0, 219.0/255.0, 171.0/255.0);
    }
    else if (name == "Uranus")
    {
        m_color_atmo = vec3(142.0/255.0, 230.0/255.0, 207.0/255.0);
    }
    else if (name == "Neptune")
    {
        m_color_atmo = vec3(101.0/255.0, 197.0/255.0, 255.0/255.0);
    }

    sphere_atmosphere = new Sphere(1, 70, 70);
    if(sphere_atmosphere == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    
}

Atmosphere::Atmosphere()
{
    if(sphere_atmosphere != nullptr)
    {
        delete sphere_atmosphere;
    }
}

Atmosphere::~Atmosphere()
{
    
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ display **************************************************************************/
/***********************************************************************************************************************************************************************/
void Atmosphere::display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *atmo_shader, Shader *ring_shader)
{
    if(atmo_shader != nullptr)
    {
        
        glm::mat4 save = modelview;
        modelview = scale(modelview, vec3(m_size, m_size, m_size));
        //==============================================================================================================================
        //Activate the shader
        glUseProgram(atmo_shader->getProgramID());

           
            atmo_shader->setMat4("modelview", modelview);
            atmo_shader->setMat4("projection", projection);
            atmo_shader->setMat4("light_src", light_src);

            atmo_shader->setVec3("viewPos", camPos);
            atmo_shader->setVec3("atmoColor", m_color_atmo);
            atmo_shader->setInt("hdr", hdr);

            
            if(sphere_atmosphere != nullptr)
            {
                sphere_atmosphere->display(projection, modelview, light_src, camPos, hdr, atmo_shader);
            }
            
            
        glUseProgram(0);
           

        modelview = save;
    }
    
    
}