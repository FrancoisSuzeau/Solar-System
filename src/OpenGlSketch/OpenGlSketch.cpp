/*
AUTHOR : SUZEAU François

DATE : 26/05/2021

MODULE : OpenGlSketch

NAMEFILE : OpenGlSketch.h

PURPOSE :   - creating OpenGL Context
            - Intialise all object of the scene
            - manage event and interaction
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "OpenGlSketch.hpp"

using namespace glm;
// using namespace ButtonChoice;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
OpenGlSketch::OpenGlSketch(): m_window_title("No name"), m_window_width(800), m_window_height(600), m_input()
//m_openGL_context(0), m_window(0), m_initiGLEW(0), m_input()
{
    
}

OpenGlSketch::OpenGlSketch(std::string window_title, int width, int height): m_window_title(window_title), m_window_width(width), m_window_height(height), m_input()
//m_openGL_context(0), m_window(0), m_initiGLEW(0), m_input()
{
    m_framebuffer = new Framebuffer();
    assert(m_framebuffer);
}

OpenGlSketch::~OpenGlSketch()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(m_openGL_context);
    SDL_DestroyWindow(m_window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    puts("");
    puts("");
    puts("");
    std::cout << ">> Leaving program SDL : SUCCESS" << std::endl;
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** initWindow ********************************************************************/
/***********************************************************************************************************************************************************************/

