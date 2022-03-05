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
Application::Application(int width, int height, SDL_Window *window, Input *input): m_data_manager(width, height),
m_window(window), 
m_input(input), m_setting()
{
    render_menu = false;
    menu_app_key_pressed = false;
}

Application::~Application()
{
    
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
// void Application::startLoop()
// {
//     /************************************************* Variables ********************************************************/
//     /************************************************* load police ********************************************************/
//     m_police.push_back(TTF_OpenFont("../../assets/font/venus rising rg.ttf", 300));
//     if(m_police[0] == nullptr)
//     {
//         std::cout << ">> Loading font file : ERROR : " << TTF_GetError() << std::endl;
//     }
//     std::cout << ">> Loading font file  " << "venus rising rg.ttf" << " : SUCCESS" << std::endl;

//     m_police.push_back(TTF_OpenFont("../../assets/font/aAtmospheric.ttf", 300));
//     if(m_police[1] == nullptr)
//     {
//         std::cout << ">> Loading font file : ERROR : " << TTF_GetError() << std::endl;
//     }
//     std::cout << ">> Loading font file  " << "aAtmospheric.ttf" << " : SUCCESS" << std::endl;

//     StartScreen *startScreen = new StartScreen(m_police[0]);
//     assert(startScreen);

//     Camera      *startScreen_cam = new Camera(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
//     assert(startScreen_cam);

//     m_overlay = new Overlay();
//     assert(m_overlay);

//     m_settings = new Settings();
//     assert(m_settings);

//     aud = new Audio();
//     assert(aud);

//     solar_system = new SolarSystemCreator();
//     assert(solar_system);

//     Square      *square = new Square(0.05f, 0.500f);
//     vec3 color = vec3(0.5f);
//     assert(square);

//     ship = new Spaceship();
//     assert(ship);

//     m_particule_manager = new ParticuleManager();
//     assert(m_particule_manager);

//     int nb_loaded(0);
   
//     //===================================================================================================================

//     m_input.capturePointer(true);
//     m_input.displayPointer(false);

//     RenderData render(m_window_width, m_window_height, 70.0f, false);
//     RenderData::setWidth(m_window_width);
//     RenderData::setHeight(m_window_height);

//     //loading system and making start screen
//     while(nb_loaded < 9)
//     {
//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplSDL2_NewFrame();
//         ImGui::NewFrame();

//         //cleaning the screen
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         if(startScreen_cam != nullptr)
//         {
//             startScreen_cam->lookAt(render.getViewMat());
//         }
        

//         //save the modelview matrix
//         render.initSaveMat();
        
//             if(startScreen != nullptr)
//             {
//                 if(render.getShader("text") != nullptr)
//                 {
//                     startScreen->drawStartScreen(render);
//                 }
//             }
            

//         //restaure the modelview matrix
//         render.saveViewMat();
        
//             if(square != nullptr)
//             {
//                 square->drawLoad(nb_loaded, render, color);
//             }
            
//         //restaure the modelview matrix
//         render.saveViewMat();

//         if(nb_loaded == 0)
//         {
//             if(solar_system != nullptr)
//             {
//                 sys_init_data sol_data;
//                 sol_data.name_sys = "Solar System";
//                 sol_data.companion_count = 8;
//                 assert(solar_system->MakingSystem(sol_data, m_police[0]));
//                 nb_loaded++;
//             }
            
//         }
//         if(nb_loaded < 9)
//         {
//             if(solar_system != nullptr)
//             {
//                 nb_loaded += solar_system->loadSystem(nb_loaded, m_police[0]);
//             }
            
//         }

//         ImGui::Render();
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//         //actualising the window
//         SDL_GL_SwapWindow(m_window);
        
//     }

//     SDL_Delay(1000);

//     if(startScreen != nullptr)
//     {
//         delete startScreen;
//     }
    
//     if(startScreen_cam != nullptr)
//     {
//         delete startScreen_cam;
//     }
    
//     if(square != nullptr)
//     {
//         delete square;
//     }
    

// }

/***********************************************************************************************************************************************************************/
/*************************************************************************************** mainLoop **********************************************************************/
/***********************************************************************************************************************************************************************/
void Application::mainLoop()
{
    /************************************************* Variables ********************************************************/
    m_data_manager.setFps(60);
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

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

        /******************************************************************* RENDER SETTINGS *******************************************************************/
            this->renderSettings();
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
// void Application::renderOverlay(RenderData &render_data)
// {
//     if((render_data.getOverlayRender()) && (render_data.getShader("square") != nullptr))
//     {
//         if((aud != nullptr) && (camera != nullptr) && (m_overlay != nullptr))
//         {
//             render_data.initSaveMat();

//             render_data.lockViewMat(vec3(0.0f, 0.0f, 1.71f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

//                 m_overlay->displayGeneralOverlay(render_data);

//             render_data.saveViewMat();

//                 m_overlay->displayMusicInfo(render_data);

//                 m_overlay->displayNavigation(render_data);

//                 m_overlay->displayAppInfo(render_data);

//         }
        
//     }
    
// }

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
// void Application::renderScene(RenderData &render_data)
// {
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
    
// }

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
        render_menu = true;
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
    }

    // if((camera != nullptr) && (m_settings != nullptr) && (render_data.getShader("square") != nullptr))
    // {
    //     if(render_data.getMenu())
    //     {
    //         m_input.capturePointer(false);
    //         m_input.displayPointer(true);

    //         m_settings->manageSettings(render_data);
    //     }
    //     else
    //     {
    //         m_input.capturePointer(true);
    //         m_input.displayPointer(false);
    //     }
    // }
    
    
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