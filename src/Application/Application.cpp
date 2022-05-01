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
m_setting(), m_overlay(), m_audio(nullptr), m_input(nullptr), camera(nullptr), m_skybox(nullptr), ship(nullptr), m_framebuffer(nullptr)
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

    if(m_framebuffer == nullptr)
    {
        m_framebuffer = new Framebuffer();
        assert(m_framebuffer);
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

    if(m_framebuffer != nullptr)
    {
        m_framebuffer->clean();
        delete m_framebuffer;
        m_framebuffer = nullptr;
    }

    m_setting.clean();
    m_overlay.clean();

    if(m_solar_system != nullptr)
    {
        m_solar_system->cleanSystem();
        delete m_solar_system;
        m_solar_system = nullptr;
    }

    m_data_manager.clean();
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* loadFrameBuffer *********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::loadFrameBuffer()
{
    m_framebuffer->initFramebuffers(m_data_manager.getWidth(), m_data_manager.getHeight());
}

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
    m_data_manager.setShader();

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
    Renderer                *planete_renderer = nullptr;
    Renderer                *ring_renderer = nullptr;
    Renderer                *sphere_renderer = nullptr;
    Renderer                *square_renderer = nullptr;
    Square                  *square = nullptr;
    for(int assets_loads = -1; assets_loads < 11; assets_loads++)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(assets_loads == 0)
        {
            square_renderer = new SquareRenderer(1.0);
            assert(square_renderer);
            square = new Square(1.0, "square");
            assert(square);
            planete_renderer = new PlaneteRenderer(1.f, 70.f, 70.f);
            assert(planete_renderer);
            ring_renderer = new RingRenderer();
            assert(ring_renderer);
            sphere_renderer = new SphereRenderer(1.f, 70.f, 70.f);
            assert(sphere_renderer);

            m_overlay.initOverlayAssets(square_renderer, square);
            m_skybox = new Skybox();
            assert(m_skybox);
            ship = new Spaceship("model");
            assert(ship);
            ship->loadModelShip(m_data_manager);
            
            camera = new Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), ship);
            assert(camera);

            DataManager::initDatas();

            m_solar_system = new SolarSystemCreator();
            assert(m_solar_system);
            assert(m_solar_system->MakingSystem(planete_renderer, ring_renderer, sphere_renderer, "Solar System"));
        }

        if((assets_loads >= 0) && (assets_loads < 8)) { m_solar_system->loadSystem(assets_loads);}

        ImGuiWindowFlags window_flags = 0;
        ImGuiStyle& style = ImGui::GetStyle();
        float save_frame = style.FrameRounding;
        style.FrameRounding = 15;

        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoScrollbar;

        ImGui::SetNextWindowPos(ImVec2(m_data_manager.getWidth()/2 - 50.f, m_data_manager.getHeight()/2 - 25.f));
        ImGui::SetNextWindowSize(ImVec2(100, 50.f));
        ImGui::Begin("Solar System", NULL, window_flags);
        ImGui::Text("Solar System");
        ImGui::End();
    
        ImGui::SetNextWindowPos(ImVec2((m_data_manager.getWidth()/2 - 300), (m_data_manager.getHeight()/2 - 25.f) + 300));
        ImGui::SetNextWindowSize(ImVec2(600, 50.f));
    
        ImGui::Begin("Progress Bar", NULL, window_flags);
        float progress = (float) (assets_loads + 1) * 0.1f;
        ImGui::ProgressBar(progress, ImVec2(-1.f, -1.f));
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(m_window);

        if(assets_loads == 10) { SDL_Delay(1000);}

        style.FrameRounding = save_frame;
    }
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

        /******************************************************************* IMGUI PIPELINE ********************************************************************/
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
        //======================================================================================================================================================

        /******************************************************************* DEPTH MAP CALCULATION *************************************************************/
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            m_data_manager.setPass(DEPTH_FBO);
            this->renderIntoFramebuffer(DEPTH_FBO);
        //======================================================================================================================================================

        /******************************************************************* RENDER SYSTEM *********************************************************************/
            m_data_manager.setPass(COLOR_FBO);
            this->renderIntoFramebuffer(COLOR_FBO);
        //======================================================================================================================================================

        /******************************************************************* RENDER SETTINGS *******************************************************************/
            this->renderSettings();
        //======================================================================================================================================================

        /******************************************************************* RENDER OVERLAY ********************************************************************/
            this->renderOverlay();
        //======================================================================================================================================================

        /******************************************************************* RENDER OVERLAY ********************************************************************/
            this->renderNameAndInfo();
        //======================================================================================================================================================

            m_framebuffer->unbindFramebuffer();
            m_framebuffer->renderFrame(m_data_manager);

        /******************************************************************* SWAPPING WINDOWS *******************************************************************/
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(m_window);
        //=======================================================================================================================================================

            this->fpsCalculation(END);
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** renderIntoFramebuffer ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::renderIntoFramebuffer(int type)
{
    m_framebuffer->bindFramebuffer(type);
    

        if(m_data_manager.getPass() == DEPTH_FBO)
        {
            glViewport(0, 0, m_data_manager.getWidth(), m_data_manager.getWidth());
            glClear(GL_DEPTH_BUFFER_BIT);
            glCullFace(GL_FRONT);
        }
        else
        {
            glViewport(0, 0, m_data_manager.getWidth(), m_data_manager.getHeight());
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        /******************************************************************* RENDER SCENE *********************************************************************/
            this->renderScene();
        //======================================================================================================================================================

        if(m_data_manager.getPass() == DEPTH_FBO)
        {
            glCullFace(GL_BACK);
            m_framebuffer->unbindFramebuffer();
        }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** makeAllChanges ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::makeAllChanges()
{
    if((ship != nullptr) && (m_input != nullptr))
    {
        if((!render_menu) )
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
        m_data_manager.setViewMat(camera->getViewMatrix());
        m_data_manager.setCamPos(camera->getPosition());
    }

    if(m_skybox != nullptr)
    {
        m_skybox->sendToShader(m_data_manager);
    }

    if(m_solar_system != nullptr)
    {
        m_solar_system->makeChanges(m_data_manager);
    }

    std::vector<glm::mat4> shadowTransforms = m_data_manager.getLightSpaceMatrix();
    glUseProgram(m_data_manager.getShader("depth_map")->getProgramID());
        for(int i = 0; i < 6; ++i)
        {
            m_data_manager.getShader("depth_map")->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
        }
        m_data_manager.getShader("depth_map")->setFloat("far_plane", m_data_manager.getFar());
        m_data_manager.getShader("depth_map")->setVec3("sunPos", m_data_manager.getSunPos());
    glUseProgram(0);
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
    if(m_data_manager.getRenderOverlay())
    {
        glm::mat4 save = m_data_manager.getViewMat();
        m_data_manager.lockView(glm::vec3(0.0f, 0.0f, -1.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_overlay.renderEdges(m_data_manager);
        m_data_manager.resetViewMat(save);

        m_overlay.renderAppInfo();

        m_overlay.renderMusicInfo(m_data_manager);

        //m_overlay->displayNavigation(render_data);
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::renderScene()
{   

    if(!render_menu && (m_data_manager.getPass() == COLOR_FBO))
    {
        ship->drawSpaceship(m_data_manager);
    }
    if(m_skybox != nullptr)
    {
        m_skybox->render(m_data_manager);
    }

    if(m_solar_system != nullptr)
    {
        m_solar_system->render(m_data_manager);
        m_solar_system->renderRing(m_data_manager);
        m_solar_system->renderAtmosphere(m_data_manager);
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** inputProcess *********************************************************************/
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
/*********************************************************************************** renderNameAndInfo *********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::renderNameAndInfo()
{
    m_solar_system->renderNameAndInfo(m_data_manager);
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