/*
AUTHOR : SUZEAU François

DATE : 26/05/2021

MODULE : Application

NAMEFILE : Application.hpp

PURPOSE :   - creating OpenGL Context
            - Intialise all object of the scene
            - manage event and interaction
*/

#include "Application.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Application::Application(int width, int height, SDL_Window *window): m_data_manager(width, height, 45.0),
m_window(window), 
m_setting(), m_overlay(), m_audio(nullptr), m_input(nullptr), camera(nullptr), m_skybox(nullptr), ship(nullptr)
{
    render_menu = false;
    menu_app_key_pressed = false;

    if(m_input == nullptr)
    {
        m_input = new Input();
        assert(m_input);
    }

    if(m_audio == nullptr)
    {
        m_audio = new Audio();
        assert(m_audio);
    }
}

Application::~Application()
{

}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** cleanAll **********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::cleanAll()
{
    if(m_skybox != nullptr)
    {
        m_skybox->clean();
        delete m_skybox;
        m_skybox = nullptr;
    }
    if(camera != nullptr)
    {
        delete camera;
        camera = nullptr;
    }
    if(ship != nullptr)
    {
        ship->clean();
        delete ship;
        ship = nullptr;
    }
    if(m_input != nullptr)
    {
        delete m_input;
        m_input = nullptr;
    }
    if(m_audio != nullptr)
    {
        m_audio->clean();
        delete m_audio;
        m_audio = nullptr;
    }

    m_setting.clean();
    m_overlay.clean();

    if(sun != nullptr)
    {
        sun->clean();
        delete sun;
    }
    if(star_renderer != nullptr)
    {
        star_renderer->clean();
        delete star_renderer;
    }

    if(mercury != nullptr)
    {
        mercury->clean();
        delete mercury;
    }
    if(earth != nullptr)
    {
        earth->clean();
        delete earth;
    }
    if(planete_renderer != nullptr)
    {
        planete_renderer->clean();
        delete planete_renderer;
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* initFrameBuffer *********************************************************************/
/***********************************************************************************************************************************************************************/
// void Application::initFrameBuffer()
// {
//     assert(m_framebuffer->initFramebuffer(m_window_width, m_window_height));
// }

/***********************************************************************************************************************************************************************/
/*************************************************************************************** loadConfig ********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::loadConfig()
{
    m_data_manager.setFps(60);
    m_data_manager.setPause(false);
    m_data_manager.setTerminate(false);
    m_data_manager.setVolume(64);
    m_data_manager.setTrack(0);
    m_data_manager.setShader(true);

    frame_rate = 1000 / m_data_manager.getFps();
    start_loop = 0;
    end_loop = 0;
    time_past = 0;

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** startLoop *********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::loadAssets()
{
    Renderer *square_renderer = new SquareRenderer(1.0);
    assert(square_renderer);
    Square  *square = new Square(1.0, "square");
    assert(square);

    m_overlay.initOverlayAssets(square_renderer, square);
    m_skybox = new Skybox();
    assert(m_skybox);
    ship = new Spaceship("model");
    assert(ship);
    ship->loadModelShip(m_data_manager);
    
    camera = new Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), ship);
    assert(camera);

    std::vector<std::string> surface_paths;
    surface_paths.push_back("../../assets/textures/CelestialBody/SunMap.jpg");
    sun = new Star(1.f, surface_paths[0], "sun");
    assert(sun);
    sun->updateSize(glm::vec3(10.f));

    star_renderer = new StarRenderer(1.f, 70.f, 70.f);
    assert(star_renderer);

    surface_paths.clear();
    surface_paths.push_back("../../assets/textures/CelestialBody/MercuryMap.jpg");
    mercury = new Planete(1.f, surface_paths, "simple_textured_planete", 32);
    assert(mercury);
    mercury->updateSize(glm::vec3(1.f));

    surface_paths.clear();
    surface_paths.push_back("../../assets/textures/CelestialBody/EarthDayMap.jpg");
    surface_paths.push_back("../../assets/textures/CelestialBody/CloudMap.jpg");
    earth = new Planete(1.f, surface_paths, "double_textured_planete", 128, 0.3f);
    assert(earth);
    earth->updateSize(glm::vec3(3.f));

    planete_renderer = new PlaneteRenderer(1.f, 70.f, 70.f);
    assert(planete_renderer);
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** mainLoop **********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::mainLoop()
{

    while(!m_data_manager.getTerminate())
    {
            this->fpsCalculation(BEGIN);

        /******************************************************************* MANAGING EVENTS ******************************************************************/
            this->inputProcess();
        //=====================================================================================================================================================

        /******************************************************************* MANAGING CHANGES *****************************************************************/
            this->makeAllChanges();
        //=====================================================================================================================================================

        /******************************************************************* RENDER AUDIO **********************************************************************/
            this->renderAudio();
        //======================================================================================================================================================

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

        /******************************************************************* RENDER SCENE *********************************************************************/
            this->renderScene();
        //======================================================================================================================================================

        /******************************************************************* RENDER SETTINGS *******************************************************************/
            this->renderSettings();
        //======================================================================================================================================================

        /******************************************************************* RENDER AUDIO **********************************************************************/
            this->renderOverlay();
        //======================================================================================================================================================

        /******************************************************************* SWAPPING WINDOWS *******************************************************************/
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(m_window);
        //=======================================================================================================================================================

            this->fpsCalculation(END);
            
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** makeAllChanges ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::makeAllChanges()
{
    if((ship != nullptr) && (m_input != nullptr))
    {
        if(!render_menu)
        {
            ship->transform(glm::vec3(0.f), m_input);
            ship->sendToShader(m_data_manager);
            m_data_manager.setShipPos(ship->getPosition());
        }
        ship->loadModelShip(m_data_manager);
    }
    if((camera != nullptr) && (m_input != nullptr))
    {
        camera->setDistFromShip(m_data_manager.getDistancteFromShip());
        camera->move(m_input, render_menu);
        camera->lookAt(m_data_manager.getViewMat());
        m_data_manager.setCamPos(camera->getPosition());
    }
    if(m_skybox != nullptr)
    {
        m_skybox->sendToShader(m_data_manager);
    }

    if(sun != nullptr)
    {
        sun->updatePosition(glm::vec3(0.f));
        sun->transform(-m_data_manager.getShipPos());
    } 

    if(mercury != nullptr)
    {
        mercury->updatePosition(glm::vec3(20.f, 0.f, 0.f));
        mercury->transform(-m_data_manager.getShipPos());
    } 

    if(earth != nullptr)
    {
        earth->updatePosition(glm::vec3(-40.f, 0.f, 0.f));
        earth->transform(-m_data_manager.getShipPos());
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderAudio ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::renderAudio()
{
    if(m_audio != nullptr)
    {
        m_audio->changeVolume(m_data_manager.getVolume());
        m_audio->pause(m_data_manager.getPause());
        m_audio->updateTrack(m_data_manager);
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** fpsCalculation ********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::fpsCalculation(int moment)
{
    switch (moment)
    {
        case BEGIN:
            start_loop = SDL_GetTicks();
            break;

        case END:
            end_loop = SDL_GetTicks();
            time_past = end_loop - start_loop;
            if(time_past < frame_rate)
            {
                SDL_Delay(frame_rate - time_past);
            }
            frame_rate = 1000 / m_data_manager.getFps();
            break;
        
        default:
            break;
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::renderOverlay()
{
    glm::mat4 save = m_data_manager.getViewMat();
    m_data_manager.lockView(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    m_overlay.renderEdges(m_data_manager);

    m_data_manager.resetViewMat(save);

    m_overlay.renderAppInfo();

    m_overlay.renderMusicInfo(m_data_manager);

    //m_overlay->displayNavigation(render_data);
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::renderScene()
{
    if(!render_menu)
    {
        ship->drawSpaceship(m_data_manager);
    }
    if(m_skybox != nullptr)
    {
        m_skybox->render(m_data_manager);
    }

    if((sun != nullptr) && (star_renderer != nullptr))
    {
        star_renderer->render(m_data_manager, sun);
    }

    if((mercury != nullptr) && (planete_renderer != nullptr))
    {
        planete_renderer->render(m_data_manager, mercury);
    }

    if((earth != nullptr) && (planete_renderer != nullptr))
    {
        planete_renderer->render(m_data_manager, earth);
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderInfo ***********************************************************************/
/***********************************************************************************************************************************************************************/
// void Application::renderInfo(RenderData &render_data)
// {
//     if((camera != nullptr) && (solar_system != nullptr) && (render_data.getShader("square") != nullptr))
//     {
//         if(render_data.getRenderInfo())
//         {
//             render_data.initSaveMat();

//                 if(render_data.getShader("text") != nullptr)
//                 {
//                     solar_system->drawInfo(render_data);
//                 }
                
//             render_data.saveViewMat();
//         }
//     }
// }

/***********************************************************************************************************************************************************************/
/*********************************************************************************** windowProcess *********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::inputProcess()
{
    if(m_input != nullptr)
    {
        m_input->updateEvents();

        if((m_input->getKey(SDL_SCANCODE_ESCAPE)) && (!menu_app_key_pressed))
        {
            render_menu = !render_menu;
            menu_app_key_pressed = true;
        }
        if ((m_input->getKey(SDL_SCANCODE_ESCAPE)) == false)
        {
            menu_app_key_pressed = false;
        }
    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderSetting *********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::renderSettings()
{
    if((render_menu) && (m_input != nullptr))
    {
        m_setting.manageSettings(m_data_manager);

        m_input->capturePointer(false);
        m_input->displayPointer(true);

    }
    else
    {
        m_input->capturePointer(true);
        m_input->displayPointer(false);
    }    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* renderParticles *********************************************************************/
/***********************************************************************************************************************************************************************/
// void Application::renderParticles(RenderData &render_data)
// {
//    if(m_particule_manager != nullptr)
//    {
//        m_particule_manager->renderParticules(render_data, ship, m_input);
//    }
// }