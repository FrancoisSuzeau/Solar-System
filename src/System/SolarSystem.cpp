/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : System

NAMEFILE : SolarSystem.cpp

PURPOSE : class SolarSystem
*/

#include "SolarSystem.hpp"


/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
SolarSystem::SolarSystem(/*sys_init_data data, TTF_Font *police*/Renderer *planete_renderer)
{
    m_sun = new Star(1.f, "../../assets/textures/CelestialBody/SunMap.jpg", "sun");
    assert(m_sun);
    m_sun->updateSize(glm::vec3(10.f));

    m_star_renderer = new StarRenderer(1.f, 70.f, 70.f);
    assert(m_star_renderer);

    m_planete_renderer = planete_renderer;

    m_asteroid_field = new AsteroidField("INSTmodel");
    assert(m_asteroid_field);

    this->initDatas();

    // m_planete_info = new PlaneteInformation();
    // assert(m_planete_info);

    // m_system_name = data.name_sys;
    // m_companion_count = data.companion_count;
    // m_planetarySYS_count = 3;
    // m_simple_planete_count = 5;

    // mini_speed = false;
    // maxi_speed = true;
    // current_speed = 200.0f;
}

SolarSystem::~SolarSystem()
{

    // for (std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
    // {
    //     if(*it != nullptr)
    //     {
    //         delete *it;
    //     }
        
    // }

    // for(std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
    // {
    //     if(*it != nullptr)
    //     {
    //         delete *it;
    //     }
    // }
    
    if(m_sun != nullptr)
    {
        m_sun->clean();
        delete m_sun;
        m_sun = nullptr;
    }
    if(m_star_renderer != nullptr)
    {
        m_star_renderer->clean();
        delete m_star_renderer;
        m_star_renderer = nullptr;
    }

    if(m_asteroid_field != nullptr)
    {
        m_asteroid_field->clean();
        delete m_asteroid_field;
        m_asteroid_field = nullptr;
    }

    for(std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->clean();
            delete it[0];
            it[0] = nullptr;
        }
    }

    for(std::vector<SystemCreator*>::iterator it = m_planetary_systems.begin(); it != m_planetary_systems.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            delete it[0];
            it[0] = nullptr;
        }
    }

    // if(m_planete_info != nullptr)
    // {
    //     delete m_planete_info;
    // }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** initDatas ****************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::initDatas()
{
    std::string surface_path = "../../assets/textures/CelestialBody/";
//     std::string norma_path = "../../assets/textures/normalMap/";
//     std::string disp_paht = "../../assets/textures/displacementMap/";

    m_bodys_data.push_back({1.f, {surface_path + "MercuryMap.jpg"}, "simple_textured_planete", 32, 0.f});

//     m_data.push_back({{surface_path + "MercuryMap.jpg"}, {norma_path + "mercury_normalMap.jpg", disp_paht + "mercury_dispMap.jpg"}, "Mercury", "one_texture_p", 11.49f, 0.01f, 0.1f, glm::vec3(5790.0f, 0.0f, 0.0f)});
//     m_data.push_back({{surface_path + "VenusMap.jpg", surface_path + "VenusCloud.jpg"}, {norma_path + "venus_normalMap.jpg", disp_paht + "venus_dispMap.jpg"}, "Venus", "multi_texture_p", 28.47f, 177.3f, 0.1f, glm::vec3(0.0f, -10820.0f, 0.0f)});
//     m_data.push_back({{surface_path + "MarsMap.jpg", surface_path + "MarsCloud.png"}, {norma_path + "mars_normalMap.jpg", disp_paht + "mars_dispMap.jpg"}, "Mars", "multi_texture_p", 15.99f, 25.19f, 0.1f, glm::vec3(0, 22790, 0)});
//     m_data.push_back({{surface_path + "UranusCloud.jpg"}, {norma_path + "uranus_normalMap.jpg", disp_paht + "uranus_dispMap.jpg"}, "Uranus", "one_texture_p", 120.21f, 97.77f, 0.1f, glm::vec3(-28707.0f, 0.0f, 0.0f)});
//     m_data.push_back({{surface_path + "NeptuneCloud.jpg"}, {norma_path + "neptune_normalMap.jpg", disp_paht + "neptune_dispMap.jpg"}, "Neptune", "one_texture_p", 116.49f, 26.32f, 0.1f, glm::vec3(0.0f, 44984.0f, 0.0f)});

//     sys_data.push_back({"Earth System", 1});
//     sys_data.push_back({"Jovian System", 4});
//     sys_data.push_back({"Saturnian System", 3});
}

