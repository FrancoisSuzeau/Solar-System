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
PlanetarySystem::PlanetarySystem(sys_init_data data, TTF_Font *police)
{
    m_system_name = data.name_sys;
    m_companion_count = data.companion_count;

    this->initData();
}

PlanetarySystem::PlanetarySystem()
{
    
}

PlanetarySystem::~PlanetarySystem()
{
    for (std::vector<PlaneteCreator*>::iterator it = m_moons_creator.begin(); it != m_moons_creator.end(); ++it)
    {
        if(*it != nullptr)
        {
            delete *it;
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
/******************************************************************************** initData *****************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::initData()
{
    m_data.push_back({"../assets/textures/CelestialBody/MoonMap.jpg", "Moon", 8.19f, 5.145f, glm::vec3(-15000, 3800, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/EarthDayMap.jpg", "Earth", 30.0f, 23.26f, glm::vec3(-15000, 0, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/EuropaMap.jpg", "Europa", 7.5f, 0.469f, glm::vec3(77164, 0, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/GanymedeMap.jpg", "Ganymede", 12.39f, 0.170f, glm::vec3(77834, -10700, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/IoMap.jpg", "Io", 8.57f, 0.036f, glm::vec3(77834, 4210, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/CallistoMap.jpg", "Callisto", 11.36f, 0.187f, glm::vec3(77834, -18800, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/JupiterCloud.jpg", "Jupiter", 363.27f, 3.13f, glm::vec3(77834, 0, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/MimasMap.jpg", "Mimas", 1.0f, 1.53f, glm::vec3(0.0, -142485, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/EnceladusMap.jpg", "Enceladus", 1.2f, 0.0f, glm::vec3(-2380, -142670, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/TitanMap.jpg", "Titan", 12.5f, 0.33f, glm::vec3(12210, -142670, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/SaturnCloud.jpg", "Saturn", 283.476f, 26.73f, glm::vec3(0.0, -142670, 0)});
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** loadSystem ***************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::loadSystem(int count, TTF_Font *police)
{
    /************************************************* loading companion ********************************************************/
    if(m_system_name == "Earth System")
    {
        m_moons_creator.push_back(new SimplePlaneteCreator());
        assert(m_moons_creator[0]);
        assert(m_moons_creator[0]->MakingPlanete(m_data[0], police));

        m_host_creator = new AtmoPlaneteCreator();
        assert(m_host_creator);
        assert(m_host_creator->MakingPlanete(m_data[1], police));

        m_atmosphere = new Atmosphere(1.05f, "Earth");
        assert(m_atmosphere);
    }
    else if(m_system_name == "Jovian System")
    {
        for (int i(2); i < 6; i++)
        {
            m_moons_creator.push_back(new SimplePlaneteCreator());
            assert(m_moons_creator[i-2]);
            assert(m_moons_creator[i-2]->MakingPlanete(m_data[i], police));
        }
        
        m_host_creator = new SimplePlaneteCreator();
        assert(m_host_creator);
        assert(m_host_creator->MakingPlanete(m_data[6], police));

    }
    else if(m_system_name == "Saturnian System")
    {
        for (int i(7); i < 10; i++)
        {
            m_moons_creator.push_back(new SimplePlaneteCreator());
            assert(m_moons_creator[i-7]);
            assert(m_moons_creator[i-7]->MakingPlanete(m_data[i], police));
        }

        m_host_creator = new PlaneteRingCreator();
        assert(m_host_creator);
        assert(m_host_creator->MakingPlanete(m_data[10], police));

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
void PlanetarySystem::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *host_shader, Shader *companion_shader, Shader *ring_shader)
{
    
    glm::mat4 save = modelview;

    if(host_shader != nullptr)
    {
        m_host_creator->UpdatePositionPlan();
        m_host_creator->drawPlanete(projection, modelview, camPos, hdr, host_shader, ring_shader);

    }

    modelview = save;

    if(companion_shader != nullptr)
    {
        for (int i(0); i < m_companion_count; i++)
        {
            m_moons_creator[i]->UpdatePositionPlan();
            m_moons_creator[i]->drawPlanete(projection, modelview, camPos, hdr, companion_shader); 

            modelview = save;
        }
    }
    
    modelview = save;

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
    if((m_system_name == "Earth System"))
    {
        glm::mat4 save = modelview;

        if(m_host_creator != nullptr)
        {
            m_host_creator->UpdatePositionPlan();

            if((m_atmosphere != nullptr) && (atmo_shader != nullptr))
            {
                m_atmosphere->display(projection, modelview, camPos, hdr, atmo_shader);
            }
        }
               
        modelview = save;
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

