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
SolarSystem::SolarSystem(sys_init_data data, TTF_Font *police, Shader *model_shader)
{
    m_planete_info = new PlaneteInformation("None", police);
    assert(m_planete_info);

    m_system_name = data.name_sys;
    m_companion_count = data.companion_count;
    m_planetarySYS_count = 3;
    m_simple_planete_count = 5;

    skybox = new Skybox();
    assert(skybox);

    sun = new Star(1, 70, 70, "../assets/textures/CelestialBody/SunMap.jpg", "Sun", 500);
    // sun = new Star(1, 70, 70, "../assets/textures/CelestialBody/SunMap.jpg", "Sun", 3270);
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
    m_data.push_back({"../assets/textures/CelestialBody/MercuryMap.jpg", "../assets/textures/normalMap/mercury_normalMap.jpg", "../assets/textures/displacementMap/mercury_dispMap.jpg", "Mercury", 11.49f, 0.01f, glm::vec3(5790.0f, 0.0f, 0.0f)});
    m_data.push_back({"../assets/textures/CelestialBody/VenusMap.jpg", "../assets/textures/normalMap/venus_normalMap.jpg", "../assets/textures/displacementMap/venus_dispMap.jpg", "Venus", 28.47f, 177.3f, glm::vec3(0.0f, -10820.0f, 0.0f)});
    m_data.push_back({"../assets/textures/CelestialBody/MarsMap.jpg", "../assets/textures/normalMap/mars_normalMap.jpg", "../assets/textures/displacementMap/mars_dispMap.jpg", "Mars", 15.99f, 25.19f, glm::vec3(0, 22790, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/UranusCloud.jpg", "../assets/textures/normalMap/uranus_normalMap.jpg", "../assets/textures/displacementMap/uranus_dispMap.jpg", "Uranus", 120.21f, 97.77f, glm::vec3(-28707.0f, 0.0f, 0.0f)});
    m_data.push_back({"../assets/textures/CelestialBody/NeptuneCloud.jpg", "../assets/textures/normalMap/neptune_normalMap.jpg", "../assets/textures/displacementMap/neptune_dispMap.jpg", "Neptune", 116.49f, 26.32f, glm::vec3(0.0f, 44984.0f, 0.0f)});

    sys_data.push_back({"Earth System", 1});
    sys_data.push_back({"Jovian System", 4});
    sys_data.push_back({"Saturnian System", 3});
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
        assert(m_planetary_system[0]->MakingSystem(sys_data[0], police));
        m_planetary_system[0]->loadSystem(count, police);
    }

    //Jovian System
    if(count == 2)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        assert(m_planetary_system[1]);
        assert(m_planetary_system[1]->MakingSystem(sys_data[1], police));
        m_planetary_system[1]->loadSystem(count, police);
    }

    //Saturian System
    if(count == 3)
    {
        m_planetary_system.push_back(new PlanetarySystemCreator());
        assert(m_planetary_system[2]);
        assert(m_planetary_system[2]->MakingSystem(sys_data[2], police));
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
void SolarSystem::displaySkybox(RenderData &render_data)
{
    render_data.initSaveMat();

        if(skybox != nullptr)
        {
            skybox->display(render_data);
        }
        

    render_data.saveViewMat();
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayAsteroidField ******************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayAsteroidField(RenderData &render_data, glm::vec3 camPos)
{
    glm::mat4 save = render_data.getViewMat();

    if(m_asteroid_field != nullptr)
    {
        m_asteroid_field->drawAsteroidField(render_data, camPos);
    }
        
    render_data.updateView(save);
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** display ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::display(RenderData &render_data, glm::vec3 &camPos, Shader *host_shader, Shader *companion_shader, Shader *ring_shader)
{
    // glm::mat4 save = view;
    render_data.initSaveMat();

    /************************************************* SUN RENDER ********************************************************/
        if(sun == nullptr)
        {
            exit(EXIT_FAILURE);
        }

        if(sun != nullptr)
        {
            sun->updatePosition();
        
            if(shaders[2] != nullptr)
            {
                sun->display(render_data, camPos, shaders[2]);
            }
        }

    render_data.saveViewMat();

    for (std::vector<PlaneteCreator*>::iterator it = m_planete_creator.begin(); it != m_planete_creator.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->UpdatePositionPlan();

            if((shaders[0] != nullptr) && (shaders[3] != nullptr))
            {
                if((it[0]->getName() == "Uranus") || (it[0]->getName() == "Neptune"))
                {
                    it[0]->drawPlanete(render_data, camPos, shaders[0], shaders[3]);
                }
                else if((it[0]->getName() == "Mars") || (it[0]->getName() == "Venus"))
                {
                    it[0]->drawPlanete(render_data, camPos, shaders[1]);
                }
                else
                {
                    it[0]->drawPlanete(render_data, camPos, shaders[0]);
                }
                
                render_data.saveViewMat();
            }
        }
    }
        
    /************************************************* PLANETARY SYSTEM RENDER ********************************************************/
    render_data.saveViewMat();

    int i(0);
    for (std::vector<sys_init_data>::iterator it = sys_data.begin(); it != sys_data.end(); ++it)
    {

        if(m_planetary_system[i] != nullptr)
        {
            if( (shaders[1] != nullptr) && (shaders[0] != nullptr) && (shaders[3] != nullptr))
            {
                if(it[0].name_sys == "Earth System")
                {
                    m_planetary_system[i]->drawSystem(render_data, camPos, shaders[1], shaders[0]);
                    render_data.saveViewMat();
                }
                else if(it[0].name_sys == "Jovian System")
                {
                    m_planetary_system[i]->drawSystem(render_data, camPos,  shaders[0], shaders[0]);
                    render_data.saveViewMat();
                }
                else if(it[0].name_sys == "Saturnian System")
                {
                    m_planetary_system[i]->drawSystem(render_data, camPos, shaders[0], shaders[0], shaders[3]);
                    render_data.saveViewMat();
                }
            }
            i++;
        }
    }

    //restaure the view matrix
    render_data.saveViewMat();
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayName **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayName(RenderData &render_data, glm::vec3 &camPos, Shader *name_render_shader)
{
    
    render_data.initSaveMat();

    for (int i(0); i < m_planetarySYS_count; i++)
    {
        if(m_planetary_system[i] != nullptr)
        {
            if(name_render_shader != nullptr)
            {
                m_planetary_system[i]->drawName(render_data, camPos, name_render_shader);
                render_data.saveViewMat();

            }
        }

        render_data.saveViewMat();
    }

    render_data.saveViewMat();

    for (int i(0); i < m_simple_planete_count; i++)
    {
       if(m_planete_creator[i] != nullptr)
       {
           if(name_render_shader != nullptr)
            {
                m_planete_creator[i]->displayName(render_data, camPos, 400, name_render_shader);
                render_data.saveViewMat();

            }
       }

        render_data.saveViewMat();
    }

    render_data.saveViewMat();

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayAtmo **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayAtmo(RenderData &render_data, glm::vec3 &camPos, Shader *atmo_shader)
{
    render_data.initSaveMat();

    /************************************************* SUN ATMO RENDER ********************************************************/
        if(sun == nullptr)
        {
            exit(EXIT_FAILURE);
        }

    render_data.saveViewMat();

    /************************************************* OTHER ATMO RENDER ********************************************************/

    for(std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            if(shaders[4] != nullptr)
            {
                it[0]->drawAtmo(render_data, camPos, shaders[4]);
            }
            
        }
        
        render_data.saveViewMat();
    }

    render_data.saveViewMat();

    for(std::vector<PlaneteCreator*>::iterator it = m_planete_creator.begin(); it != m_planete_creator.end(); ++it)
    {
        if(it[0] != nullptr)
        {

            if((shaders[4] != nullptr) && (it[0] != nullptr))
            {
                it[0]->drawAtmoPlanete(render_data, camPos, shaders[4]);
            }
            
        }

        render_data.saveViewMat();
    }

    render_data.saveViewMat();
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayInfo **************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::displayInfo(RenderData &render_data, glm::vec3 &camPos, std::vector<Shader *> shaders, PlaneteInformation *plan_info)
{
    
    glm::mat4 save = render_data.getViewMat();

    for(std::vector<PlaneteCreator*>::iterator it = m_planete_creator.begin(); it != m_planete_creator.end(); ++it)
    {
        if( (it[0] != nullptr) && (m_planete_info != nullptr))
        {
            float r = it[0]->getRadius(camPos);
            float size_plan = it[0]->getSizePlan();

            if(r <= 10 * size_plan)
            {
                // view = lookAt(vec3(0.0f, 0.0f, 1.71f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
                render_data.lockViewMat(glm::vec3(0.0f, 0.0f, 1.71f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                std::string tmp_name = it[0]->getName();
                
                if(tmp_name != m_planete_info->getInfoName())
                {
                    m_planete_info->changeNamePlan(tmp_name);
                }


                if((shaders[0] != nullptr) && (shaders[1] != nullptr))
                {
                    m_planete_info->renderInfo(render_data, shaders);
                    render_data.updateView(save);
                }
            }
        }
        render_data.updateView(save);
    }
    render_data.updateView(save);

    //display information of planetof the planetary system
    for (std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            if((shaders[0] != nullptr) && (shaders[1] != nullptr))
            {
                it[0]->drawInfo(render_data, camPos, shaders, m_planete_info);
                render_data.updateView(save);
            }
        }
        
        render_data.updateView(save);
    }

    render_data.updateView(save);
    
}