// /***********************************************************************************************************************************************************************/
// /******************************************************************************* loadSystem ****************************************************************************/
// /***********************************************************************************************************************************************************************/
void SolarSystem::loadSystem(/*int count, TTF_Font *police*/)
{
    m_planetes.push_back(new Planete(m_bodys_data[0].size, m_bodys_data[0].textures_path, m_bodys_data[0].type, m_bodys_data[0].shininess, m_bodys_data[0].oppacity));
    assert(m_planetes[0]);

    m_planetary_systems.push_back(new PlanetarySystemCreator());
    assert(m_planetary_systems[0]);
    assert(m_planetary_systems[0]->MakingSystem(m_planete_renderer));
    m_planetary_systems[0]->loadSystem();

//     assert(police);
//     /************************************************* loading planetary system ********************************************************/
//     // Earth System
//     if(count == 1)
//     {
//         m_planetary_system.push_back(new PlanetarySystemCreator());
//         assert(m_planetary_system[0]);
//         assert(m_planetary_system[0]->MakingSystem(sys_data[0], police));
//         m_planetary_system[0]->loadSystem(count, police);
//     }
//     // Jovian System
//     if(count == 2)
//     {
//         m_planetary_system.push_back(new PlanetarySystemCreator());
//         assert(m_planetary_system[1]);
//         assert(m_planetary_system[1]->MakingSystem(sys_data[1], police));
//         m_planetary_system[1]->loadSystem(count, police);
//     }

//     //Saturian System
//     if(count == 3)
//     {
//         m_planetary_system.push_back(new PlanetarySystemCreator());
//         assert(m_planetary_system[2]);
//         assert(m_planetary_system[2]->MakingSystem(sys_data[2], police));
//         m_planetary_system[2]->loadSystem(count, police);
//     }  
//     //===================================================================================================================

//     /************************************************* loading planete ********************************************************/

//     if(count == 4)
//     {
//         m_planetes.push_back(new Planete(m_data[0], police));
//         assert(m_planetes[0]);
//     }
    
//     if(count == 5)
//     {
//         m_planetes.push_back(new Planete(m_data[1], police));
//         assert(m_planetes[1]);
//     }

//     if(count == 6)
//     {
//         m_planetes.push_back(new Planete(m_data[2], police));
//         assert(m_planetes[2]);
//     }

//     if(count == 7)
//     {
//         m_planetes.push_back(new Planete(m_data[3], police));
//         assert(m_planetes[3]);
//     }
//     if(count == 8)
//     {
//         m_planetes.push_back(new Planete(m_data[4], police));
//         assert(m_planetes[4]);
//     }
//     //===================================================================================================================   
}

// /***********************************************************************************************************************************************************************/
// /****************************************************************************** makeChanges ****************************************************************************/
// /***********************************************************************************************************************************************************************/
void SolarSystem::makeChanges(DataManager &data_manager)
{
    if(m_sun != nullptr)
    {
        m_sun->updatePosition(glm::vec3(0.f, 0.f, 0.f));
        m_sun->transform(-data_manager.getShipPos());
    }

    if(m_asteroid_field != nullptr)
    {
        m_asteroid_field->transform(-data_manager.getShipPos());
        m_asteroid_field->sendToShader(data_manager);
    }

    if(m_planetes[0] != nullptr)
    {
        m_planetes[0]->updatePosition(glm::vec3(20.f, 0.f, 1.5f));
        m_planetes[0]->transform(-data_manager.getShipPos());
    }

    for(std::vector<SystemCreator*>::iterator it = m_planetary_systems.begin(); it != m_planetary_systems.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->makeChanges(data_manager);
        }
    }
}

