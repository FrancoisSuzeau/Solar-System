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
    m_data.push_back({"../assets/textures/CelestialBody/MoonMap.jpg", "../assets/textures/normalMap/moon_normalMap.jpg", "../assets/textures/displacementMap/moon_dispMap.jpg", "Moon", 8.19f, 5.145f, glm::vec3(-15000, 3800, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/EarthDayMap.jpg", "../assets/textures/normalMap/earth_normalMap.jpg", "../assets/textures/displacementMap/earth_dispMap.jpg", "Earth", 30.0f, 23.26f, glm::vec3(-15000, 0, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/EuropaMap.jpg", "../assets/textures/normalMap/europa_normalMap.jpg", "../assets/textures/displacementMap/europa_dispMap.jpg", "Europa", 7.5f, 0.469f, glm::vec3(77164, 0, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/GanymedeMap.jpg", "../assets/textures/normalMap/ganymede_normalMap.jpg", "../assets/textures/displacementMap/ganymede_dispMap.jpg", "Ganymede", 12.39f, 0.170f, glm::vec3(77834, -10700, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/IoMap.jpg", "../assets/textures/normalMap/io_normalMap.jpg", "../assets/textures/displacementMap/io_dispMap.jpg", "Io", 8.57f, 0.036f, glm::vec3(77834, 4210, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/CallistoMap.jpg", "../assets/textures/normalMap/callisto_normalMap.jpg", "../assets/textures/displacementMap/callisto_dispMap.jpg", "Callisto", 11.36f, 0.187f, glm::vec3(77834, -18800, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/JupiterCloud.jpg", "../assets/textures/normalMap/jupiter_normalMap.jpg", "../assets/textures/displacementMap/jupiter_dispMap.jpg", "Jupiter", 363.27f, 3.13f, glm::vec3(77834, 0, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/MimasMap.jpg", "../assets/textures/normalMap/mimas_normalMap.jpg", "../assets/textures/displacementMap/mimas_dispMap.jpg", "Mimas", 1.0f, 1.53f, glm::vec3(2380.0, -14248, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/EnceladusMap.jpg", "../assets/textures/normalMap/enceladus_normalMap.jpg", "../assets/textures/displacementMap/enceladus_dispMap.jpg", "Enceladus", 1.2f, 0.0f, glm::vec3(-2380, -14267, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/TitanMap.jpg", "../assets/textures/normalMap/titan_normalMap.jpg", "../assets/textures/displacementMap/titan_dispMap.jpg", "Titan", 12.5f, 0.33f, glm::vec3(12210, -14267, 0)});
    m_data.push_back({"../assets/textures/CelestialBody/SaturnCloud.jpg", "../assets/textures/normalMap/saturn_normalMap.jpg", "../assets/textures/displacementMap/uranus_dispMap.jpg", "Saturn", 283.476f, 26.73f, glm::vec3(0.0, -14267, 0)});
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

        m_atmosphere = new Atmosphere(1.05f, "Jupiter");
        assert(m_atmosphere);

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

        m_atmosphere = new Atmosphere(1.05f, "Saturn");
        assert(m_atmosphere);
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
void PlanetarySystem::display(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, bool hdr, Shader *host_shader, Shader *companion_shader, Shader *ring_shader)
{
    
    glm::mat4 save = view;

    if(host_shader != nullptr)
    {
        m_host_creator->UpdatePositionPlan();
        m_host_creator->drawPlanete(projection, view, camPos, hdr, host_shader, ring_shader);

    }

    view = save;

    if(companion_shader != nullptr)
    {
        for (int i(0); i < m_companion_count; i++)
        {
            m_moons_creator[i]->UpdatePositionPlan();
            m_moons_creator[i]->drawPlanete(projection, view, camPos, hdr, companion_shader); 

            view = save;
        }
    }
    
    view = save;

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayName **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayName(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, Shader *name_render_shader)
{
    glm::mat4 save = view;

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
                m_host_creator->displayName(projection, view, camPos, 400, name_render_shader);
                view = save;
            }
            view = save;
        }
        else
        {
            for (int i(0); i < m_companion_count; i++)
            {
                if(name_render_shader != nullptr)
                {
                    m_moons_creator[i]->displayName(projection, view, camPos, 10, name_render_shader);
                    view = save;
                }  
                view = save;
            }
        }
        view = save;
    }
    view = save;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayAtmo **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayAtmo(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, bool hdr, Shader *atmo_shader)
{
    if((m_system_name == "Earth System") || (m_system_name == "Jovian System") || (m_system_name == "Saturnian System"))
    {
        glm::mat4 save = view;

        if(m_host_creator != nullptr)
        {
            if((m_atmosphere != nullptr) && (atmo_shader != nullptr))
            {
                m_atmosphere->updatePosAtmo(m_host_creator->getPostion());
                m_atmosphere->display(projection, view, camPos, hdr, atmo_shader);
            }
        }
               
        view = save;
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayInfo **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayInfo(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, bool hdr, std::vector<Shader *> shaders, PlaneteInformation *planete_info)
{
    glm::mat4 save = view;

    float r = m_host_creator->getRadius(camPos);
    float size_plan = m_host_creator->getSizePlan();

        if(r <= 10 * size_plan)
        {
            view = lookAt(vec3(0.0, 0.0, 1.71), vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));

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
                    planete_info->renderInfo(projection, view, hdr, shaders);
                    view = save;
                }
                
            }
            
        }

        view = save;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** NOT CONCERN **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displaySkybox(RenderData &render_data)
{
    //do nothing and doesn't have
}

void PlanetarySystem::displayAsteroidField(std::vector<glm::mat4> projection_view_mat, glm::vec3 camPos, bool hdr)
{
    //do nothing and doesn't have
}

