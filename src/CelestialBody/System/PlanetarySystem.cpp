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

    planete_render = new PlaneteRender();
    assert(planete_render);

    this->initData();
}

PlanetarySystem::PlanetarySystem()
{
    
}

PlanetarySystem::~PlanetarySystem()
{
    if(planete_render != nullptr)
    {
        delete planete_render;
    }

    for(std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
    {
        if(*it != nullptr)
        {
            delete *it;
        }
    }

    if(m_host != nullptr)
    {
        delete m_host;
    }

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** initData *****************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::initData()
{
    m_data.push_back({{"../assets/textures/CelestialBody/MoonMap.jpg"}, "../assets/textures/normalMap/moon_normalMap.jpg", "Moon", "one_texture_p", 8.19f, 5.145f, 0.1f, glm::vec3(-15000, 3800, 0)});
    m_data.push_back({{"../assets/textures/CelestialBody/EarthDayMap.jpg", "../assets/textures/CelestialBody/CloudMap.jpg"}, "../assets/textures/normalMap/earth_normalMap.jpg", "Earth", "multi_texture_p", 30.0f, 23.26f, 0.1f, glm::vec3(-15000, 0, 0)});
    m_data.push_back({{"../assets/textures/CelestialBody/EuropaMap.jpg"}, "../assets/textures/normalMap/europa_normalMap.jpg", "Europa", "one_texture_p", 7.5f, 0.469f, 0.1f, glm::vec3(77164, 0, 0)});
    m_data.push_back({{"../assets/textures/CelestialBody/GanymedeMap.jpg"}, "../assets/textures/normalMap/ganymede_normalMap.jpg", "Ganymede", "one_texture_p", 12.39f, 0.170f, 0.1f, glm::vec3(77834, -10700, 0)});
    m_data.push_back({{"../assets/textures/CelestialBody/IoMap.jpg"}, "../assets/textures/normalMap/io_normalMap.jpg", "Io", "one_texture_p", 8.57f, 0.036f, 0.1f, glm::vec3(77834, 4210, 0)});
    m_data.push_back({{"../assets/textures/CelestialBody/CallistoMap.jpg"}, "../assets/textures/normalMap/callisto_normalMap.jpg", "Callisto", "one_texture_p", 11.36f, 0.187f, 0.1f, glm::vec3(77834, -18800, 0)});
    m_data.push_back({{"../assets/textures/CelestialBody/JupiterCloud.jpg"}, "../assets/textures/normalMap/jupiter_normalMap.jpg", "Jupiter",  "one_texture_p",363.27f, 3.13f, 0.1f, glm::vec3(77834, 0, 0)});
    m_data.push_back({{"../assets/textures/CelestialBody/MimasMap.jpg"}, "../assets/textures/normalMap/mimas_normalMap.jpg", "Mimas", "one_texture_p", 1.0f, 1.53f, 0.1f, glm::vec3(2380.0, -14248, 0)});
    m_data.push_back({{"../assets/textures/CelestialBody/EnceladusMap.jpg"}, "../assets/textures/normalMap/enceladus_normalMap.jpg", "Enceladus", "one_texture_p", 1.2f, 0.0f, 0.1f, glm::vec3(-2380, -14267, 0)});
    m_data.push_back({{"../assets/textures/CelestialBody/TitanMap.jpg"}, "../assets/textures/normalMap/titan_normalMap.jpg", "Titan", "one_texture_p", 12.5f, 0.33f, 0.1f, glm::vec3(12210, -14267, 0)});
    m_data.push_back({{"../assets/textures/CelestialBody/SaturnCloud.jpg"}, "../assets/textures/normalMap/saturn_normalMap.jpg", "Saturn", "one_texture_p", 283.476f, 26.73f, 0.1f, glm::vec3(0.0, -14267, 0)});
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** loadSystem ***************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::loadSystem(int count, TTF_Font *police)
{
    /************************************************* loading companion ********************************************************/
    if(m_system_name == "Earth System")
    {
        m_moons.push_back(new Planete(m_data[0], police));
        assert(m_moons[0]);

        m_host = new Planete(m_data[1], police);
        assert(m_host);
    }
    else if(m_system_name == "Jovian System")
    {
        for (int i(2); i < 6; i++)
        {
            m_moons.push_back(new Planete(m_data[i], police));
            assert(m_moons[i-2]);
        }
        
        m_host = new Planete(m_data[6], police);
        assert(m_host);

    }
    else if(m_system_name == "Saturnian System")
    {
        for (int i(7); i < 10; i++)
        {
            m_moons.push_back(new Planete(m_data[i], police));
            assert(m_moons[i-7]);
        }

        m_host = new Planete(m_data[10], police);
        assert(m_host);
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
void PlanetarySystem::display(RenderData &render_data)
{
    render_data.initSaveMat();

    std::cout << m_host->getName() << " : " << m_moons.size() << std::endl;

    for (std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
    {
        if((it[0] != nullptr) && (planete_render != nullptr))
        {
            it[0]->updatePosition();

            if(render_data.getShader("one_texture_p") != nullptr)
            {
                planete_render->display(render_data, it[0]);

                std::cout << m_host->getName() << " : " << m_moons.size() << std::endl;
                
                render_data.saveViewMat();
            }
        }
        render_data.saveViewMat();
    }

    render_data.saveViewMat();

    if((m_host != nullptr) && (planete_render != nullptr))
    {
        m_host->updatePosition();

        if((render_data.getShader("one_texture_p") != nullptr) && (render_data.getShader("multi_texture_p") != nullptr))
        {
            planete_render->display(render_data, m_host);
        }
    }
    
    render_data.saveViewMat();

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayName **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayName(RenderData &render_data)
{
    render_data.initSaveMat();

    for (std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
    {
       if(it[0] != nullptr)
       {
           if(render_data.getShader("text") != nullptr)
            {
                planete_render->displayName(render_data, 400, it[0]);
                render_data.saveViewMat();
            }
       }

        render_data.saveViewMat();
    }
    render_data.saveViewMat();

    if(m_host != nullptr)
    {
        if(render_data.getShader("text") != nullptr)
        {
            planete_render->displayName(render_data, 400, m_host);
            render_data.saveViewMat();
        }
    }

    render_data.saveViewMat();
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayAtmo **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayAtmo(RenderData &render_data)
{
    render_data.initSaveMat();

    if(m_host != nullptr)
    {
        if((m_host->getAtmosphere() != nullptr) && (render_data.getShader("atmosphere") != nullptr))
        {
            planete_render->displayAtmo(render_data, m_host);
        }
    }

    render_data.saveViewMat();
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** renderInfos **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::renderInfos(RenderData &render_data, PlaneteInformation *planete_info)
{
    glm::mat4 save = render_data.getViewMat();

    this->displayInfo(render_data, m_host, planete_info);

    for(std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
    {
        this->displayInfo(render_data, it[0], planete_info);
    }

    render_data.updateView(save);
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayInfos *************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayInfo(RenderData &render_data, Planete *planete, PlaneteInformation *planete_info)
{
    glm::mat4 save = render_data.getViewMat();

    if(planete != nullptr)
    {
        float r = planete->getRadiusFromCam(render_data.getCamPos());
        float size_plan = planete->getSize();

            if(r <= 10 * size_plan)
            {
                render_data.lockViewMat(glm::vec3(0.0, 0.0, 1.71), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

                std::string tmp_name = planete->getName();
                
                if(planete_info != nullptr)
                {
                    if(tmp_name != planete_info->getInfoName())
                    {
                        planete_info->changeNamePlan(tmp_name);
                    }

                    if((render_data.getShader("text") != nullptr) && (render_data.getShader("square") != nullptr))
                    {
                        planete_info->renderInfo(render_data);
                        render_data.updateView(save);
                    }
                }
                
            }
    }
    
    render_data.updateView(save);
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** displayRing **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displayRing(RenderData &render_data)
{
    render_data.initSaveMat();
    
    if( (render_data.getShader("ring") != nullptr) && (m_host != nullptr) )
    {
        planete_render->renderRing(render_data, m_host);
    }

    render_data.saveViewMat();
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** NOT CONCERN **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::displaySkybox(RenderData &render_data)
{
    //do nothing and doesn't have
}

void PlanetarySystem::displayAsteroidField(RenderData &render_data)
{
    //do nothing and doesn't have
}

