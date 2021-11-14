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

    //HACK : go to sphere class declaration to change number of parameters
    sphere_atmosphere = new Sphere(1, 70, 70);
    assert(sphere_atmosphere);

    /*Because atmosphere objects will use the same shader, color is initiate by the instance and will be used later in the shader*/
    if(name == "Sun")
    {
        m_color_atmo = glm::vec3(255.0/255.0, 255.0/255.0, 224.0/255.0);
        //! m_apparent_size = glm::vec3(3500 , 3500, 3500);
        sphere_atmosphere->setInclinaisonAngle(0.0f);
        sphere_atmosphere->setSpeedRot(0.0f);
        sphere_atmosphere->setSize(3500.0f);
    }
    else if(name == "Earth")
    {
        m_color_atmo = glm::vec3(147.0/255.0, 188.0/255.0, 251.0/255.0);
        //! m_apparent_size = glm::vec3(m_size, m_size, m_size);
        sphere_atmosphere->setInclinaisonAngle(23.26f);
        sphere_atmosphere->setSpeedRot(0.05);
        sphere_atmosphere->setSize(31.0f);
    }
    else if(name == "Venus")
    {
        m_color_atmo = glm::vec3(1.0, 1.0, 224.0/255.0);
        //! m_apparent_size = glm::vec3(m_size, m_size, m_size);
        sphere_atmosphere->setInclinaisonAngle(177.3);
        sphere_atmosphere->setSpeedRot(0.05f);
        sphere_atmosphere->setSize(29.47f);
    }
    else if (name == "Mars")
    {
        m_color_atmo = glm::vec3(178.0/255.0, 100.0/255.0, 100.0/255.0);
        //! m_apparent_size = glm::vec3(m_size, m_size, m_size);
        sphere_atmosphere->setInclinaisonAngle(25.19f);
        sphere_atmosphere->setSpeedRot(0.05f);
        sphere_atmosphere->setSize(16.99f);
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
/****************************************************************************** updatePosAtmo **************************************************************************/
/***********************************************************************************************************************************************************************/
void Atmosphere::updatePosAtmo(glm::vec3 pos_plan)
{
    if(sphere_atmosphere != nullptr)
    {
        sphere_atmosphere->setPosition(pos_plan);
        sphere_atmosphere->updatePosition();
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ display **************************************************************************/
/***********************************************************************************************************************************************************************/
void Atmosphere::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *atmo_shader, Shader *ring_shader)
{
    if(atmo_shader != nullptr)
    {
        
        glm::mat4 save = modelview;
        //! modelview = scale(modelview, m_apparent_size);

        //==============================================================================================================================
        glUseProgram(atmo_shader->getProgramID());

            atmo_shader->setVec3("atmoColor", m_color_atmo);
            
            if(sphere_atmosphere != nullptr)
            {
                sphere_atmosphere->display(projection, modelview, camPos, hdr, atmo_shader);
            }
            
        glUseProgram(0);
        
        modelview = save;
    }
}