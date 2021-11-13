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
PlanetarySystem::PlanetarySystem(std::string name_system, TTF_Font *police, int companion_count)
{
    m_system_name = name_system;
    m_companion_count = companion_count;

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
    

    if(m_system_name == "Earth System")
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
void PlanetarySystem::loadSystem(int count, TTF_Font *police)
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
        m_moons_creator[0]->MakingPlanete("../assets/textures/CelestialBody/MoonMap.jpg", "Moon", 8.19f, 5.145f, glm::vec3(-15000, 3800, 0), police);

        m_host_creator = new AtmoPlaneteCreator();
        if(m_host_creator == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_host_creator->MakingPlanete("../assets/textures/CelestialBody/EarthDayMap.jpg", "Earth", 30.0f, 23.26f, glm::vec3(-15000, 0, 0), police);

        m_atmosphere = new Atmosphere(1.05f, "Earth");
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
        m_moons_creator[0]->MakingPlanete("../assets/textures/CelestialBody/EuropaMap.jpg", "Europa", 7.5f, 0.469f, glm::vec3(77164, 0, 0), police);

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[1] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[1]->MakingPlanete("../assets/textures/CelestialBody/GanymedeMap.jpg", "Ganymede", 12.39f, 0.170f, glm::vec3(77834, -10700, 0), police);

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[2] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[2]->MakingPlanete("../assets/textures/CelestialBody/IoMap.jpg", "Io", 8.57f, 0.036f, glm::vec3(77834, 4210, 0), police);

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[3] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[3]->MakingPlanete("../assets/textures/CelestialBody/CallistoMap.jpg", "Callisto", 11.36f, 0.187f, glm::vec3(77834, -18800, 0), police);

        m_host_creator = new SimplePlaneteCreator();
        if(m_host_creator == nullptr)
        {
            exit(EXIT_FAILURE);
        }

        m_host_creator->MakingPlanete("../assets/textures/CelestialBody/JupiterCloud.jpg", "Jupiter", 363.27f, 3.13f, glm::vec3(77834, 0, 0), police);

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
        m_moons_creator[0]->MakingPlanete("../assets/textures/CelestialBody/MimasMap.jpg", "Mimas", 1.0f, 1.53f, glm::vec3(0.0, -142485, 0), police);

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[1] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[1]->MakingPlanete("../assets/textures/CelestialBody/EnceladusMap.jpg", "Enceladus", 1.2f, 0.0f, glm::vec3(-2380, -142670, 0), police);

        m_moons_creator.push_back(new SimplePlaneteCreator());
        if(m_moons_creator[2] == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_moons_creator[2]->MakingPlanete("../assets/textures/CelestialBody/TitanMap.jpg", "Titan", 12.5f, 0.33f, glm::vec3(12210, -142670, 0), police);

        m_host_creator = new PlaneteRingCreator();
        if(m_host_creator == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        m_host_creator->MakingPlanete("../assets/textures/CelestialBody/SaturnCloud.jpg", "Saturn", 283.476f, 26.73f, glm::vec3(0.0, -142670, 0), police);

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
void PlanetarySystem::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos, Shader *host_shader, Shader *companion_shader, Shader *ring_shader)
{
    
    glm::mat4 save = modelview;
    glm::vec3 target_point(0.0f, 0.0f, 0.0f);
    glm::vec3 vertical_axe(0.0f, 0.0f, 1.0f);
    glm::mat4 light_src = glm::lookAt(sun_pos, target_point, vertical_axe);
    glm::mat4 save_light_src = light_src;

    if(host_shader != nullptr)
    {
        m_host_creator->UpdatePositionPlan(projection, modelview);
        m_host_creator->updatePosLight(projection, light_src);
        m_host_creator->drawPlanete(projection, modelview, light_src, camPos, hdr, host_shader, ring_shader);

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
        if(m_host_creator == nullptr) 
        {
            exit(EXIT_FAILURE);
        }
        float size_plan = m_host_creator->getSizePlan();
        float r = m_host_creator->getRadius(camPos);

        if( r >= 400 * size_plan ) // juste to allow the application to display host name or moon name depends on the posiiton of the camera
        {
            if( name_render_shader != nullptr )
            {
                m_host_creator->displayName(projection, modelview, camPos, 400, name_render_shader);
                modelview = save;
            }
            modelview = save;
        }
        else
        {
            for (int i(0); i < m_companion_count; i++)
            {
                if(name_render_shader != nullptr)
                {
                    m_moons_creator[i]->displayName(projection, modelview, camPos, 10, name_render_shader);
                    modelview = save;
                }  
                modelview = save;
            }
        }
        modelview = save;
    }
    modelview = save;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayAtmo **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *atmo_shader)
{
    if((m_system_name == "Earth System")) //|| (m_system_name == "Jovian System") || (m_system_name == "Saturnian System"))
    {
        glm::mat4 save = modelview;
        glm::vec3 position(0.1f, 0.0f, 0.0f);
        glm::vec3 target_point(0.0f, 0.0f, 0.0f);
        glm::vec3 vertical_axe(0.0f, 0.0f, 1.0f);
        glm::mat4 light_src = glm::lookAt(position, target_point, vertical_axe);
        glm::mat4 save_light_src = light_src;

        if(m_host_creator != nullptr)
        {
            m_host_creator->UpdatePositionPlan(projection, modelview);
            m_host_creator->updatePosLight(projection, light_src);

            if((m_atmosphere != nullptr) && (atmo_shader != nullptr))
            {
                m_atmosphere->display(projection, modelview, light_src, camPos, hdr, atmo_shader);
            }
        }
               
        modelview = save;
        light_src = save_light_src;
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayInfo **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, std::vector<Shader *> shaders, PlaneteInformation *planete_info)
{
    glm::mat4 save = modelview;

    float r = m_host_creator->getRadius(camPos);
    float size_plan = m_host_creator->getSizePlan();

        if(r <= 10 * size_plan)
        {
            modelview = lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));

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

                if((shaders[0] != nullptr) && (shaders[1] != nullptr))
                {
                    planete_info->renderInfo(projection, modelview, hdr, shaders);
                    modelview = save;
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

void PlanetarySystem::displayAsteroidField(std::vector<glm::mat4> projection_view_mat, bool hdr)
{
    //do nothing and doesn't have
}

