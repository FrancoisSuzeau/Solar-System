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
SolarSystem::SolarSystem(std::string name, TTF_Font *police, int celestial_object_count, Shader *model_shader)
{
    m_planete_info = new PlaneteInformation("None", police);
    assert(m_planete_info);

    m_system_name = name;
    m_companion_count = celestial_object_count;
    m_planetarySYS_count = 3;
    m_simple_planete_count = 5;

    skybox = new Skybox();
    assert(skybox);

    sun = new Star(1, 70, 70, "../assets/textures/CelestialBody/SunMap.jpg", "Sun", 3270);
    assert(sun);

    m_asteroid_field = new AsteroidField(model_shader);
    assert(m_asteroid_field);

    shaders.push_back(new Shader("../src/Shader/Shaders/planeteTexture.vert", "../src/Shader/Shaders/oneTexturePlanete.frag"));
    assert(shaders[0]);
    assert(shaders[0]->loadShader());

    shaders.push_back(new Shader("../src/Shader/Shaders/planeteTexture.vert", "../src/Shader/Shaders/MultiPlaneteTexture.frag"));
    assert(shaders[1]);
    assert(shaders[1]->loadShader());

    shaders.push_back(new Shader("../src/Shader/Shaders/sunShader.vert", "../src/Shader/Shaders/sunShader.frag"));
    assert(shaders[2]);
    assert(shaders[2]->loadShader());

    shaders.push_back(new Shader("../src/Shader/Shaders/texture.vert", "../src/Shader/Shaders/texture.frag"));
    assert(shaders[3]);
    assert(shaders[3]->loadShader());

    shaders.push_back(new Shader("../src/Shader/Shaders/sphereShader.vert", "../src/Shader/Shaders/sphereShader.frag"));
    assert(shaders[4]);
    assert(shaders[4]->loadShader());

    shaders.push_back(new Shader("../src/Shader/Shaders/sunAtmo.vert", "../src/Shader/Shaders/sunAtmo.frag"));
    assert(shaders[5]);
    assert(shaders[5]->loadShader());

    if(model_shader != nullptr)
    {
        m_model_shader = model_shader;
    }
    
    this->initData();
}

SolarSystem::SolarSystem() : sun()
{

}

