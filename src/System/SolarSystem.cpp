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
SolarSystem::SolarSystem(/*sys_init_data data, TTF_Font *police*/Renderer *planete_renderer, Renderer *ring_renderer, std::string const system_name)
{
    m_sun = new Star(1.f, "../../assets/textures/CelestialBody/SunMap.jpg", "sun");
    assert(m_sun);
    m_sun->updateSize(glm::vec3(10.f));

    m_star_renderer = new StarRenderer(1.f, 70.f, 70.f);
    assert(m_star_renderer);

    m_planete_renderer = planete_renderer;
    m_ring_renderer = ring_renderer;

    m_asteroid_field = new AsteroidField("INSTmodel");
    assert(m_asteroid_field);

    // this->initDatas();

    // m_planete_info = new PlaneteInformation();
    // assert(m_planete_info);

    // mini_speed = false;
    // maxi_speed = true;
    // current_speed = 200.0f;
}

SolarSystem::~SolarSystem()
{   
    

    // if(m_planete_info != nullptr)
    // {
    //     delete m_planete_info;
    // }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** clean ******************************************************************************/
/***********************************************************************************************************************************************************************/
void SolarSystem::clean()
{
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
            it[0]->cleanSystem();
            delete it[0];
            it[0] = nullptr;
        }
    }
}

// /***********************************************************************************************************************************************************************/
// /******************************************************************************* loadSystem ****************************************************************************/
// /***********************************************************************************************************************************************************************/
void SolarSystem::loadSystem(int count)
{
    if(count == 0)
    {
        m_planetes.push_back(new Planete(DataManager::getBodyData(0)));
        assert(m_planetes[0]);
    }
    else if(count == 1)
    {
        m_planetes.push_back(new Planete(DataManager::getBodyData(1)));
        assert(m_planetes[1]);
    }
    else if(count == 2)
    {
        m_planetary_systems.push_back(new PlanetarySystemCreator());
        assert(m_planetary_systems[0]);
        assert(m_planetary_systems[0]->MakingSystem(m_planete_renderer, m_ring_renderer, "Earth System"));
        m_planetary_systems[0]->loadSystem();
    }
    else if(count == 3)
    {
        m_planetes.push_back(new Planete(DataManager::getBodyData(4)));
        assert(m_planetes[2]);
    }
    else if(count == 4)
    {
        m_planetary_systems.push_back(new PlanetarySystemCreator());
        assert(m_planetary_systems[1]);
        assert(m_planetary_systems[1]->MakingSystem(m_planete_renderer, m_ring_renderer, "Jovian System"));
        m_planetary_systems[1]->loadSystem();
    }
    else if(count == 5)
    {
        m_planetary_systems.push_back(new PlanetarySystemCreator());
        assert(m_planetary_systems[2]);
        assert(m_planetary_systems[2]->MakingSystem(m_planete_renderer, m_ring_renderer, "Saturnian System"));
        m_planetary_systems[2]->loadSystem();
    }
    else if(count == 6)
    {
        m_planetes.push_back(new Planete(DataManager::getBodyData(14)));
        assert(m_planetes[3]);
    }
    else if(count == 7)
    {
        m_planetes.push_back(new Planete(DataManager::getBodyData(15)));
        assert(m_planetes[4]);
    }
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
    

    for(std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->updatePosition(it[0]->getPosition());
            it[0]->transform(-data_manager.getShipPos());
            it[0]->makeRingChanges(data_manager);
        }
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
// /*********************************************************************************** renderNameAndInfo ***************************************************************************/
// /***********************************************************************************************************************************************************************/
void SolarSystem::renderNameAndInfo(DataManager &data_manager)
{
    for(std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->renderName(data_manager);
        }
    }

    for(std::vector<SystemCreator*>::iterator it = m_planetary_systems.begin(); it != m_planetary_systems.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->renderNameAndInfo(data_manager);
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
// /******************************************************************************* renderRing *****************************************************************************/
// /************************************************************************************************************************************************************************/
void SolarSystem::renderRing(DataManager &data_manager)
{
    for(std::vector<Planete*>::iterator it = m_planetes.begin(); it != m_planetes.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            if((m_ring_renderer != nullptr) && (it[0]->getRing() != nullptr))
            {
                m_ring_renderer->render(data_manager, it[0]->getRing());
            }
        }
    }
    for(std::vector<SystemCreator*>::iterator it = m_planetary_systems.begin(); it != m_planetary_systems.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->renderRing(data_manager);
        }
    }
}

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