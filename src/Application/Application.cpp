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
Application::Application(int width, int height, SDL_Window *window, Input *input, Audio *audio): m_data_manager(width, height, 45.0),
m_window(window), 
m_input(input), m_setting(), m_audio(audio), m_overlay()
{
    render_menu = false;
    menu_app_key_pressed = false;
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

    m_overlay.clean();
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* initFrameBuffer *********************************************************************/
/***********************************************************************************************************************************************************************/
// void Application::initFrameBuffer()
// {
//     assert(m_framebuffer->initFramebuffer(m_window_width, m_window_height));
// }

/***********************************************************************************************************************************************************************/
/*************************************************************************************** startLoop *********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::loadAssets()
{
    Renderer *square_renderer = new SquareRenderer(1.0);
    assert(square_renderer);
    Square  *square = new Square(1.0);
    assert(square);

    m_overlay.initOverlayAssets(square_renderer, square);
    m_skybox = new Skybox();
    assert(m_skybox);
    ship = new Spaceship();
    assert(ship);
    ship->loadModelShip(m_data_manager);
    camera = new Camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f), ship);
    assert(camera);
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** mainLoop **********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::mainLoop()
{
    /************************************************* Variables ********************************************************/
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

    

    //=====================================================================================================================================================


    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_None;

    while(!m_data_manager.getTerminate())
    {
            this->fpsCalculation(BEGIN);

        /******************************************************************* MANAGING EVENTS ******************************************************************/
            this->inputProcess();
        //=====================================================================================================================================================

        /******************************************************************* RENDER AUDIO **********************************************************************/
            this->renderAudio();
        //======================================================================================================================================================

        if(camera != nullptr)
        {
            camera->move(*m_input, render_menu);

            camera->lookAt(m_data_manager.getViewMat());
        }

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            if(!render_menu)
            {
                ship->drawSpaceship(m_data_manager, *m_input);
            }
            
            camera->setDistFromShip(3.f);

        /******************************************************************* RENDER SETTINGS *******************************************************************/
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

            glDisable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            this->fpsCalculation(END);
            
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderAudio ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::renderAudio()
{
    m_audio->changeVolume(m_data_manager.getVolume());
    m_audio->pause(m_data_manager.getPause());
    m_audio->updateTrack(m_data_manager);
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

    // m_overlay->displayMusicInfo(render_data);

    //m_overlay->displayNavigation(render_data);
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::renderScene()
{
    if(m_skybox != nullptr)
    {
        m_skybox->render(m_data_manager);
    }
//     if( (camera != nullptr) && (solar_system != nullptr))
//     {
//             render_data.initSaveMat();

//             /****************************************** skybox render **************************************************/

//                 solar_system->drawSkybox(render_data);

//             render_data.saveViewMat();

//             /****************************************** bodys render ****************************************************/
            
//                 solar_system->drawSystem(render_data);

//             render_data.saveViewMat();

//             // /****************************************** atmosphere render *************************************************/

//                 solar_system->drawAtmo(render_data);

//             render_data.saveViewMat();

//             // /******************************************* name render *****************************************************/

//                 if((render_data.getShader("text") != nullptr) && (render_data.getRenderName()))
//                 {
//                     solar_system->drawName(render_data);
//                 }
                
//             render_data.saveViewMat();


//             // /******************************************* ring render *****************************************************/

//                 solar_system->drawRing(render_data);
                
//             render_data.saveViewMat();


//             // /******************************************* asteroid field render *****************************************************/

//                 solar_system->drawAsteroidField(render_data);
                
//             render_data.saveViewMat();


//                 solar_system->setMostGravInfluence(render_data);

//                 solar_system->approchBody(ship);

//     }
    
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

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderSetting *********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::renderSettings()
{
    if(render_menu)
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