/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : PlanetarySystem.cpp

PURPOSE : class PlanetarySystem
*/



#include "PlanetarySystem.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
PlanetarySystem::PlanetarySystem(std::string name_system, int companion_count) : m_name_renderer(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf")
{
    m_system_name = name_system;
    m_companion_count = companion_count;

    m_name_renderer.loadTTF(m_system_name);

    //No need to create a planete info pointer because we use Only one

}

PlanetarySystem::PlanetarySystem()
{
    
}

PlanetarySystem::~PlanetarySystem()
{
    for (int i(0); i < m_companion_count; i++)
    {
        if(m_moons_creator[i] != nullptr)
        {
            delete m_moons_creator[i];
        }
        
    }

    if(m_host_creator != nullptr)
    {
        delete m_host_creator;
    }
    

    if((m_system_name == "Earth System") || (m_system_name == "Jovian System") || (m_system_name == "Saturnian System"))
    {
        if(m_atmosphere != nullptr)
        {
            delete m_atmosphere;
        }
        
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** loadSystem ***************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::loadSystem(int count)
{
    /************************************************* loading companion ********************************************************/
    if(m_system_name == "Earth System")
    {
        m_companion_name.push_back("Moon");
        
        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[0] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[0]->MakingPlanete("../assets/textures/CelestialBody/MoonMap.jpg", "Moon", 2.0, 5.145, glm::vec3(-110, 20, 0));

        m_host_creator = new AtmoPlaneteCreator();
        if(m_host_creator == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_host_creator->MakingPlanete("../assets/textures/CelestialBody/EarthDayMap.jpg", "Earth", 5.0, 23.26, glm::vec3(-110, 0, 0));

        m_atmosphere = new Atmosphere(10.8, "Earth", "../assets/textures/atmosphere.png");
        if(m_atmosphere == nullptr)
        {
            exit(EXIT_FAILURE);
        }
    }
    else if(m_system_name == "Jovian System")
    {
        m_companion_name.push_back("Europa");
        m_companion_name.push_back("Ganymede");
        m_companion_name.push_back("Io");
        m_companion_name.push_back("Callisto");

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[0] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[0]->MakingPlanete("../assets/textures/CelestialBody/EuropaMap.jpg", "Europa", 2.0, 0.469, glm::vec3(175, 0, 0));

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[1] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[1]->MakingPlanete("../assets/textures/CelestialBody/GanymedeMap.jpg", "Ganymede", 2.0, 0.170, glm::vec3(195, -40, 0));

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[2] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[2]->MakingPlanete("../assets/textures/CelestialBody/IoMap.jpg", "Io", 2.0, 0.036, glm::vec3(195, 60, 0));

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[3] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[3]->MakingPlanete("../assets/textures/CelestialBody/CallistoMap.jpg", "Callisto", 2.0, 0.187, glm::vec3(265, 80, 0));

        m_host_creator = new SimplePlaneteCreator();
        if(m_host_creator == nullptr)
        {
            exit(EXIT_FAILURE);
        }

        m_host_creator->MakingPlanete("../assets/textures/CelestialBody/JupiterCloud.jpg", "Jupiter", 14.0, 3.13, glm::vec3(195, 0, 0));

        m_atmosphere = new Atmosphere(30.3, "Jupiter", "../assets/textures/atmosphere.png");
        if(m_atmosphere == nullptr)
        {
            exit(EXIT_FAILURE);
        }

    }
    else if(m_system_name == "Saturnian System")
    {
        m_companion_name.push_back("Titan");
        m_companion_name.push_back("Enceladus");
        m_companion_name.push_back("Mimas");

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[0] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[0]->MakingPlanete("../assets/textures/CelestialBody/MimasMap.jpg", "Mimas", 2.0, 1.53, glm::vec3(40, -250, 0));

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[1] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[1]->MakingPlanete("../assets/textures/CelestialBody/EnceladusMap.jpg", "Enceladus", 2.0, 0.0, glm::vec3(-60, -250, 0));

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[2] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[2]->MakingPlanete("../assets/textures/CelestialBody/TitanMap.jpg", "Titan", 2.0, 0.33, glm::vec3(0, -170, 0));

        m_host_creator = new PlaneteRingCreator();
        if(m_host_creator == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_host_creator->MakingPlanete("../assets/textures/CelestialBody/SaturnCloud.jpg", "Saturn", 13.0, 26.73, glm::vec3(0.0, -250, 0));

        m_atmosphere = new Atmosphere(28, "Saturn", "../assets/textures/atmosphere.png");
        if(m_atmosphere == nullptr)
        {
            exit(EXIT_FAILURE);
        }

    }
    else
    {
        std::cout << ">> Loading planetary System : no name match found" << std::endl;
    }
    //===================================================================================================================
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** display ***************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos, Shader *host_shader, Shader *companion_shader)
{
    
    glm::mat4 save = modelview;
    glm::vec3 target_point(0.0, 0.0, 0.0);
    glm::vec3 vertical_axe(0.0, 0.0, 1.0);
    glm::mat4 light_src = glm::lookAt(sun_pos, target_point, vertical_axe);
    glm::mat4 save_light_src = light_src;

    if(host_shader != nullptr)
    {
        m_host_creator->UpdatePositionPlan(projection, modelview);
        m_host_creator->updatePosLight(projection, light_src);
        m_host_creator->drawPlanete(projection, modelview, light_src, camPos, hdr, host_shader);
    }

    modelview = save;
    light_src = save_light_src;

    if(companion_shader != nullptr)
    {
        for (int i(0); i < m_companion_count; i++)
        {
            m_moons_creator[i]->UpdatePositionPlan(projection, modelview);
            m_moons_creator[i]->updatePosLight(projection, light_src);
            m_moons_creator[i]->drawPlanete(projection, modelview, light_src, camPos, hdr, companion_shader); 

            modelview = save;
            light_src = save_light_src;

        }
    }
    
        
    modelview = save;
    light_src = save_light_src;

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayName **************************************************************************/
/***********************************************************************************************************************************************************************/

void PlanetarySystem::displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, Shader *name_render_shader)
{
    glm::mat4 save = modelview;

    if(name_render_shader != nullptr)
    {
        

        /*
            CamPos is the M point in spherical coordinate, so we already have his x, y, z coordinate
            but this coordinate are relative to the world reference
            so we add the planete position to the cam position to have the coordinate reference opposite to the planete
            we only use the parametrical coordinate to find the r radius
        */
        if(m_host_creator == nullptr) //exceptionnaly we exit the program because without light it can be a solar position
        {
            exit(EXIT_FAILURE);
        }
        glm::vec3 host_pos = m_host_creator->getPostion();
        
        if(m_host_creator == nullptr) //exceptionnaly we exit the program because without light it can be a solar size
        {
            exit(EXIT_FAILURE);
        }
        float size_plan = m_host_creator->getSizePlan();

        double x = camPos[0] - host_pos[0]; //doesn't know why I have to use the reverse value
        double y = camPos[1] - host_pos[1];
        double z = camPos[2] - host_pos[2];
        double r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
            
        double r = std::sqrt(r_squarre);

        float phi = atan(y/x);
        float theta = acos(z/r);

        if( r >= 100 )
        {
            modelview = translate(modelview, host_pos);
            m_name_renderer.renderText(projection, modelview, size_plan, r, phi, theta, y, name_render_shader);
            // std::cout << name_render_shader << std::endl;
        }

        
        //     m_host_creator->displayName(projection, modelview);

        // modelview = save;

        // for (int i(0); i < m_companion_count; i++)
        // {
        //     m_moons_creator[i]->displayName(projection, modelview);

        //     modelview = save;
        // }

        
    }
    
    modelview = save;

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayAtmo **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *atmo_shader)
{
    if((m_system_name == "Earth System") || (m_system_name == "Jovian System") || (m_system_name == "Saturnian System"))
    {
        glm::mat4 save = modelview;
        glm::vec3 position(0.1, 0.0, 0.0);
        glm::vec3 target_point(0.0, 0.0, 0.0);
        glm::vec3 vertical_axe(0.0, 0.0, 1.0);
        glm::mat4 light_src = glm::lookAt(position, target_point, vertical_axe);

        if(m_host_creator == nullptr) //exceptionnaly we exit the program because without light it can be a solar system
        {
            exit(EXIT_FAILURE);
        }
        m_host_creator->updateAtmoInter(projection, light_src);
        glm::mat4 save_light_src = light_src;

        if(m_host_creator == nullptr) //exceptionnaly we exit the program because without light it can be a solar position
        {
            exit(EXIT_FAILURE);
        }
        glm::vec3 host_pos = m_host_creator->getPostion();

        double x = camPos[0] - host_pos[0]; //doesn't know why I have to use the reverse value
        double y = camPos[1] - host_pos[1];
        double z = camPos[2] - host_pos[2];
        double r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
            
        double r = std::sqrt(r_squarre);

        float phi = atan(y/x);
        float theta = acos(z/r);

        glm::vec3 cameraPos = vec3(x, y, z);

        modelview = translate(modelview, host_pos);
        if(atmo_shader !=nullptr)
        {
            if(m_atmosphere !=nullptr)
            {
                m_atmosphere->display(projection, modelview, phi, theta, cameraPos, light_src, camPos, hdr, atmo_shader);
            }
            
        }
        

        modelview = save;
        light_src = save_light_src;
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayInfo **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, PlaneteInformation *planete_info, Shader *text_shader, Shader *square_shader)
{
    glm::mat4 save = modelview;

    glm::vec3 planete_pos = m_host_creator->getPostion();
    

        float x = camPos[0] - planete_pos[0]; //doesn't know why I have to use the reverse value
        float y = camPos[1] - planete_pos[1];
        float z = camPos[2] - planete_pos[2];
            
            
        float r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
            
        float r = std::sqrt(r_squarre);

        if(r <= 20)
        {
            modelview = lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
            //m_host_creator[i]->drawInfoPlan(projection, modelview, hdr);

            if(m_host_creator == nullptr) //exceptionnaly we exit the program because without 
            {
                exit(EXIT_FAILURE);
            }
            std::string tmp_name = m_host_creator->getName();
            
            if(planete_info != nullptr)
            {
                 if(tmp_name != planete_info->getInfoName())
                {
                    planete_info->changeNamePlan(tmp_name);
                }

                if((text_shader != nullptr) && (square_shader != nullptr))
                {
                    planete_info->renderInfo(projection, modelview, hdr, text_shader, square_shader);
                }
                
            }
            
        }

        modelview = save;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** NOT CONCERN **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displaySkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
{
    //do nothing and doesn't have
}

