/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : System

NAMEFILE : PlanetarySystem.cpp

PURPOSE : class PlanetarySystem
*/



#include "PlanetarySystem.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
PlanetarySystem::PlanetarySystem(/*sys_init_data data, TTF_Font *police,*/Renderer *planete_renderer, Renderer *ring_renderer, std::string const system_name)
{
    m_planete_renderer = planete_renderer;
    m_ring_renderer = ring_renderer;
    m_system_name = system_name;

    this->initDatas();

//     mini_speed = false;
//     maxi_speed = true;
//     current_speed = 200.0f;
}

PlanetarySystem::~PlanetarySystem()
{
    for(std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->clean();
            delete it[0];
            it[0] = nullptr;
        }
    }

    if(m_host != nullptr)
    {
        m_host->clean();
        delete m_host;
        m_host = nullptr;
    }

}

/***********************************************************************************************************************************************************************/
/******************************************************************************** initDatas ****************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::initDatas()
{
    std::string surface_path = "../../assets/textures/CelestialBody/";
//     std::string norma_path = "../../assets/textures/normalMap/";
//     std::string disp_paht = "../../assets/textures/displacementMap/";

    m_bodys_data.push_back({1.f, {surface_path + "MoonMap.jpg"}, "simple_textured_planete", 32, 0.f, glm::vec3(-70.f, 0.f, 0.f), "Moon"});
    m_bodys_data.push_back({3.f, {surface_path + "EarthDayMap.jpg", surface_path + "CloudMap.jpg", surface_path + "EarthNightMap.jpg"}, "earth", 128, 0.5f, glm::vec3(-80.f, 0.f, 0.f), "Earth"});

    m_bodys_data.push_back({5.f, {surface_path + "SaturnCloud.jpg"}, "simple_textured_planete", 16, 0.f, glm::vec3(100.f, 0.f, 0.f), "Saturn"});

//     m_data.push_back({{surface_path + "MoonMap.jpg"}, {norma_path + "moon_normalMap.jpg", disp_paht + "moon_dispMap.jpg"}, "Moon", "one_texture_p", 8.19f, 5.145f, 0.1f, glm::vec3(-15000, 3800, 0)});
//     m_data.push_back({{surface_path + "EarthDayMap.jpg", surface_path + "CloudMap.jpg"}, {norma_path + "earth_normalMap.jpg", disp_paht + "earth_dispMap.jpg"}, "Earth", "multi_texture_p", 30.0f, 23.26f, 0.1f, glm::vec3(-15000, 0, 0)});
//     m_data.push_back({{surface_path + "EuropaMap.jpg"}, {norma_path + "europa_normalMap.jpg", disp_paht + "europa_dispMap.jpg"}, "Europa", "one_texture_p", 7.5f, 0.469f, 0.1f, glm::vec3(77164, 0, 0)});
//     m_data.push_back({{surface_path + "GanymedeMap.jpg"}, {norma_path + "ganymede_normalMap.jpg", disp_paht + "ganymede_dispMap.jpg"}, "Ganymede", "one_texture_p", 12.39f, 0.170f, 0.1f, glm::vec3(77834, -10700, 0)});
//     m_data.push_back({{surface_path + "IoMap.jpg"}, {norma_path + "io_normalMap.jpg", disp_paht + "io_dispMap.jpg"}, "Io", "one_texture_p", 8.57f, 0.036f, 0.1f, glm::vec3(77834, 4210, 0)});
//     m_data.push_back({{surface_path + "CallistoMap.jpg"}, {norma_path + "callisto_normalMap.jpg", disp_paht + "callisto_dispMap.jpg"}, "Callisto", "one_texture_p", 11.36f, 0.187f, 0.1f, glm::vec3(77834, -18800, 0)});
//     m_data.push_back({{surface_path + "JupiterCloud.jpg"}, {norma_path + "jupiter_normalMap.jpg", disp_paht + "jupiter_dispMap.jpg"}, "Jupiter",  "one_texture_p",363.27f, 3.13f, 0.1f, glm::vec3(77834, 0, 0)});
//     m_data.push_back({{surface_path + "MimasMap.jpg"}, {norma_path + "mimas_normalMap.jpg", disp_paht + "mimas_dispMap.jpg"}, "Mimas", "one_texture_p", 1.0f, 1.53f, 0.1f, glm::vec3(2380.0, -14248, 0)});
//     m_data.push_back({{surface_path + "EnceladusMap.jpg"}, {norma_path + "enceladus_normalMap.jpg", disp_paht + "enceladus_dispMap.jpg"}, "Enceladus", "one_texture_p", 1.2f, 0.0f, 0.1f, glm::vec3(-2380, -14267, 0)});
//     m_data.push_back({{surface_path + "TitanMap.jpg"}, {norma_path + "titan_normalMap.jpg", disp_paht + "titan_dispMap.jpg"}, "Titan", "one_texture_p", 12.5f, 0.33f, 0.1f, glm::vec3(12210, -14267, 0)});
//     m_data.push_back({{surface_path + "SaturnCloud.jpg"}, {norma_path + "saturn_normalMap.jpg", disp_paht + "saturn_dispMap.jpg"}, "Saturn", "one_texture_p", 283.476f, 26.73f, 0.1f, glm::vec3(0.0, -14267, 0)});
}

// /***********************************************************************************************************************************************************************/
// /******************************************************************************** loadSystem ***************************************************************************/
// /***********************************************************************************************************************************************************************/
void PlanetarySystem::loadSystem(/*int count, TTF_Font *police*/)
{
    
    /************************************************* loading companion ********************************************************/
    if(m_system_name == "Earth System")
    {
        m_moons.push_back(new Planete(m_bodys_data[0]));
        assert(m_moons[0]);

        m_host = new Planete(m_bodys_data[1]);
        assert(m_host);
    }
//     else if(m_system_name == "Jovian System")
//     {
//         for (int i(2); i < 6; i++)
//         {
//             m_moons.push_back(new Planete(m_data[i], police));
//             assert(m_moons[i-2]);
//         }
        
//         m_host = new Planete(m_data[6], police);
//         assert(m_host);

//     }
    else if(m_system_name == "Saturnian System")
    {
        // for (int i(7); i < 10; i++)
        // {
        //     m_moons.push_back(new Planete(m_data[i], police));
        //     assert(m_moons[i-7]);
        // }

        m_host = new Planete(m_bodys_data[2]);
        assert(m_host);
    }
//     else
//     {
//         std::cout << ">> Loading planetary System : no name match found" << std::endl;
//     }
//     //===================================================================================================================
}

