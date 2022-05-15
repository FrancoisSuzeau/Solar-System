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
PlanetarySystem::PlanetarySystem(Renderer *planete_renderer, Renderer *ring_renderer, Renderer *sphere_renderer, std::string const system_name)
{
    m_planete_renderer = planete_renderer;
    m_ring_renderer = ring_renderer;
    m_sphere_renderer = sphere_renderer;
    m_system_name = system_name;

//     mini_speed = false;
//     maxi_speed = true;
//     current_speed = 200.0f;
}

PlanetarySystem::~PlanetarySystem()
{
    

}

/***********************************************************************************************************************************************************************/
/****************************************************************************** clean ******************************************************************************/
/***********************************************************************************************************************************************************************/
void PlanetarySystem::clean()
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

// /***********************************************************************************************************************************************************************/
// /******************************************************************************** loadSystem ***************************************************************************/
// /***********************************************************************************************************************************************************************/
void PlanetarySystem::loadSystem(int count)
{
    
    /************************************************* loading companion ********************************************************/
    if(m_system_name == "Earth System")
    {
        m_moons.push_back(new Planete(DataManager::getBodyData(2)));
        assert(m_moons[0]);

        m_host = new Planete(DataManager::getBodyData(3));
        assert(m_host);
    }
    else if(m_system_name == "Jovian System")
    {
        for (int i(6); i < 10; i++)
        {
            m_moons.push_back(new Planete(DataManager::getBodyData(i)));
            assert(m_moons[i - 6]);
        }
        
        m_host = new Planete(DataManager::getBodyData(5));
        assert(m_host);

    }
    else if(m_system_name == "Saturnian System")
    {
        for (int i(11); i < 14; i++)
        {
            m_moons.push_back(new Planete(DataManager::getBodyData(i)));
            assert(m_moons[i - 11]);
        }

        m_host = new Planete(DataManager::getBodyData(10));
        assert(m_host);
    }
    else if(m_system_name == "Uranian System")
    {
        // for (int i(11); i < 14; i++)
        // {
        //     m_moons.push_back(new Planete(DataManager::getBodyData(i)));
        //     assert(m_moons[i - 11]);
        // }

        m_host = new Planete(DataManager::getBodyData(14));
        assert(m_host);
    }
    else if(m_system_name == "Neptunian System")
    {
        // for (int i(11); i < 14; i++)
        // {
        //     m_moons.push_back(new Planete(DataManager::getBodyData(i)));
        //     assert(m_moons[i - 11]);
        // }

        m_host = new Planete(DataManager::getBodyData(15));
        assert(m_host);
    }
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
        m_host->makeOtherChanges(data_manager);
    }

    for(std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->updatePosition(it[0]->getPosition());
            it[0]->transform(-data_manager.getShipPos());
            it[0]->makeOtherChanges(data_manager);
        }
    }   
}

// /***********************************************************************************************************************************************************************/
// /*********************************************************************************** renderNameAndInfo ***************************************************************************/
// /***********************************************************************************************************************************************************************/
void PlanetarySystem::renderNameAndInfo(DataManager &data_manager)
{
    if(m_host != nullptr)
    {
        m_host->renderName(data_manager);
    }

    for(std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            it[0]->renderName(data_manager);
        }
    }  
}

// /***********************************************************************************************************************************************************************/
// /*********************************************************************************** render ***************************************************************************/
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

// /************************************************************************************************************************************************************************/
// /******************************************************************************* renderRing *****************************************************************************/
// /************************************************************************************************************************************************************************/
void PlanetarySystem::renderRing(DataManager &data_manager)
{
    if(m_host != nullptr)
    {
        if((m_ring_renderer != nullptr) && (m_host->getRing() != nullptr))
        {
            m_ring_renderer->render(data_manager, m_host->getRing());
        }
    }
}

// /************************************************************************************************************************************************************************/
// /******************************************************************************* renderAtmosphere *****************************************************************************/
// /************************************************************************************************************************************************************************/
void PlanetarySystem::renderAtmosphere(DataManager &data_manager)
{
    Sphere *atmo = nullptr;
    if(m_host != nullptr)
    {
        atmo = m_host->getAmosphere();
        if((m_sphere_renderer != nullptr) && (atmo != nullptr) && (data_manager.getPass() == COLOR_FBO))
        {
            atmo->sendToShader(data_manager);
            m_sphere_renderer->render(data_manager, atmo);
        }
    }

    for(std::vector<Planete*>::iterator it = m_moons.begin(); it != m_moons.end(); ++it)
    {
        if(it[0] != nullptr)
        {
            atmo = it[0]->getAmosphere();
            if((m_sphere_renderer != nullptr) && (atmo != nullptr) && (data_manager.getPass() == COLOR_FBO))
            {
                atmo->sendToShader(data_manager);
                m_sphere_renderer->render(data_manager, atmo);
            }
        }
    }
    atmo = nullptr;
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
void PlanetarySystem::renderFlareSun(DataManager &data_manager)
{
    //do nothing and doesn't have
}