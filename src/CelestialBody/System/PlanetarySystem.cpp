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
PlanetarySystem::PlanetarySystem(std::string name_system, int companion_count) : m_name_renderer(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag")
{
    m_system_name = name_system;
    m_companion_count = companion_count;

    m_name_renderer.loadTTF(m_system_name);
}

PlanetarySystem::PlanetarySystem()
{
    
}

PlanetarySystem::~PlanetarySystem()
{
    for (int i(0); i < m_companion_count; i++)
    {
        delete m_moons_creator[i];
    }

    delete m_host_creator;
    
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
        m_moons_creator[0]->MakingPlanete("../assets/textures/CelestialBody/MoonMap.jpg", "Moon", 2.0, 5.145, glm::vec3(-110, 20, 0));
        m_host_creator = new AtmoPlaneteCreator();
        m_host_creator->MakingPlanete("../assets/textures/CelestialBody/EarthDayMap.jpg", "Earth", 5.0, 23.26, glm::vec3(-110, 0, 0));

        // m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/MoonMap.jpg", "Moon", 2.0, 5.145, glm::vec3(-110, 20, 0)));
        // m_host = new AtmoPlanete("../assets/textures/CelestialBody/EarthDayMap.jpg", "Earth", 5.0, 23.26, glm::vec3(-110, 0, 0));
    }
    else if(m_system_name == "Jovian System")
    {
        m_companion_name.push_back("Europa");
        m_companion_name.push_back("Ganymede");
        m_companion_name.push_back("Io");
        m_companion_name.push_back("Callisto");

        m_moons_creator.push_back(new SimplePlaneteCreator());
        m_moons_creator[0]->MakingPlanete("../assets/textures/CelestialBody/EuropaMap.jpg", "Europa", 2.0, 0.469, glm::vec3(-195, 20, 0));

        m_moons_creator.push_back(new SimplePlaneteCreator());
        m_moons_creator[1]->MakingPlanete("../assets/textures/CelestialBody/GanymedeMap.jpg", "Ganymede", 2.0, 0.170, glm::vec3(-195, 40, 0));

        m_moons_creator.push_back(new SimplePlaneteCreator());
        m_moons_creator[2]->MakingPlanete("../assets/textures/CelestialBody/IoMap.jpg", "Io", 2.0, 0.036, glm::vec3(-195, 60, 0));

        m_moons_creator.push_back(new SimplePlaneteCreator());
        m_moons_creator[3]->MakingPlanete("../assets/textures/CelestialBody/CallistoMap.jpg", "Callisto", 2.0, 0.187, glm::vec3(-195, 80, 0));

        m_host_creator = new SimplePlaneteCreator();
        m_host_creator->MakingPlanete("../assets/textures/CelestialBody/JupiterCloud.jpg", "Jupiter", 14.0, 3.13, glm::vec3(-195, 0, 0));

        // m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/EuropaMap.jpg", "Europa", 2.0, 0.469, glm::vec3(-195, 20, 0)));
        // m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/GanymedeMap.jpg", "Ganymede", 2.0, 0.170, glm::vec3(-195, 40, 0)));
        // m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/IoMap.jpg", "Io", 2.0, 0.036, glm::vec3(-195, 60, 0)));
        // m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/CallistoMap.jpg", "Callisto", 2.0, 0.187, glm::vec3(-195, 80, 0)));
        // m_host = new SimplePlanete("../assets/textures/CelestialBody/JupiterCloud.jpg", "Jupiter", 14.0, 3.13, glm::vec3(-195, 0, 0));
        
    }
    else if(m_system_name == "Saturnian System")
    {
        m_companion_name.push_back("Titan");
        m_companion_name.push_back("Enceladus");
        m_companion_name.push_back("Mimas");

        m_moons_creator.push_back(new SimplePlaneteCreator());
        m_moons_creator[0]->MakingPlanete("../assets/textures/CelestialBody/MimasMap.jpg", "Mimas", 2.0, 1.53, glm::vec3(-250, 40, 0));

        m_moons_creator.push_back(new SimplePlaneteCreator());
        m_moons_creator[1]->MakingPlanete("../assets/textures/CelestialBody/EnceladusMap.jpg", "Enceladus", 2.0, 0.0, glm::vec3(-250, 60, 0));

        m_moons_creator.push_back(new SimplePlaneteCreator());
        m_moons_creator[2]->MakingPlanete("../assets/textures/CelestialBody/TitanMap.jpg", "Titan", 2.0, 0.33, glm::vec3(-250, 80, 0));

        m_host_creator = new PlaneteRingCreator();
        m_host_creator->MakingPlanete("../assets/textures/CelestialBody/SaturnCloud.jpg", "Saturn", 13.0, 26.73, glm::vec3(-250, 0, 0));

        // m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/MimasMap.jpg", "Mimas", 2.0, 1.53, glm::vec3(-250, 40, 0)));
        // m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/EnceladusMap.jpg", "Enceladus", 2.0, 0.0, glm::vec3(-250, 60, 0)));
        // m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/TitanMap.jpg", "Titan", 2.0, 0.33, glm::vec3(-250, 80, 0)));
        // m_host = new PlaneteRing("../assets/textures/CelestialBody/SaturnCloud.jpg", "Saturn", 13.0, 26.73, glm::vec3(-250, 0, 0));

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
void PlanetarySystem::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos)
{
    glm::mat4 save = modelview;
    glm::vec3 m_position(0.1, 0.0, 0.0);
    glm::vec3 m_target_point(0.0, 0.0, 0.0);
    glm::vec3 m_vertical_axe(0.0, 0.0, 1.0);
    glm::mat4 light_src = glm::lookAt(m_position, m_target_point, m_vertical_axe);
    glm::mat4 save_light_src = light_src;

    m_host_creator->UpdatePositionPlan(projection, modelview);
    m_host_creator->updatePosLight(projection, light_src);
    m_host_creator->drawPlanete(projection, modelview, light_src, camPos);

    modelview = save;
    light_src = save_light_src;

    for (int i(0); i < m_companion_count; i++)
    {
        m_moons_creator[i]->UpdatePositionPlan(projection, modelview);
        m_moons_creator[i]->updatePosLight(projection, light_src);
        m_moons_creator[i]->drawPlanete(projection, modelview, light_src, camPos); 

        modelview = save;
        light_src = save_light_src;

    }
        
    modelview = save;
    light_src = save_light_src;

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayName **************************************************************************/
/***********************************************************************************************************************************************************************/

void PlanetarySystem::displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos)
{
    glm::vec3 abs_cam  = glm::vec3(abs(camPos[0]), abs(camPos[1]), abs(camPos[2]));
    glm::vec3 pos_host = m_host_creator->getPostion();
    glm::vec3 abs_pos = glm::vec3(abs(pos_host[0]), abs(pos_host[1]), abs(pos_host[2]));

    glm::vec3 dist = abs_cam - abs_pos;
    glm::vec3 abs_dist = glm::vec3(abs(dist[0]), abs(dist[1]), abs(dist[2]));

    glm::mat4 save = modelview;

    if( (abs_dist[0] >= 10) && (abs_dist[1] >= 10) && (abs_dist[2] >= 10) )
    {
        modelview = translate(modelview, pos_host);
        m_name_renderer.renderText(projection, modelview, 10);
    }

    
    //     m_host_creator->displayName(projection, modelview);

    // modelview = save;

    // for (int i(0); i < m_companion_count; i++)
    // {
    //     m_moons_creator[i]->displayName(projection, modelview);

    //     modelview = save;
    // }

    modelview = save;

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** NOT CONCERN **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displaySkybox(glm::mat4 &projection, glm::mat4 &modelview)
{
    //do nothing and doesn't have
}