// /***********************************************************************************************************************************************************************/
// /****************************************************************************** makeChanges ****************************************************************************/
// /***********************************************************************************************************************************************************************/
void PlanetarySystem::makeChanges(DataManager &data_manager)
{
    if(m_host != nullptr)
    {
        m_host->updatePosition(m_host->getPosition());
        m_host->transform(-data_manager.getShipPos());

        m_host->makeRingChanges(data_manager);
    }

    for(std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->updatePosition(it[0]->getPosition());
            it[0]->transform(-data_manager.getShipPos());
        }
    }
    
}

// /***********************************************************************************************************************************************************************/
// /*********************************************************************************** display ***************************************************************************/
// /***********************************************************************************************************************************************************************/
void PlanetarySystem::render(DataManager &data_manager)
{
    for(std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
    {
        if((m_planete_renderer != nullptr) && (it[0] != nullptr))
        {
            m_planete_renderer->render(data_manager, it[0]);
        }
    }

    if((m_planete_renderer != nullptr) && (m_host != nullptr))
    {
        m_planete_renderer->render(data_manager, m_host);
    }
}

// /***********************************************************************************************************************************************************************/
// /******************************************************************************** displayName **************************************************************************/
// /***********************************************************************************************************************************************************************/
// void PlanetarySystem::displayName(RenderData &render_data)
// {
//     render_data.initSaveMat();

//     if(m_host->getProximity())
//     {
//         for (std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
//         {
//             if(it[0] != nullptr)
//             {
//                 if(render_data.getShader("text") != nullptr)
//                 {
//                     planete_render->displayName(render_data, 10, it[0]);
//                     render_data.saveViewMat();
//                 }
//             }

//             render_data.saveViewMat();
//         }

//         render_data.saveViewMat();
//     }
    
//     if(m_host != nullptr)
//     {
//         if(render_data.getShader("text") != nullptr)
//         {
//             planete_render->displayName(render_data, 30, m_host);
//             render_data.saveViewMat();
//         }
//     }

    
    

    

//     render_data.saveViewMat();
// }

// /***********************************************************************************************************************************************************************/
// /******************************************************************************** displayAtmo **************************************************************************/
// /***********************************************************************************************************************************************************************/
// void PlanetarySystem::displayAtmo(RenderData &render_data)
// {
//     render_data.initSaveMat();

//     if(m_host != nullptr)
//     {
//         if((m_host->getAtmosphere() != nullptr) && (render_data.getShader("atmosphere") != nullptr))
//         {
//             planete_render->displayAtmo(render_data, m_host);
//         }
//     }

//     render_data.saveViewMat();
    
// }

// /***********************************************************************************************************************************************************************/
// /******************************************************************************** renderInfos **************************************************************************/
// /***********************************************************************************************************************************************************************/
// void PlanetarySystem::renderInfos(RenderData &render_data, PlaneteInformation *planete_info)
// {
//     this->displayInfo(render_data, m_host, planete_info);

//     for(std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
//     {
//         this->displayInfo(render_data, it[0], planete_info);
//     }
// }

// /***********************************************************************************************************************************************************************/
// /******************************************************************************** displayInfos *************************************************************************/
// /***********************************************************************************************************************************************************************/
// void PlanetarySystem::displayInfo(RenderData &render_data, Planete *planete, PlaneteInformation *planete_info)
// {
//     if(planete != nullptr)
//     {
//         float r = planete->getRadiusFromCam(render_data.getShipPos());
//         float size_plan = planete->getSize();

//             if(r <= 10 * size_plan)
//             {
                
//                 if(planete_info != nullptr)
//                 {
//                     std::string tmp_name = planete->getName();
//                     planete_info->renderInfo(render_data, tmp_name);
//                 }
                
//             }
//     }
// }

// /************************************************************************************************************************************************************************/
// /******************************************************************************* renderRing *****************************************************************************/
// /************************************************************************************************************************************************************************/
void PlanetarySystem::renderRing(DataManager &data_manager)
{
    if((m_ring_renderer != nullptr) && (m_host->getRing() != nullptr))
    {
        m_ring_renderer->render(data_manager, m_host->getRing());
    }
}

// /************************************************************************************************************************************************************************/
// /********************************************************************** setMostGravInfluence ****************************************************************************/
// /************************************************************************************************************************************************************************/
// void PlanetarySystem::setMostGravInfluence(RenderData &render_data)
// {
//     if(m_host != nullptr)
//     {
//         std::vector<float> r = {m_host->getRadiusFromCam(render_data.getShipPos())};
//         float size_plan = m_host->getSize();

//         if(r[0] <= 30 * size_plan)
//         {
//             std::string tmp_name = m_host->getName();

//             for(std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
//             {
//                 r.push_back(it[0]->getRadiusFromCam(render_data.getShipPos()));
//             }

//             std::vector<double> grav_inf = Physique::getGravInfluence(tmp_name, r);

//             render_data.setInfName(tmp_name);
//             render_data.setInfVal(grav_inf);
//         }
//     }
// }

// /************************************************************************************************************************************************************************/
// /*************************************************************************** approchBody ********************************************************************************/
// /************************************************************************************************************************************************************************/
// void PlanetarySystem::approchBody(Spaceship *ship)
// {
//     std::string tmp = "none";

//     float r = m_host->getRadiusFromCam(ship->getPosition());
//     float size_plan = m_host->getSize();
//     if(r < 50 * size_plan)
//     {
//         tmp = m_host->getName();
//     }

//     if(tmp != "none")
//     {
//         if(mini_speed == false)
//         {
//             current_speed = ship->getSpeed();
//             ship->setMinimumSpeed();
//             mini_speed = true;
//             maxi_speed = false;
//         }
//     }
//     else
//     {
//         if(maxi_speed == false)
//         {
//             ship->updateSpeed(current_speed);
//             maxi_speed = true;
//             mini_speed = false;
//         }
//     }
// }

// /***********************************************************************************************************************************************************************/
// /******************************************************************************** NOT CONCERN **************************************************************************/
// /***********************************************************************************************************************************************************************/

// void PlanetarySystem::renderFlareSun(RenderData &render_data)
// {
//     //do nothing and doesn't have
// }