// /***********************************************************************************************************************************************************************/
// /*********************************************************************************** render ****************************************************************************/
// /***********************************************************************************************************************************************************************/
void SolarSystem::render(DataManager &data_manager)
{
    /************************************************* SUN RENDER ********************************************************/
    if((m_sun != nullptr) && (m_star_renderer != nullptr) && (data_manager.getPass() == COLOR_FBO))
    {
        m_star_renderer->render(data_manager, m_sun);
    }

    if((m_asteroid_field != nullptr) && (data_manager.getPass() == COLOR_FBO))
    {
        m_asteroid_field->render(data_manager);
    }

    for(std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
    {
        if((m_planete_renderer != nullptr) && (it[0] != nullptr))
        {
            m_planete_renderer->render(data_manager, it[0]);
        }
    }

    for(std::vector<SystemCreator*>::iterator it = m_planetary_systems.begin(); it != m_planetary_systems.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->render(data_manager);
        }
    }

//     for (std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
//     {
//         if(it[0] != nullptr)
//         {
//             it[0]->updatePosition(render_data.getShipPos());

//             if((render_data.getShader("one_texture_p") != nullptr) && (render_data.getShader("multi_texture_p")))
//             {
//                 planete_render->display(render_data, it[0]);
                
//                 render_data.saveViewMat();
//             }
//         }

//         render_data.saveViewMat();
//     }
        
//     /************************************************* PLANETARY SYSTEM RENDER ********************************************************/
//     render_data.saveViewMat();

//     for (std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
//     {

//         if(it[0] != nullptr)
//         {
//             if( (render_data.getShader("multi_texture_p") != nullptr) && (render_data.getShader("one_texture_p") != nullptr))
//             {
//                 it[0]->drawSystem(render_data);
//                 render_data.saveViewMat();
//             }
//         }

//         render_data.saveViewMat();
//     }

//     //restaure the view matrix
//     render_data.saveViewMat();
}

// /***********************************************************************************************************************************************************************/
// /******************************************************************************** displayName **************************************************************************/
// /***********************************************************************************************************************************************************************/
// void SolarSystem::displayName(RenderData &render_data)
// {
    
//     render_data.initSaveMat();


//     for (std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
//     {
//         if(it[0] != nullptr)
//         {
//             if(render_data.getShader("text") != nullptr)
//             {
//                 it[0]->drawName(render_data);
//                 render_data.saveViewMat();
//             }
//         }

//         render_data.saveViewMat();
//     }

//     render_data.saveViewMat();

//     for (std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
//     {
//        if(it[0] != nullptr)
//        {
//            if(render_data.getShader("text") != nullptr)
//             {
//                 planete_render->displayName(render_data, 30, it[0]);
//                 render_data.saveViewMat();
//             }
//        }

//         render_data.saveViewMat();
//     }

//     render_data.saveViewMat();

// }

// /***********************************************************************************************************************************************************************/
// /******************************************************************************** displayAtmo **************************************************************************/
// /***********************************************************************************************************************************************************************/
// void SolarSystem::displayAtmo(RenderData &render_data)
// {
//     render_data.initSaveMat();

//     /************************************************* OTHER ATMO RENDER ********************************************************/

//     for(std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
//     {
//         if(it[0] != nullptr)
//         {
//             if(render_data.getShader("atmosphere") != nullptr)
//             {
//                 it[0]->drawAtmo(render_data);

//                 render_data.saveViewMat();
//             }
            
//         }
        
//         render_data.saveViewMat();
//     }

//     render_data.saveViewMat();

