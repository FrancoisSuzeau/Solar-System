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
    m_planete_info = new PlaneteInformation("None");
    m_system_name = name;
    m_companion_count = celestial_object_count;
    m_planetarySYS_count = 3;
    m_simple_planete_count = 5;
    skybox = new Skybox();
    sun = new Star(1, 50, 50, "../assets/textures/CelestialBody/SunMap.jpg", "Sun", 20.0);

    m_body_shader.push_back(new Shader("../src/Shader/Shaders/planeteTexture.vert", "../src/Shader/Shaders/oneTexturePlanete.frag"));
    m_body_shader[0]->loadShader();
    m_body_shader.push_back(new Shader("../src/Shader/Shaders/planeteTexture.vert", "../src/Shader/Shaders/MultiPlaneteTexture.frag"));
    m_body_shader[1]->loadShader();
    m_body_shader.push_back(new Shader("../src/Shader/Shaders/sunShader.vert", "../src/Shader/Shaders/sunShader.frag"));
    m_body_shader[2]->loadShader();

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

    for (int i(0); i < m_simple_planete_count; i++)
    {
        delete m_planete_creator[i];
    }
    
    delete skybox;
    delete sun;

    if(m_planete_info != nullptr)
    {
        delete m_planete_info;
    }

    for (int i(0); i < 3; i++)
    {
        if(m_body_shader[i] != nullptr)
        {
            delete m_body_shader[i];
        }
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* loadSystem ****************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::loadSystem(int count)
{

    /************************************************* loading planetary system ********************************************************/
    //Earth System
    if(count == 1)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        m_planetary_system[0]->MakingSystem("Earth System", 1);
        m_planetary_system[0]->loadSystem(count);
    }

    //Jovian System
    if(count == 2)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        m_planetary_system[1]->MakingSystem("Jovian System", 4);
        m_planetary_system[1]->loadSystem(count);
    }

    //Saturian System
    if(count == 3)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        m_planetary_system[2]->MakingSystem("Saturnian System", 3);
        m_planetary_system[2]->loadSystem(count);
    }  
    //===================================================================================================================

    /************************************************* loading simple planete ********************************************************/

    if(count == 4)
    {
        m_planete_creator.push_back(new SimplePlaneteCreator());
        m_planete_creator[0]->MakingPlanete("../assets/textures/CelestialBody/MercuryMap.jpg", "Mercury", 3.0, 0.01, glm::vec3(50.0, 0.0, 0.0));
    }
    
    if(count == 5)
    {
        m_planete_creator.push_back(new AtmoPlaneteCreator());
        m_planete_creator[1]->MakingPlanete("../assets/textures/CelestialBody/VenusMap.jpg", "Venus", 4.8, 177.3, glm::vec3(-80.0, -80.0, 0.0));
    }

    if(count == 6)
    {
        m_planete_creator.push_back(new AtmoPlaneteCreator());
        m_planete_creator[2]->MakingPlanete("../assets/textures/CelestialBody/MarsMap.jpg", "Mars", 4.5, 25.19, glm::vec3(0, 140, 0));
    }

    if(count == 7)
    {
        m_planete_creator.push_back(new PlaneteRingCreator());
        m_planete_creator[3]->MakingPlanete("../assets/textures/CelestialBody/UranusCloud.jpg", "Uranus", 7.0, 97.77, glm::vec3(-300.0, 0.0, 0.0));
    }
    if(count == 8)
    {
        m_planete_creator.push_back(new PlaneteRingCreator());
        m_planete_creator[4]->MakingPlanete("../assets/textures/CelestialBody/NeptuneCloud.jpg", "Neptune", 7.0, 26.32, glm::vec3(0.0, 350.0, 0.0));
    }
    //===================================================================================================================

}
/***********************************************************************************************************************************************************************/
/*********************************************************************************** displaySkybox *********************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displaySkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
{
    glm::mat4 save = modelview;

        skybox->display(projection, modelview, hdr);

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** display ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos, Shader *host_shader, Shader *companion_shader)
{
    glm::mat4 save = modelview;

    /************************************************* SUN RENDER ********************************************************/
        glm::vec3 m_position = sun->getCurrentPos(); //cannot postioning to {0.0, 0.0, 0.0} so this the closest
        glm::mat4 light_src = glm::lookAt(m_position, vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0));
        glm::mat4 save_light_src = light_src;

        sun->updatePosition(projection, modelview, 0.0);
        sun->updatePositionLight(projection, light_src);
        sun->display(projection, modelview, light_src, camPos, hdr, m_body_shader[2]);
        

    /************************************************* MERCURY RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;


        m_planete_creator[0]->UpdatePositionPlan(projection, modelview);
        m_planete_creator[0]->updatePosLight(projection, light_src);
        m_planete_creator[0]->drawPlanete(projection, modelview, light_src, camPos, hdr, m_body_shader[0]);

    /************************************************* VENUS RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planete_creator[1]->UpdatePositionPlan(projection, modelview);
        m_planete_creator[1]->updatePosLight(projection, light_src);
        m_planete_creator[1]->drawPlanete(projection, modelview, light_src, camPos, hdr, m_body_shader[1]);

    /************************************************* EARTH RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planetary_system[0]->drawSystem(projection, modelview, camPos, hdr, m_position, m_body_shader[1], m_body_shader[0]);

    /************************************************* MARS RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planete_creator[2]->UpdatePositionPlan(projection, modelview);
        m_planete_creator[2]->updatePosLight(projection, light_src);
        m_planete_creator[2]->drawPlanete(projection, modelview, light_src, camPos, hdr, m_body_shader[1]);

    /************************************************* JUPITER RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planetary_system[1]->drawSystem(projection, modelview, camPos, hdr, m_position, m_body_shader[0], m_body_shader[0]);
        
    /************************************************* SATURN RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planetary_system[2]->drawSystem(projection, modelview, camPos, hdr, m_position, m_body_shader[0], m_body_shader[0]);

    /************************************************* URANUS RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planete_creator[3]->UpdatePositionPlan(projection, modelview);
        m_planete_creator[3]->updatePosLight(projection, light_src);
        m_planete_creator[3]->drawPlanete(projection, modelview, light_src, camPos, hdr, m_body_shader[0]);

    /************************************************* NEPTUNE RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        m_planete_creator[4]->UpdatePositionPlan(projection, modelview);
        m_planete_creator[4]->updatePosLight(projection, light_src);
        m_planete_creator[4]->drawPlanete(projection, modelview, light_src, camPos, hdr, m_body_shader[0]);

    //restaure the modelview matrix
    modelview = save;

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayName **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos)
{
    glm::mat4 save = modelview;

    for (int i(0); i < m_planetarySYS_count; i++)
    {
        m_planetary_system[i]->drawName(projection, modelview, camPos);

        modelview = save;
    }

    modelview = save;


    for (int i(0); i < m_simple_planete_count; i++)
    {

      /*
            CamPos is the M point in spherical coordinate, so we already have his x, y, z coordinate
            but this coordinate are relative to the world reference
            so we add the planete position to the cam position to have the coordinate reference opposite to the planete
            we only use the parametrical coordinate to find the r radius
        */

        glm::vec3 planete_pos = m_planete_creator[i]->getPostion();
    

        float x = camPos[0] - planete_pos[0]; //doesn't know why I have to use the reverse value
        float y = camPos[1] - planete_pos[1];
        float z = camPos[2] - planete_pos[2];
	    
        
        float r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
        
        float r = std::sqrt(r_squarre);

        float phi = atan(y/x);
        float theta = acos(z/r);

        if(r >= 100)
        {
            m_planete_creator[i]->displayName(projection, modelview, r, phi, theta, y);
        }
        

        modelview = save;
    }

    modelview = save;

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayAtmo **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr)
{
    glm::mat4 save = modelview;

    /************************************************* SUN ATMO RENDER ********************************************************/

        glm::vec3 position_sun = sun->getCurrentPos(); //cannot postioning to {0.0, 0.0, 0.0} so this the closest
        glm::mat4 light_src = glm::lookAt(position_sun, vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0));
        float x_sun = camPos[0] - position_sun[0]; //doesn't know why I have to use the reverse value
        float y_sun = camPos[1] - position_sun[1];
        float z_sun = camPos[2] - position_sun[2];
            
        float r_square_sun = std::pow(x_sun, 2) + std::pow(y_sun, 2) + std::pow(z_sun, 2);
            
        float r_sun = std::sqrt(r_square_sun);

        float phi_sun = atan(y_sun/x_sun);
        float theta_sun = acos(z_sun/r_sun);

        glm::vec3 cameraPos_sun = vec3(x_sun, y_sun, z_sun);
        sun->displayAtmo(projection, modelview, phi_sun, theta_sun, cameraPos_sun, hdr);

    modelview = save;
    glm::mat4 save_light_src = light_src;

    /************************************************* OTHER ATMO RENDER ********************************************************/

    for(int i(0); i < m_planetarySYS_count; i++)
    {
        m_planetary_system[i]->drawAtmo(projection, modelview, camPos, hdr);
        modelview = save;
    }

    modelview = save;

    for(int i(0); i < m_simple_planete_count; i++)
    {
        glm::vec3 planete_pos = m_planete_creator[i]->getPostion();
    

        float x = camPos[0] - planete_pos[0]; //doesn't know why I have to use the reverse value
        float y = camPos[1] - planete_pos[1];
        float z = camPos[2] - planete_pos[2];
            
            
        float r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
            
        float r = std::sqrt(r_squarre);

        float phi = atan(y/x);
        float theta = acos(z/r);

        glm::vec3 cameraPos = vec3(x, y, z);

        m_planete_creator[i]->updateAtmoInter(projection, light_src);
        m_planete_creator[i]->drawAtmoPlanete(projection, modelview, phi, theta, cameraPos, light_src, camPos, hdr);

        modelview = save;
        light_src = save_light_src;
    }

    modelview = save;
    light_src = save_light_src;

    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayInfo **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, PlaneteInformation *plan_info)
{
    glm::mat4 save = modelview;

    for(int i(0); i < m_simple_planete_count; i++)
    {
        glm::vec3 planete_pos = m_planete_creator[i]->getPostion();
    

        float x = camPos[0] - planete_pos[0]; //doesn't know why I have to use the reverse value
        float y = camPos[1] - planete_pos[1];
        float z = camPos[2] - planete_pos[2];
            
            
        float r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
            
        float r = std::sqrt(r_squarre);

        if(r <= 20)
        {
            modelview = lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
            //m_planete_creator[i]->drawInfoPlan(projection, modelview, hdr);
            std::string tmp_name = m_planete_creator[i]->getName();
            
            if(tmp_name != m_planete_info->getInfoName())
            {
                m_planete_info->changeNamePlan(tmp_name);
            }


            
            m_planete_info->renderInfo(projection, modelview, hdr);
        }


        modelview = save;
    
    }

    modelview = save;

    //display information of planetof the planetary system
    for (int i(0); i < m_planetarySYS_count; i++)
    {
        m_planetary_system[i]->drawInfo(projection, modelview, camPos, hdr, m_planete_info);

        modelview = save;
    }

    modelview = save;
    
}