bool OpenGlSketch::initWindow()
{
    /************************************************* initialize SDL ********************************************************/
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << ">> Initialise SDL : ERROR : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    std::cout << ">> Initialise SDL : SUCCESS" << std::endl;
    //===================================================================================================================

    /************************************************* initialize SDL mixer ********************************************************/
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        std::cout << ">> Initialise SDL mixer : ERROR : " << Mix_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    std::cout << ">> Initialise SDL mixer : SUCCESS" << std::endl;
    //===================================================================================================================

    /************************************************* initialize SDL ttf ********************************************************/
    if(TTF_Init() < 0)
    {
        std::cout << ">> Initialise TTF : ERROR : " << TTF_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Initialise TTF : SUCCESS" << std::endl;
    //===================================================================================================================

    /************************************************* setting attribute for openGL context ********************************************************/
    //openGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    /*
        - SDL_GL_CONTEXT_PROFILE_CORE : erradicate all ancient implementation OpenGL fonctionnality
        - SDL_GL_CONTEXT_PROFILE_COMPATIBILITY : compatible with OpenGL 2.1
    */

    //double buffering deprecated in OpenGL 3.3
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //===================================================================================================================

    m_window = SDL_CreateWindow(m_window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_width, m_window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(m_window == NULL)
    {
        std::cout << ">> Creating window : ERROR : " << SDL_GetError() << std::endl;
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Creating window : SUCCESS" << std::endl;
    //===================================================================================================================

    /************************************************* creating an openGL context ********************************************************/
    m_openGL_context = SDL_GL_CreateContext(m_window);
    if(m_openGL_context == 0)
    {
        std::cout << ">> Creating context OpenGL : ERROR : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Creating context OpenGL : SUCCESS" << std::endl;
    //===================================================================================================================

    return true;
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** initGL ************************************************************************/
/***********************************************************************************************************************************************************************/
bool OpenGlSketch::initGL()
{
    /************************************************* initialize Glew ********************************************************/
    m_initiGLEW = glewInit();
    if (m_initiGLEW != GLEW_OK)
    {
        std::cout << ">> Initialize Glew : ERROR : " << glewGetErrorString(m_initiGLEW) << std::endl;
        SDL_GL_DeleteContext(m_openGL_context);
        SDL_DestroyWindow(m_window);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Initialize Glew : SUCCESS" << std::endl;
    glEnable(GL_DEPTH_TEST);
    //===================================================================================================================

    return true; 
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ initImGUI ************************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::initImGUI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(m_window, m_openGL_context);
    ImGui_ImplOpenGL3_Init("#version 330");
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* initFrameBuffer *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::initFrameBuffer()
{
    assert(m_framebuffer->initFramebuffer(m_window_width, m_window_height));
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** startLoop *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::startLoop()
{
    /************************************************* Variables ********************************************************/
    /************************************************* load police ********************************************************/
    m_police.push_back(TTF_OpenFont("../assets/font/venus rising rg.ttf", 300));
    if(m_police[0] == nullptr)
    {
        std::cout << ">> Loading font file : ERROR : " << TTF_GetError() << std::endl;
    }
    std::cout << ">> Loading font file  " << "../assets/font/venus rising rg.ttf" << " : SUCCESS" << std::endl;

    m_police.push_back(TTF_OpenFont("../assets/font/aAtmospheric.ttf", 300));
    if(m_police[1] == nullptr)
    {
        std::cout << ">> Loading font file : ERROR : " << TTF_GetError() << std::endl;
    }
    std::cout << ">> Loading font file  " << "../assets/font/aAtmospheric.ttf" << " : SUCCESS" << std::endl;

    StartScreen *startScreen = new StartScreen(m_police[0]);
    assert(startScreen);

    Camera      *startScreen_cam = new Camera(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    assert(startScreen_cam);

    m_overlay = new Overlay();
    assert(m_overlay);

    m_settings = new Settings();
    assert(m_settings);

    aud = new Audio();
    assert(aud);

    solar_system = new SolarSystemCreator();
    assert(solar_system);

    Square      *square = new Square(0.05f, 0.500f);
    vec3 color = vec3(0.5f);
    assert(square);

    ship = new Spaceship("../assets/model/spaceship/untitled.obj", 0.1f);
    assert(ship);

    // m_particuleGenerator = new Particule(ship);
    // assert(m_particuleGenerator);

    int nb_loaded(0);
   
    //===================================================================================================================

    m_input.capturePointer(true);
    m_input.displayPointer(false);

    RenderData render(m_window_width, m_window_height, 70.0f, false);

    //loading system and making start screen
    while(nb_loaded < 9)
    {

        //cleaning the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(startScreen_cam != nullptr)
        {
            startScreen_cam->lookAt(render.getViewMat());
        }
        

        //save the modelview matrix
        render.initSaveMat();
        
            if(startScreen != nullptr)
            {
                if(render.getShader("text") != nullptr)
                {
                    startScreen->drawStartScreen(render);
                }
            }
            

        //restaure the modelview matrix
        render.saveViewMat();
        
            if(square != nullptr)
            {
                square->drawLoad(nb_loaded, render, color);
            }
            
        //restaure the modelview matrix
        render.saveViewMat();

        //actualising the window
        SDL_GL_SwapWindow(m_window);

        if(nb_loaded == 0)
        {
            if(solar_system != nullptr)
            {
                sys_init_data sol_data;
                sol_data.name_sys = "Solar System";
                sol_data.companion_count = 8;
                assert(solar_system->MakingSystem(sol_data, m_police[0]));
                nb_loaded++;
            }
            
        }
        if(nb_loaded < 9)
        {
            if(solar_system != nullptr)
            {
                nb_loaded += solar_system->loadSystem(nb_loaded, m_police[0]);
            }
            
        }
        
    }

    SDL_Delay(1000);

    if(startScreen != nullptr)
    {
        delete startScreen;
    }
    
    if(startScreen_cam != nullptr)
    {
        delete startScreen_cam;
    }
    
    if(square != nullptr)
    {
        delete square;
    }
    

}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** mainLoop **********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::mainLoop()
{
    /************************************************* Variables ********************************************************/
    speed_key_pressed = false;

    m_terminate = false;

    RenderData render_data(m_window_width, m_window_height, 45.0f, true);
    render_data.setTrackMusic(1);
    render_data.setPauseMusic(true);
    

    camera = new Camera(vec3(1.0f, 9000.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), ship);
    // m_particuleGenerator->initParticles(camera->getTargetPoint());
    
    assert(camera);

    hdr_key_pressed = false;

    render_data.setMenu(false);
    menu_app_key_pressed = false;

    info_render = false;
    info_render_key_pressed = false;

    m_overlay_display = true;
    m_name_display = true;

    is_moving = false;

    //==================================================================================================================
    
    m_input.capturePointer(true);
    m_input.displayPointer(false);

    //load and play the music
    if(aud != nullptr)
    {
        assert(aud->loadMusic(render_data));
        // aud->playMusic();
    }

    while(!m_terminate)
    {
        render_data.initFrameRate();
    
    /********************************************************** MANAGING EVENTS *************************************************************/
        m_input.updateEvents();

        windowProcess(render_data);

    //======================================================================================================================================

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

    /******************************************************** MANAGING MUSIC *******************************************************************/
        if(aud != nullptr)
        {
            aud->changeVolume(render_data.getVolume());
            aud->pause(render_data.getPauseMusic());
            aud->updateTrack(render_data);
        }

    /********************************************************************** Framebuffer activation ******************************************************************/
            m_framebuffer->bindFramebuffer();
        
    //===========================================================================================================================================
        if(camera != nullptr)
        {
            camera->move(m_input, render_data.getMenu());

            camera->lookAt(render_data.getViewMat());
        }

        render_data.setCamPos(camera->getPosition());
        render_data.setShipPos(ship->getPosition());
        render_data.setShipSpeed(ship->getSpeed());

    /************************************************************** RENDER OF ALL THE SCENE *****************************************************************/
            renderScene(render_data);
    //=======================================================================================================================================================

    /******************************************************************* RENDER OVERLAY ********************************************************************/
            renderOverlay(render_data);
    //=======================================================================================================================================================

    /******************************************************************* RENDER OVERLAY ********************************************************************/
            renderInfo(render_data);
    //=======================================================================================================================================================

    /******************************************************************* RENDER OVERLAY ********************************************************************/
            renderSettings(render_data);
    //=======================================================================================================================================================

    /******************************************************************* RENDER PARTICLES ********************************************************************/
            // renderParticles();
    //=======================================================================================================================================================

        render_data.initSaveMat();

            if(!render_data.getMenu())
            {
                ship->drawSpaceship(render_data, m_input);
            }
            
        
        render_data.saveViewMat();

    /**************************************************************** SWAPPING FRAMEBUFFER *****************************************************************/

        ImGui::Render();
        m_framebuffer->renderFrame(render_data);
        

    /************************************************* SWAPPING WINDOWS ********************************************************/

        //actualising the window

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(m_window);

        render_data.manageFrameRate();
    //===================================================================================================================
    }

    if(m_framebuffer != nullptr)
    {
        delete m_framebuffer;
    }

    if(solar_system != nullptr)
    {
        delete solar_system;
    }
    
    if(camera != nullptr)
    {
        delete camera;
    }
    
    if(aud != nullptr)
    {
        delete aud;
    }

    if(m_overlay != nullptr)
    {
        delete m_overlay;
    }
    
    if(m_settings != nullptr)
    {
        delete m_settings;
    }

    // if(m_particuleGenerator != nullptr)
    // {
    //     delete m_particuleGenerator;
    // }

    for (int i(0); i < 2; i++)
    {
        if(m_police[i] != nullptr)
        {
            TTF_CloseFont(m_police[i]);
        }
    }

    if(ship != nullptr)
    {
        delete ship;
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderOverlay(RenderData &render_data)
{
    if((m_overlay_display) && (render_data.getShader("square") != nullptr))
    {
        if((aud != nullptr) && (camera != nullptr) && (m_overlay != nullptr))
        {
            render_data.initSaveMat();

                render_data.lockViewMat(vec3(0.0f, 0.0f, 1.71f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayGeneralOverlay(render_data);

                render_data.saveViewMat();

                render_data.lockViewMat(vec3(0.0f, 0.0f, 1.71f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayMusicInfo(render_data);

                render_data.saveViewMat();

                render_data.lockViewMat(vec3(0.0f, 0.0f, 1.71f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayNavigation(render_data);

                render_data.saveViewMat();

                render_data.lockViewMat(vec3(0.0f, 0.0f, 1.71f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayAppInfo(render_data);

            render_data.saveViewMat();

        }
        
    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderScene(RenderData &render_data)
{
    if( (camera != nullptr) && (solar_system != nullptr))
    {
        // glm::vec3 camPos = camera->getPosition();

            render_data.initSaveMat();

            /****************************************** skybox render **************************************************/

                solar_system->drawSkybox(render_data);

            render_data.saveViewMat();

            /****************************************** bodys render ****************************************************/
            
                solar_system->drawSystem(render_data);

            render_data.saveViewMat();

            // /****************************************** atmosphere render *************************************************/

                solar_system->drawAtmo(render_data);

            render_data.saveViewMat();

            // /******************************************* name render *****************************************************/

                if((render_data.getShader("text") != nullptr) && (m_name_display == true))
                {
                    solar_system->drawName(render_data);
                }
                
            render_data.saveViewMat();


            // /******************************************* ring render *****************************************************/

                solar_system->drawRing(render_data);
                
            render_data.saveViewMat();


            // /******************************************* asteroid field render *****************************************************/

                solar_system->drawAsteroidField(render_data);
                
            render_data.saveViewMat();

    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderInfo ***********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderInfo(RenderData &render_data)
{
    if((camera != nullptr) && (solar_system != nullptr) && (render_data.getShader("square") != nullptr))
    {
        if(info_render)
        {
            render_data.initSaveMat();

                if(render_data.getShader("text") != nullptr)
                {
                    solar_system->drawInfo(render_data);
                }
                
            render_data.saveViewMat();
        }
    }
    
    

}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** windowProcess *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::windowProcess(RenderData &render_data)
{
        if(m_input.getKey(SDL_SCANCODE_ESCAPE))
        {
            m_terminate = true;
        }

        int scroll = m_input.getScroll();

        if(ship != nullptr)
        {
            if(scroll != 0)
            {
                if((ship->getSpeed() < 200.0f) && (scroll > 0))
                {
                    ship->setSpeed(1.0f);
                }

                if((ship->getSpeed() >= 0.0f) && (scroll < 0))
                {
                    ship->setSpeed(-1.0f);
                }
            }
        }
        
        
        if((m_input.getKey(SDL_SCANCODE_Q)) && (!speed_key_pressed))
        {
            if(ship->getSpeed() > 0.6f)
            {
                ship->setMinimumSpeed();
            }
            speed_key_pressed = true;
        }
        if ((m_input.getKey(SDL_SCANCODE_Q)) == false)
        {
            speed_key_pressed = false;
        }

        if((m_input.getKey(SDL_SCANCODE_E)) && (!speed_key_pressed))
        {
            if(ship->getSpeed() >= 0.6f)
            {
                ship->setMaximumSpeed();
            }
            speed_key_pressed = true;
        }
        if ((m_input.getKey(SDL_SCANCODE_E)) == false)
        {
            speed_key_pressed = false;
        }

        if((m_input.getKey(SDL_SCANCODE_P)) && (!menu_app_key_pressed))
        {
            render_data.setMenu(!render_data.getMenu());
            menu_app_key_pressed = true;
        }
        if ((m_input.getKey(SDL_SCANCODE_P)) == false)
        {
            menu_app_key_pressed = false;
        }

        if((m_input.getKey(SDL_SCANCODE_I)) && (!info_render_key_pressed))
        {
            info_render = !info_render;
            info_render_key_pressed = true;
        }
        if ((m_input.getKey(SDL_SCANCODE_I)) == false)
        {
            info_render_key_pressed = false;
        }

        if((m_input.getKey(SDL_SCANCODE_W)) || (m_input.getKey(SDL_SCANCODE_S)) || (m_input.getKey(SDL_SCANCODE_A)) || (m_input.getKey(SDL_SCANCODE_D)))
        {
            is_moving = true;
        }
        else if((!m_input.getKey(SDL_SCANCODE_W)) && (!m_input.getKey(SDL_SCANCODE_S)) && (!m_input.getKey(SDL_SCANCODE_A)) && (!m_input.getKey(SDL_SCANCODE_D)))
        {
            is_moving = false;
        }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderSetting *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderSettings(RenderData &render_data)
{
    if((camera != nullptr) && (m_settings != nullptr) && (render_data.getShader("square") != nullptr))
    {
        if(render_data.getMenu())
        {
            m_input.capturePointer(false);
            m_input.displayPointer(true);

            // render_data.initSaveMat();

            // render_data.lockViewMat(glm::vec3(0.0f, 0.0f, 1.71f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

            //     m_settings->displayFrameSettings(render_data);

            // render_data.saveViewMat();

            // int button_type = m_settings->manageButton(m_input);

            // switch (button_type)
            // {
            //     case QUIT:
            //         m_terminate = true;
            //         break;

            //     case HDR_ON:
            //         render_data.updateHDR(true);
            //         if(render_data.getExposure() <= 0.5f)
            //         {
            //             render_data.updateExposure(0.8f);
            //         }
            //         break;

            //     case HDR_OFF:
            //         render_data.updateHDR(false);
            //         render_data.updateExposure(0.5f);
            //         break;

            //     case EXPOSURE_DEC:
            //         if( (render_data.getExposure() > 0.5f) && (render_data.getExposure() <= 0.8f))
            //         {
            //             render_data.changeExposure(-0.1f);
            //         }
            //         if(render_data.getExposure() <= 0.5f)
            //         {
            //             render_data.updateHDR(false);
            //             render_data.updateExposure(0.5f);
            //         }
            //         break;

            //     case EXPOSURE_INC:
            //         if( (render_data.getExposure() >= 0.5f) && (render_data.getExposure() <= 0.8f))
            //         {
            //             render_data.changeExposure(0.1f);
            //         }
            //         if(render_data.getExposure() > 0.8f)
            //         {
            //             render_data.updateExposure(0.8f);
            //         }
            //         if(render_data.getExposure() == 0.8f)
            //         {
            //             render_data.updateHDR(true);
            //         }
            //         break;

            //     case SPEED_DEC:
            //         if((ship->getSpeed() >= 0.0f))
            //         {
            //             ship->setSpeed(-0.1f);
            //         }
            //         break;

            //     case SPEED_INC:
            //         if(ship->getSpeed() <= 1.0f)
            //         {
            //             ship->setSpeed(0.1f);
            //         }
            //         break;

            //     case OVERLAY_ON:
            //         m_overlay_display = true;
            //         break;

            //     case OVERLAY_OFF:
            //         m_overlay_display = false;
            //         break;

            //     case PLANETE_INFO_ON:
            //         info_render = true;
            //         break;
                
            //     case PLANETE_INFO_OFF:
            //         info_render = false;
            //         break;

            //     case SHOW_NAME_ON:
            //         m_name_display = true;
            //         break;

            //     case SHOW_NAME_OFF:
            //         m_name_display = false;
            //         break;

            //     default:
            //         break;
            // }
            // if(render_data.getHDR())
            // {
            //     render_data.updateBloom(true);
            // }
            // else
            // {
            //     render_data.updateBloom(false);
            // }
        }
        else
        {
            m_input.capturePointer(true);
            m_input.displayPointer(false);
        }
    }
    
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* renderParticles *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderParticles()
{
    // glm::mat4 save = view;

    //     // view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    //     // glm::vec3 target_point = camera->getTargetPoint();
        
    //     // if(m_particuleGenerator != nullptr)
    //     // {
    //     //     if((m_input.getKey(SDL_SCANCODE_W)) && (m_input.getKey(SDL_SCANCODE_S)))
    //     //     {
    //     //         //do nothing
    //     //     }
    //     //     else
    //     //     {
    //     //         // m_particuleGenerator->drawParticles(projection, view, m_input, is_moving, target_point);
    //     //     }
    //     // }

    // view = save;
}