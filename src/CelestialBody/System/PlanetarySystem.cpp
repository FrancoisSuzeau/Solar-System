/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : PlanetarySystem.cpp

PURPOSE : class PlanetarySystem
*/



#include "PlanetarySystem.h"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
PlanetarySystem::PlanetarySystem(std::string name_system, int companion_count)
{
    m_system_name = name_system;
    m_companion_count = companion_count;
}

PlanetarySystem::PlanetarySystem()
{
    for (int i(0); i < m_companion_count; i++)
    {
        delete m_moons[i];
    }

    delete m_host;
}

PlanetarySystem::~PlanetarySystem()
{

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** loadSystem ***************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::loadSystem()
{
    /************************************************* loading companion ********************************************************/
    if(m_system_name == "Earth System")
    {
        m_companion_name.push_back("Moon");
        
        m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/MoonMap.jpg", "Moon", 2.0, 5.145, glm::vec3(-110, 20, 0)));
        m_host = new AtmoPlanete("../assets/textures/CelestialBody/EarthDayMap.jpg", "Earth", 5.0, 23.26, glm::vec3(-110, 0, 0));
    }
    else if(m_system_name == "Jovian System")
    {
        m_companion_name.push_back("Europa");
        m_companion_name.push_back("Ganymede");
        m_companion_name.push_back("Io");
        m_companion_name.push_back("Callisto");

        m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/EuropaMap.jpg", "Europa", 2.0, 0.469, glm::vec3(-195, 20, 0)));
        m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/GanymedeMap.jpg", "Ganymede", 2.0, 0.170, glm::vec3(-195, 40, 0)));
        m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/IoMap.jpg", "Io", 2.0, 0.036, glm::vec3(-195, 60, 0)));
        m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/CallistoMap.jpg", "Callisto", 2.0, 0.187, glm::vec3(-195, 80, 0)));
        m_host = new SimplePlanete("../assets/textures/CelestialBody/JupiterCloud.jpg", "Jupiter", 14.0, 3.13, glm::vec3(-195, 0, 0));
        
    }
    else if(m_system_name == "Saturnian System")
    {
        m_companion_name.push_back("Titan");
        m_companion_name.push_back("Enceladus");
        m_companion_name.push_back("Mimas");

        m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/MimasMap.jpg", "Mimas", 2.0, 1.53, glm::vec3(-250, 40, 0)));
        m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/EnceladusMap.jpg", "Enceladus", 2.0, 0.0, glm::vec3(-250, 60, 0)));
        m_moons.push_back(new SimplePlanete("../assets/textures/CelestialBody/TitanMap.jpg", "Titan", 2.0, 0.33, glm::vec3(-250, 80, 0)));
        m_host = new PlaneteRing("../assets/textures/CelestialBody/SaturnCloud.jpg", "../assets/textures/CelestialBody/SaturnRing.png", "Saturn", 13.0, 26.73, glm::vec3(-250, 0, 0));
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
        
    m_host->updatePosition(projection, modelview);
    m_host->updatePositionLight(projection, light_src);
    m_host->display(projection, modelview, light_src, camPos);

    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

    for (int i(0); i < m_companion_count; i++)
    {
        m_moons[i]->updatePosition(projection, modelview);
        m_moons[i]->updatePositionLight(projection, light_src);
        m_moons[i]->display(projection, modelview, light_src, camPos); 

        modelview = save;
        light_src = save_light_src;

    }
    
    modelview = save;
    light_src = save_light_src;


}

void PlanetarySystem::displaySkybox(glm::mat4 &projection, glm::mat4 &modelview)
{
    //do nothing and doesn't have
}