SolarSystem::~SolarSystem()
{
    for (std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
    {
        if(*it != nullptr)
        {
            delete *it;
        }
        
    }

    for (std::vector<PlaneteCreator*>::iterator it = m_planete_creator.begin(); it != m_planete_creator.end(); ++it)
    {
        if(*it != nullptr)
        {
            delete *it;
        }
        
    }
    
    if(skybox != nullptr)
    {
        delete skybox;
    }
    
    if(sun != nullptr)
    {
        delete sun;
    }

    if(m_asteroid_field != nullptr)
    {
        delete m_asteroid_field;
    }
    

    if(m_planete_info != nullptr)
    {
        delete m_planete_info;
    }

    for (std::vector<Shader*>::iterator it = shaders.begin(); it!= shaders.end(); ++it)
    {
        if(*it != nullptr)
        {
            delete *it;
        }
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** initData *****************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::initData()
{
    m_data.push_back({"../assets/textures/CelestialBody/MercuryMap.jpg", "Mercury", 11.49f, 0.01f, glm::vec3(5790.0f, 0.0f, 0.0f)});
    m_data.push_back({"../assets/textures/CelestialBody/VenusMap.jpg", "Venus", 28.47f, 177.3f, glm::vec3(0.0f, -10820.0f, 0.0f)});
    m_data.push_back({"../assets/textures/CelestialBody/MarsMap.jpg", "Mars", 15.99f, 25.19f, glm::vec3(0, 22790, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/UranusCloud.jpg", "Uranus", 120.21f, 97.77f, glm::vec3(-287070.0f, 0.0f, 0.0f)});
    m_data.push_back({"../assets/textures/CelestialBody/NeptuneCloud.jpg", "Neptune", 116.49f, 26.32f, glm::vec3(0.0f, 449840.0f, 0.0f)});
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* loadSystem ****************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::loadSystem(int count, TTF_Font *police)
{
    assert(police);
    /************************************************* loading planetary system ********************************************************/
    //Earth System
    if(count == 1)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        assert(m_planetary_system[0]);
        assert(m_planetary_system[0]->MakingSystem("Earth System", 1, police));
        m_planetary_system[0]->loadSystem(count, police);
    }

    //Jovian System
    if(count == 2)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        assert(m_planetary_system[1]);
        assert(m_planetary_system[1]->MakingSystem("Jovian System", 4, police));
        m_planetary_system[1]->loadSystem(count, police);
    }

    //Saturian System
    if(count == 3)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        assert(m_planetary_system[2]);
        assert(m_planetary_system[2]->MakingSystem("Saturnian System", 3, police));
        m_planetary_system[2]->loadSystem(count, police);
    }  
    //===================================================================================================================

    /************************************************* loading simple planete ********************************************************/
    if(count == 4)
    {
        m_planete_creator.push_back(new SimplePlaneteCreator());
        assert(m_planete_creator[0]);
        assert(m_planete_creator[0]->MakingPlanete(m_data[0], police));
    }
    
    if(count == 5)
    {
        m_planete_creator.push_back(new AtmoPlaneteCreator());
        assert(m_planete_creator[1]);
        assert(m_planete_creator[1]->MakingPlanete(m_data[1], police));
    }

    if(count == 6)
    {
        m_planete_creator.push_back(new AtmoPlaneteCreator());
        assert(m_planete_creator[2]);
        assert(m_planete_creator[2]->MakingPlanete(m_data[2], police));
    }

    if(count == 7)
    {
        m_planete_creator.push_back(new PlaneteRingCreator());
        assert(m_planete_creator[3]);
        assert(m_planete_creator[3]->MakingPlanete(m_data[3], police));
    }
    if(count == 8)
    {
        m_planete_creator.push_back(new PlaneteRingCreator());
        assert(m_planete_creator[4]);
        assert(m_planete_creator[4]->MakingPlanete(m_data[4], police));
    }
    //===================================================================================================================

    
}
/***********************************************************************************************************************************************************************/
/*********************************************************************************** displaySkybox *********************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displaySkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
{
    glm::mat4 save = modelview;

        if(skybox != nullptr)
        {
            skybox->display(projection, modelview, hdr);
        }
        

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayAsteroidField ******************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayAsteroidField(std::vector<glm::mat4> projection_view_mat, bool hdr)
{
    glm::mat4 save = projection_view_mat[1];

    if(m_asteroid_field != nullptr)
    {
        m_asteroid_field->drawAsteroidField(projection_view_mat, hdr);
    }
        
    projection_view_mat[1] = save;
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** display ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos, Shader *host_shader, Shader *companion_shader, Shader *ring_shader)
{
    glm::mat4 save = modelview;

    /************************************************* SUN RENDER ********************************************************/
        if(sun == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        glm::vec3 m_position = sun->getCurrentPos(); //cannot postioning to {0.0, 0.0, 0.0} so this the closest
        glm::mat4 light_src = glm::lookAt(m_position, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 save_light_src = light_src;

        if(sun != nullptr)
        {
            sun->updatePosition(projection, modelview, 0.0f);
            sun->updatePositionLight(projection, light_src);
        
            if(shaders[2] != nullptr)
            {
                sun->display(projection, modelview, light_src, camPos, hdr, shaders[2]);
            }
        }

    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

    for (std::vector<PlaneteCreator*>::iterator it = m_planete_creator.begin(); it != m_planete_creator.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->UpdatePositionPlan(projection, modelview);
            it[0]->updatePosLight(projection, light_src);

            if((shaders[0] != nullptr) && (shaders[3] != nullptr))
            {
                if((it[0]->getName() == "Uranus") || (it[0]->getName() == "Neptune"))
                {
                    it[0]->drawPlanete(projection, modelview, light_src, camPos, hdr, shaders[0], shaders[3]);
                }
                else
                {
                    it[0]->drawPlanete(projection, modelview, light_src, camPos, hdr, shaders[0]);
                }
                

                //restaure the modelview matrix
                modelview = save;
                light_src = save_light_src;
            }
        }
    }
        
    /************************************************* EARTH RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planetary_system[0] != nullptr)
        {
            if( (shaders[1] != nullptr) && (shaders[0] != nullptr) )
            {
                m_planetary_system[0]->drawSystem(projection, modelview, camPos, hdr, m_position, shaders[1], shaders[0]);
            }
        }
        
    /************************************************* JUPITER RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planetary_system[1] != nullptr)
        {
            if( shaders[0] != nullptr )
            {
                m_planetary_system[1]->drawSystem(projection, modelview, camPos, hdr, m_position, shaders[0], shaders[0]);
            }
        }
        
    /************************************************* SATURN RENDER ********************************************************/
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

        if(m_planetary_system[2] != nullptr)
        {
            if( (shaders[0] != nullptr) && (shaders[3] != nullptr) )
            {
                m_planetary_system[2]->drawSystem(projection, modelview, camPos, hdr, m_position, shaders[0], shaders[0], shaders[3]);
            }
        }
        
    
    //restaure the modelview matrix
    modelview = save;
    light_src = save_light_src;

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayName **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, Shader *name_render_shader)
{
    
    glm::mat4 save = modelview;

    for (int i(0); i < m_planetarySYS_count; i++)
    {
        if(m_planetary_system[i] != nullptr)
        {
            if(name_render_shader != nullptr)
            {
                m_planetary_system[i]->drawName(projection, modelview, camPos, name_render_shader);
                modelview = save;

            }
        }

        modelview = save;
    }

    modelview = save;

    for (int i(0); i < m_simple_planete_count; i++)
    {
       if(m_planete_creator[i] != nullptr)
       {
           if(name_render_shader != nullptr)
            {
                m_planete_creator[i]->displayName(projection, modelview, camPos, 400, name_render_shader);
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
void SolarSystem::displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *atmo_shader)
{
    glm::mat4 save = modelview;

    /************************************************* SUN ATMO RENDER ********************************************************/
        if(sun == nullptr)
        {
            exit(EXIT_FAILURE);
        }
        glm::vec3 position_sun = sun->getCurrentPos(); //cannot postioning to {0.0, 0.0, 0.0} so this the closest
        glm::mat4 light_src = glm::lookAt(position_sun, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
        
        // if(sun != nullptr)
        // {
        //     if(shaders[5] != nullptr)
        //     {
        //         sun->displayAtmo(projection, modelview, hdr, shaders[5]);
        //     }
            
        // }

    modelview = save;
    glm::mat4 save_light_src = light_src;

    /************************************************* OTHER ATMO RENDER ********************************************************/

    for(std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            if(shaders[4] != nullptr)
            {
                it[0]->drawAtmo(projection, modelview, camPos, hdr, shaders[4]);
            }
            
        }
        
        modelview = save;
    }

    modelview = save;

    for(std::vector<PlaneteCreator*>::iterator it = m_planete_creator.begin(); it != m_planete_creator.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->UpdatePositionPlan(projection, modelview);
            it[0]->updatePosLight(projection, light_src);

            if((shaders[4] != nullptr) && (it[0] != nullptr))
            {
                it[0]->drawAtmoPlanete(projection, modelview, light_src, camPos, hdr, shaders[4]);
            }
            
        }

        modelview = save;
        light_src = save_light_src;
    }

    modelview = save;
    light_src = save_light_src;

    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayInfo **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, std::vector<Shader *> shaders, PlaneteInformation *plan_info)
{
    
    glm::mat4 save = modelview;

    for(std::vector<PlaneteCreator*>::iterator it = m_planete_creator.begin(); it != m_planete_creator.end(); ++it)
    {
        if( (it[0] != nullptr) && (m_planete_info != nullptr))
        {
            float r = it[0]->getRadius(camPos);
            float size_plan = it[0]->getSizePlan();

            if(r <= 10 * size_plan)
            {
                modelview = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
                std::string tmp_name = it[0]->getName();
                
                if(tmp_name != m_planete_info->getInfoName())
                {
                    m_planete_info->changeNamePlan(tmp_name);
                }


                if((shaders[0] != nullptr) && (shaders[1] != nullptr))
                {
                    m_planete_info->renderInfo(projection, modelview, hdr, shaders);
                    modelview = save;
                }
            }
        }
        modelview = save;
    }
    modelview = save;

    //display information of planetof the planetary system
    for (std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            if((shaders[0] != nullptr) && (shaders[1] != nullptr))
            {
                it[0]->drawInfo(projection, modelview, camPos, hdr, shaders, m_planete_info);
                modelview = save;
            }
        }
        
        modelview = save;
    }

    modelview = save;
    
}