/*
AUTHOR : SUZEAU François

DATE : 05/07/2021

MODULE : Atmosphere

NAMEFILE : Atmosphere.cpp

PURPOSE : class Atmosphere
*/

#include "Atmosphere.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Atmosphere::Atmosphere(float size, std::string const name)
{

    name_planete_host = name;
    m_size = size;

    /*Because atmosphere objects will use the same shader, color is initiate by the instance and will be used later in the shader*/
    if(name == "Sun")
    {
        m_color_atmo = glm::vec3(255.0/255.0, 255.0/255.0, 224.0/255.0);
    }
    else if(name == "Earth")
    {
        m_color_atmo = glm::vec3(147.0/255.0, 188.0/255.0, 251.0/255.0);
    }
    else if(name == "Venus")
    {
        m_color_atmo = glm::vec3(1.0, 1.0, 224.0/255.0);
    }
    else if (name == "Mars")
    {
        m_color_atmo = glm::vec3(178.0/255.0, 100.0/255.0, 100.0/255.0);
    }


    //HACK : go to sphere class declaration to change number of parameters
    sphere_atmosphere = new Sphere(1, 70, 70);
    if(sphere_atmosphere == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    
}

Atmosphere::Atmosphere()
{
    
}

Atmosphere::~Atmosphere()
{
    if(sphere_atmosphere != nullptr)
    {
        delete sphere_atmosphere;
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ display **************************************************************************/
/***********************************************************************************************************************************************************************/
void Atmosphere::display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *atmo_shader, Shader *ring_shader)
{
    if(atmo_shader != nullptr)
    {
        
        glm::mat4 save = modelview;
        modelview = scale(modelview, glm::vec3(m_size, m_size, m_size));

        //==============================================================================================================================
        glUseProgram(atmo_shader->getProgramID());

            atmo_shader->setVec3("atmoColor", m_color_atmo);
            
            if(sphere_atmosphere != nullptr)
            {
                sphere_atmosphere->display(projection, modelview, light_src, camPos, hdr, atmo_shader);
            }
            
        glUseProgram(0);
        
        modelview = save;
    }
}


/***********************************************************************************************************************************************************************/
/************************************************************************************ display **************************************************************************/
/***********************************************************************************************************************************************************************/
void Atmosphere::displaySunAtmo(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, Shader *atmo_shader)
{
    if(atmo_shader != nullptr)
    {
        
        glm::mat4 save = modelview;
        modelview = scale(modelview, glm::vec3(3500 , 3500, 3500));

        //==============================================================================================================================
        glUseProgram(atmo_shader->getProgramID());

            atmo_shader->setVec3("atmoColor", m_color_atmo);

            if(sphere_atmosphere != nullptr)
            {
                sphere_atmosphere->displayForSun(projection, modelview, hdr, atmo_shader);
            }
             
        glUseProgram(0);

        modelview = save;
    }
}