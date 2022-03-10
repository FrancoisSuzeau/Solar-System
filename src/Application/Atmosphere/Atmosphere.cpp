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
    if(name == "Earth")
    {
        m_color_atmo = glm::vec3(147.0/255.0, 188.0/255.0, 251.0/255.0);
        sphere_atmosphere->setInclinaisonAngle(23.26f);
        sphere_atmosphere->setSpeedRot(0.05);
        sphere_atmosphere->setSize(31.0f);
    }
    else if(name == "Venus")
    {
        m_color_atmo = glm::vec3(1.0, 1.0, 224.0/255.0);
        sphere_atmosphere->setInclinaisonAngle(177.3);
        sphere_atmosphere->setSpeedRot(0.05f);
        sphere_atmosphere->setSize(29.47f);
    }
    else if (name == "Mars")
    {
        // m_color_atmo = glm::vec3(178.0/255.0, 100.0/255.0, 100.0/255.0);
        m_color_atmo = glm::vec3(255.0/255.0, 160.0/255.0, 122.0/255.0);
        sphere_atmosphere->setInclinaisonAngle(25.19f);
        sphere_atmosphere->setSpeedRot(0.05f);
        sphere_atmosphere->setSize(16.50f);
    }
    else if (name == "Jupiter")
    {
        m_color_atmo = glm::vec3(255.0/255.0, 228.0/255.0, 196.0/255.0);
        sphere_atmosphere->setInclinaisonAngle(3.13f);
        sphere_atmosphere->setSpeedRot(0.05f);
        sphere_atmosphere->setSize(367.27f);
    }
    else if (name == "Saturn")
    {
        m_color_atmo = glm::vec3(253.0/255.0, 241.0/255.0, 184.0/255.0);
        sphere_atmosphere->setInclinaisonAngle(26.73f);
        sphere_atmosphere->setSpeedRot(0.05f);
        sphere_atmosphere->setSize(287.476f);
    }
    else if (name == "Uranus")
    {
        m_color_atmo = glm::vec3(173.0/255.0, 216.0/255.0, 230.0/255.0);
        sphere_atmosphere->setInclinaisonAngle(97.77f);
        sphere_atmosphere->setSpeedRot(0.05f);
        sphere_atmosphere->setSize(122.21f);
    }
    else if (name == "Neptune")
    {
        m_color_atmo = glm::vec3(65.0/255.0, 105.0/255.0, 255.0/255.0);
        sphere_atmosphere->setInclinaisonAngle(26.32f);
        sphere_atmosphere->setSpeedRot(0.05f);
        sphere_atmosphere->setSize(119.49f);
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
void Atmosphere::display(RenderData &render_data)
{
    if(render_data.getShader("atmosphere") != nullptr)
    {
        
        // glm::mat4 save = view;
        render_data.initSaveMat();
        //! view = scale(view, m_apparent_size);

        //==============================================================================================================================
        glUseProgram(render_data.getShader("atmosphere")->getProgramID());

            render_data.getShader("atmosphere")->setVec3("atmoColor", m_color_atmo);
            
            if(sphere_atmosphere != nullptr)
            {
                glUseProgram(render_data.getShader("atmosphere")->getProgramID());

                    if(render_data.getHDR())
                    {
                        
                        if(name_planete_host == "Jupiter")
                        {
                            render_data.getShader("atmosphere")->setFloat("trans_strenght", 0.0001);
                            render_data.getShader("atmosphere")->setFloat("lightcolor", 0.35);
                        }
                        else
                        {
                            render_data.getShader("atmosphere")->setFloat("trans_strenght", 0.2);
                            render_data.getShader("atmosphere")->setFloat("lightcolor", 0.5);

                        }
                    }
                    else
                    {
                        
                        if(name_planete_host == "Jupiter")
                        {
                            render_data.getShader("atmosphere")->setFloat("trans_strenght", 0.2);
                            render_data.getShader("atmosphere")->setFloat("lightcolor", 0.09);

                        }
                        else
                        {
                            render_data.getShader("atmosphere")->setFloat("trans_strenght", 0.5);
                            render_data.getShader("atmosphere")->setFloat("lightcolor", 0.09);

                        }
                    }

                glUseProgram(0);
                sphere_atmosphere->display(render_data);
            }
            
        glUseProgram(0);
        
        render_data.saveViewMat();
    }
}