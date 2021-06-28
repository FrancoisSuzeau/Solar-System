/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : SolarSystem.cpp

PURPOSE : class SolarSystem
*/

#include "SolarSystem.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
SolarSystem::SolarSystem(std::string name, int celestial_object_count)
{
    m_system_name = name;
    m_companion_count = celestial_object_count;
    m_planetarySYS_count = 3;
    m_simple_planete_count = 5;
    sun = new Star(1, 50, 50, "../assets/textures/CelestialBody/SunMap.jpg", "Sun", 20.0);
    skybox = new Skybox();
}

SolarSystem::SolarSystem() : sun()
{

}

SolarSystem::~SolarSystem()
{
    for (int i(0); i < m_planetarySYS_count; i++)
    {
        delete m_planetary_system[i];
    }

    // for (int i(0); i < m_simple_planete_count; i++)
    // {
    //     delete m_simple_planete[i];
    // }

    for (int i(0); i < m_simple_planete_count; i++)
    {
        delete m_planete_creator[i];
    }
    
    delete sun;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* loadSystem ****************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::loadSystem()
{

    /************************************************* loading planetary system ********************************************************/
    //Earth System
    SystemCreator *earth_system = new PlanetarySystemCreator();
    earth_system->MakingSystem("Earth System", 1);
    m_planetary_system.push_back(earth_system);

    //Jovian System
    SystemCreator *jovian_system = new PlanetarySystemCreator();
    jovian_system->MakingSystem("Jovian System", 4);
    m_planetary_system.push_back(jovian_system);

    //Saturian System
    SystemCreator *saturian_system = new PlanetarySystemCreator();
    saturian_system->MakingSystem("Saturnian System", 3);
    m_planetary_system.push_back(saturian_system);
    
    //===================================================================================================================

    /************************************************* loading simple planete ********************************************************/

    m_planete_creator.push_back(new SimplePlaneteCreator());
    m_planete_creator[0]->MakingPlanete("../assets/textures/CelestialBody/MercuryMap.jpg", "Mercury", 3.0, 0.01, glm::vec3(50.0, 0.0, 0.0));

    m_planete_creator.push_back(new AtmoPlaneteCreator());
    m_planete_creator[1]->MakingPlanete("../assets/textures/CelestialBody/VenusMap.jpg", "Venus", 4.8, 177.3, glm::vec3(-80.0, 0.0, 0.0));

    m_planete_creator.push_back(new AtmoPlaneteCreator());
    m_planete_creator[2]->MakingPlanete("../assets/textures/CelestialBody/MarsMap.jpg", "Mars", 4.5, 25.19, glm::vec3(-140, 0, 0));

    m_planete_creator.push_back(new PlaneteRingCreator());
    m_planete_creator[3]->MakingPlanete("../assets/textures/CelestialBody/UranusCloud.jpg", "Uranus", 7.0, 97.77, glm::vec3(-300.0, 0.0, 0.0));

    m_planete_creator.push_back(new PlaneteRingCreator());
    m_planete_creator[4]->MakingPlanete("../assets/textures/CelestialBody/NeptuneCloud.jpg", "Neptune", 7.0, 26.32, glm::vec3(-350.0, 0.0, 0.0));

    // SimplePlanete *mercury = new SimplePlanete("../assets/textures/CelestialBody/MercuryMap.jpg", "Mercury", 3.0, 0.01, glm::vec3(50.0, 0.0, 0.0));
    // SimplePlanete *venus = new AtmoPlanete("../assets/textures/CelestialBody/VenusMap.jpg", "Venus", 4.8, 177.3, glm::vec3(-80.0, 0.0, 0.0));
    // SimplePlanete *mars = new AtmoPlanete("../assets/textures/CelestialBody/MarsMap.jpg", "Mars", 4.5, 25.19, glm::vec3(-140, 0, 0));
    // SimplePlanete *uranus = new PlaneteRing("../assets/textures/CelestialBody/UranusCloud.jpg", "Uranus", 7.0, 97.77, glm::vec3(-300.0, 0.0, 0.0));
    // SimplePlanete *neptune = new PlaneteRing("../assets/textures/CelestialBody/NeptuneCloud.jpg", "Neptune", 7.0, 26.32, glm::vec3(-350.0, 0.0, 0.0));

    // m_simple_planete.push_back(mercury);
    // m_simple_planete.push_back(venus);
    // m_simple_planete.push_back(mars);
    // m_simple_planete.push_back(uranus);
    // m_simple_planete.push_back(neptune);
    //===================================================================================================================

}
/***********************************************************************************************************************************************************************/
/*********************************************************************************** displaySkybox *********************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displaySkybox(glm::mat4 &projection, glm::mat4 &modelview)
{
    glm::mat4 save = modelview;

        skybox->display(projection, modelview);

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** display ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos)
{
    glm::mat4 save = modelview;

    /************************************************* SUN RENDER ********************************************************/
        glm::vec3 m_position = sun->getCurrentPos(); //cannot postioning to {0.0, 0.0, 0.0} so this the closest
        glm::mat4 light_src = glm::lookAt(m_position, vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0));
        glm::mat4 save_light_src = light_src;

        sun->updatePosition(projection, modelview, 0.0);
        sun->display(projection, modelview);
        

    /************************************************* MERCURY RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;

        m_planete_creator[0]->UpdatePositionPlan(projection, modelview);
        m_planete_creator[0]->updatePosLight(projection, light_src);
        m_planete_creator[0]->drawPlanete(projection, modelview, light_src, camPos);

    /************************************************* VENUS RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planete_creator[1]->UpdatePositionPlan(projection, modelview);
        m_planete_creator[1]->updatePosLight(projection, light_src);
        m_planete_creator[1]->drawPlanete(projection, modelview, light_src, camPos);

    /************************************************* EARTH RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planetary_system[0]->drawSystem(projection, modelview, camPos);
        

    /************************************************* MARS RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planete_creator[2]->UpdatePositionPlan(projection, modelview);
        m_planete_creator[2]->updatePosLight(projection, light_src);
        m_planete_creator[2]->drawPlanete(projection, modelview, light_src, camPos);

    /************************************************* JUPITER RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planetary_system[1]->drawSystem(projection, modelview, camPos);
        
    /************************************************* SATURN RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planetary_system[2]->drawSystem(projection, modelview, camPos);

    /************************************************* URANUS RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planete_creator[3]->UpdatePositionPlan(projection, modelview);
        m_planete_creator[3]->updatePosLight(projection, light_src);
        m_planete_creator[3]->drawPlanete(projection, modelview, light_src, camPos);

    /************************************************* NEPTUNE RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planete_creator[4]->UpdatePositionPlan(projection, modelview);
        m_planete_creator[4]->updatePosLight(projection, light_src);
        m_planete_creator[4]->drawPlanete(projection, modelview, light_src, camPos);

    //restaure the modelview matrix
    modelview = save;

}