//     for(std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
//     {
//         if((render_data.getShader("atmosphere") != nullptr) && (it[0] != nullptr))
//         {
//             planete_render->displayAtmo(render_data, it[0]);

//             render_data.saveViewMat();
//         }

//         render_data.saveViewMat();
//     }

//     render_data.saveViewMat();
// }

// /***********************************************************************************************************************************************************************/
// /******************************************************************************** displayInfo **************************************************************************/
// /***********************************************************************************************************************************************************************/
// void SolarSystem::renderInfos(RenderData &render_data, PlaneteInformation *plan_info)
// {
//     for(std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
//     {

//         if( (it[0] != nullptr) && (m_planete_info != nullptr))
//         {
//             float r = it[0]->getRadiusFromCam(render_data.getShipPos());
//             float size_plan = it[0]->getSize();

//             if(r <= 10 * size_plan)
//             {
               
//                 std::string tmp_name = it[0]->getName();

//                 m_planete_info->renderInfo(render_data, tmp_name);
//             }
//         }
//     }

//     // display information of planetof the planetary system
//     for (std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
//     {
//         if(it[0] != nullptr)
//         {
//             it[0]->drawInfo(render_data, m_planete_info);
//         }
        
//     }
    
// }

// /************************************************************************************************************************************************************************/
// /******************************************************************************* displayRing ****************************************************************************/
// /************************************************************************************************************************************************************************/
// void SolarSystem::displayRing(RenderData &render_data)
// {
//     render_data.initSaveMat();
    
//     for(std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
//     {
//         if( (render_data.getShader("ring") != nullptr) && (it[0] != nullptr) )
//         {
//             planete_render->renderRing(render_data, it[0]);
//         }
//     }

//     render_data.saveViewMat();

//     for(std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
//     {
//         if(it[0] != nullptr)
//         {
//             it[0]->drawRing(render_data);
//         }
//     }
// }

// /************************************************************************************************************************************************************************/
// /********************************************************************** setMostGravInfluence ****************************************************************************/
// /************************************************************************************************************************************************************************/
// void SolarSystem::setMostGravInfluence(RenderData &render_data)
// {
//     for(std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
//     {
//         if(it[0] != nullptr)
//         {
//             std::vector<float> r = {it[0]->getRadiusFromCam(render_data.getShipPos())};
//             float size_plan = it[0]->getSize();


//             if(r[0] <= 30 * size_plan)
//             {
//                 std::string tmp_name = it[0]->getName();
//                 std::vector<double> grav_inf = Physique::getGravInfluence(tmp_name, r);

//                 render_data.setInfName(tmp_name);
//                 render_data.setInfVal(grav_inf);

//             }
//         }
//     }

//     for (std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
//     {
//         if(it[0] != nullptr)
//         {
//             it[0]->setMostGravInfluence(render_data);
//         }
//     }
// }

// /************************************************************************************************************************************************************************/
// /*************************************************************************** approchBody ********************************************************************************/
// /************************************************************************************************************************************************************************/
// void SolarSystem::approchBody(Spaceship *ship)
// {
//     std::string tmp = "none";

//     for(std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
//     {
//         float r = it[0]->getRadiusFromCam(ship->getPosition());
//         float size_plan = it[0]->getSize();

//         if(r <= 50 * size_plan)
//         {
//             tmp = it[0]->getName();
//         }
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

//      for (std::vector<SystemCreator*>::iterator it = m_planetary_system.begin(); it != m_planetary_system.end(); ++it)
//     {
//         if(it[0] != nullptr)
//         {
//             it[0]->approchBody(ship);
//         }
//     }
// }

// /************************************************************************************************************************************************************************/
// /*************************************************************************** renderFlareSun *****************************************************************************/
// /************************************************************************************************************************************************************************/
// void SolarSystem::renderFlareSun(RenderData &render_data)
// {
//     fm.renderLensFlare(render_data);

//     if(sun != nullptr)
//     {
//         sun->renderFlare(render_data);
//     }
// }