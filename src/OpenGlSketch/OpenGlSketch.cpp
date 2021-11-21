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
using namespace ButtonChoice;

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

    text_shader = new Shader("../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag");
    assert(text_shader);
    assert(text_shader->loadShader());

    m_overlay = new Overlay(m_police[1]);
    assert(m_overlay);

    m_settings = new Settings(m_police[1]);
    assert(m_settings);

    aud = new Audio();
    assert(aud);

    solar_system = new SolarSystemCreator();
    assert(solar_system);

    square_shader = new Shader("../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag");
    assert(square_shader);
    assert(square_shader->loadShader());

    Square      *square = new Square(0.05f, 0.500f);
    vec3 color = vec3(0.5f);
    assert(square);

    ship = new Spaceship("../assets/model/spaceship/untitled.obj");
    assert(ship);

    // m_particuleGenerator = new Particule(ship);
    // assert(m_particuleGenerator);

    m_model_shader = new Shader("../src/Shader/Shaders/model.vert", "../src/Shader/Shaders/model.frag");
    assert(m_model_shader);
    assert(m_model_shader->loadShader());

    int nb_loaded(0);

    mat4 projection;
    mat4 view;
    mat4 save_view;     
    //===================================================================================================================

    m_input.capturePointer(true);
    m_input.displayPointer(false);

    //initialize modelview and projection matrix
    projection = perspective(glm::radians(70.0), (double)m_window_width / m_window_height, 1.0, 120.0);
    view = mat4(1.0f);

    //loading system and making start screen
    while(nb_loaded < 9)
    {

        //cleaning the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(startScreen_cam != nullptr)
        {
            startScreen_cam->lookAt(view);
        }
        

        //save the modelview matrix
        save_view = view;

            view = translate(view, vec3(0.0f, 0.5f, 0.0f));
            if(startScreen != nullptr)
            {
                if(text_shader != nullptr)
                {
                    startScreen->drawStartScreen(projection, view, text_shader);
                }
            }
            

        //restaure the modelview matrix
        view = save_view;
        
            if(square != nullptr)
            {
                square->drawLoad(nb_loaded, projection, view, color, square_shader);
            }
            
        //restaure the modelview matrix
        view = save_view;

        //actualising the window
        SDL_GL_SwapWindow(m_window);

        if(nb_loaded == 0)
        {
            if(solar_system != nullptr)
            {
                sys_init_data sol_data;
                sol_data.name_sys = "Solar System";
                sol_data.companion_count = 8;
                assert(solar_system->MakingSystem(sol_data, m_police[0], m_model_shader));
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
    pause_music = false;
    speed_key_pressed = false;
    volume = 0;

    m_terminate = false;

    frame_rate = 1000 / 50;
    start_loop = 0;
    end_loop = 0;
    time_past = 0;

    camera = new Camera(vec3(1.0f, 9000.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), ship);
    // m_particuleGenerator->initParticles(camera->getTargetPoint());
    
    assert(camera);

    //hdr variables
    exposure = 5.0f;
    hdr = true;
    hdr_key_pressed = false;

    menu = false;
    menu_app_key_pressed = false;

    info_render = false;
    info_render_key_pressed = false;

    m_overlay_display = true;
    m_name_display = true;

    is_moving = false;

    //==================================================================================================================
    
    m_input.capturePointer(true);
    m_input.displayPointer(false);
    
    //initialize modelview and projection matrix
    projection = perspective(glm::radians(70.0), (double)m_window_width / m_window_height, 1.0, 900000.0);

    //TODO : change name by view
    view = mat4(1.0f);

    //load and play the music
    if(aud != nullptr)
    {
        assert(aud->loadMusic());
        // aud->playMusic();
    }

    while(!m_terminate)
    {   
        start_loop = SDL_GetTicks();
    
    /********************************************************** MANAGING EVENTS *************************************************************/
        m_input.updateEvents();

        windowProcess();

    //======================================================================================================================================

    /******************************************************** MANAGING MUSIC *******************************************************************/
        if(aud != nullptr)
        {
            aud->volume(volume);
            aud->pause(pause_music);
            volume = 0;
            // aud->updateTrack();
        }
        
    //===========================================================================================================================================
        if(camera != nullptr)
        {
            camera->move(m_input, !menu);

            camera->lookAt(view);
        }

    /********************************************************************** Framebuffer activation ******************************************************************/
            m_framebuffer->bindFramebuffer();

    /************************************************************** RENDER OF ALL THE SCENE *****************************************************************/
            renderScene();
    //=======================================================================================================================================================

    /******************************************************************* RENDER OVERLAY ********************************************************************/
            renderOverlay();
    //=======================================================================================================================================================

    /******************************************************************* RENDER OVERLAY ********************************************************************/
            renderInfo();
    //=======================================================================================================================================================

    /******************************************************************* RENDER OVERLAY ********************************************************************/
            renderSettings();
    //=======================================================================================================================================================

    /******************************************************************* RENDER PARTICLES ********************************************************************/
            renderParticles();
    //=======================================================================================================================================================

        save_view = view;

            std::vector<glm::mat4> projection_view;
            projection_view.push_back(projection);
            projection_view.push_back(view);
            projection_view.push_back(glm::mat4(1.0f));
            glm::vec3 camPos = camera->getPosition();

            ship->drawSpaceship(projection_view, camPos, hdr, m_model_shader, m_input);
        
        view = save_view;


    /**************************************************************** SWAPPING FRAMEBUFFER *****************************************************************/

        m_framebuffer->unbindFramebuffer();

        m_framebuffer->renderFrame(exposure, hdr);
        

    /************************************************* SWAPPING WINDOWS ********************************************************/

        //actualising the window
        SDL_GL_SwapWindow(m_window);

        //managing the frame rate
        end_loop = SDL_GetTicks();
        time_past = end_loop - start_loop;
        if(time_past < frame_rate)
        {
            SDL_Delay(frame_rate - time_past);
        }
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
    
    if(text_shader != nullptr)
    {
        delete text_shader;
    }

    if(square_shader != nullptr)
    {
        delete square_shader;
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

    if(m_model_shader != nullptr)
    {
        delete m_model_shader;
    }

    if(ship != nullptr)
    {
        delete ship;
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderOverlay()
{
    if((m_overlay_display) && (square_shader != nullptr))
    {
        if((aud != nullptr) && (camera != nullptr) && (m_overlay != nullptr))
        {
            std::string track = aud->getTrack();
            glm::vec3 position = camera->getPosition();
            float speed = ship->getSpeed();

                view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayGeneralOverlay(projection, view, hdr, square_shader);

                //restaure the modelview matrix
                view = save_view;

                view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayMusicOverlay(projection, view, hdr, track, text_shader, square_shader);

                //restaure the modelview matrix
                view = save_view;

                view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayMoveInfoOverlay(projection, view, hdr, position, speed, text_shader, square_shader);

                //restaure the modelview matrix
                view = save_view;

                view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayTimeInfoOverlay(projection, view, hdr, text_shader, square_shader);

                //restaure the modelview matrix
                view = save_view;
        }
        
    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderScene()
{
    if( (camera != nullptr) && (solar_system != nullptr))
    {
        glm::vec3 camPos = camera->getPosition();

            //save the modelview matrix
            save_view = view;

            /****************************************** skybox render **************************************************/

                solar_system->drawSkybox(projection, view, hdr);

            //restaure the modelview matrix
            view = save_view;

            /****************************************** bodys render ****************************************************/
            
                solar_system->drawSystem(projection, view, camPos, hdr);

            //restaure the modelview matrix
            view = save_view;

            /****************************************** atmosphere render *************************************************/

                solar_system->drawAtmo(projection, view, camPos, hdr);

            //restaure the modelview matrix
            view = save_view;

            /******************************************* name render *****************************************************/

                if((text_shader != nullptr) && (m_name_display == true))
                {
                    solar_system->drawName(projection, view, camPos, text_shader);
                }
                

            //restaure the modelview matrix
            view = save_view;

            /******************************************* asteroid field render *****************************************************/

                std::vector<glm::mat4> projection_view;
                projection_view.push_back(projection);
                projection_view.push_back(view);

                solar_system->drawAsteroidField(projection_view, camPos, hdr);
                
            //restaure the modelview matrix
            view = save_view;
    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderInfo ***********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderInfo()
{
    if((camera != nullptr) && (solar_system != nullptr) && (square_shader != nullptr))
    {
        if(info_render)
        {
            //save the modelview matrix
            save_view = view;

            glm::vec3 camPos = camera->getPosition();

                if(text_shader != nullptr)
                {
                    std::vector<Shader*> shaders;
                    shaders.push_back(text_shader);
                    shaders.push_back(square_shader);

                    solar_system->drawInfo(projection, view, camPos, hdr, shaders);
                }
                
            //restaure the modelview matrix
            view = save_view;
        }
    }
    
    

}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** windowProcess *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::windowProcess()
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
            if(ship->getSpeed() > 0.6f)
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
            menu = !menu;
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
void OpenGlSketch::renderSettings()
{
    if((camera != nullptr) && (m_settings != nullptr) && (square_shader != nullptr))
    {
        if(menu)
        {
            m_input.capturePointer(false);
            m_input.displayPointer(true);

            view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                m_settings->displayFrameSettings(projection, view, hdr, text_shader, square_shader);

            view = save_view;

            int button_type = m_settings->manageButton(m_input);

            switch (button_type)
            {
                case QUIT:
                    m_terminate = true;
                    break;

                case HDR_ON:
                    hdr = true;
                    if(exposure == 0.0f)
                    {
                        exposure = 5.0f;
                    }
                    break;

                case HDR_OFF:
                    hdr = false;
                    break;

                case EXPOSURE_DEC:
                    if( (exposure >= 0.0f) && (exposure <= 5.0f))
                    {
                        exposure = exposure - 1.0f;
                    }
                    if(exposure == 0.0f)
                    {
                        hdr = false;
                    }
                    break;

                case EXPOSURE_INC:
                    if( (exposure >= 0.0f) && (exposure <= 5.0f))
                    {
                        exposure = exposure + 1.0f;
                    }
                    if(exposure > 5.0f)
                    {
                        exposure = 5.0f;
                    }
                    if(exposure == 1.0f)
                    {
                        hdr = true;
                    }
                    break;

                case SPEED_DEC:
                    if((ship->getSpeed() >= 0.0f))
                    {
                        ship->setSpeed(-0.1f);
                    }
                    break;

                case SPEED_INC:
                    if(ship->getSpeed() <= 1.0f)
                    {
                        ship->setSpeed(0.1f);
                    }
                    break;

                case MUSIC_ON:
                    pause_music = false;
                    break;
        
                case MUSIC_OFF:
                    pause_music = true;
                    break;

                case MUSIC_DEC:
                    volume = -2;
                    break;

                case MUSIC_INC:
                    volume = 2;
                    break;

                case OVERLAY_ON:
                    m_overlay_display = true;
                    break;

                case OVERLAY_OFF:
                    m_overlay_display = false;
                    break;

                case PLANETE_INFO_ON:
                    info_render = true;
                    break;
                
                case PLANETE_INFO_OFF:
                    info_render = false;
                    break;

                case SHOW_NAME_ON:
                    m_name_display = true;
                    break;

                case SHOW_NAME_OFF:
                    m_name_display = false;
                    break;

                default:
                    break;
            }
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
    glm::mat4 save = view;

        // view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        // glm::vec3 target_point = camera->getTargetPoint();
        
        // if(m_particuleGenerator != nullptr)
        // {
        //     if((m_input.getKey(SDL_SCANCODE_W)) && (m_input.getKey(SDL_SCANCODE_S)))
        //     {
        //         //do nothing
        //     }
        //     else
        //     {
        //         // m_particuleGenerator->drawParticles(projection, view, m_input, is_moving, target_point);
        //     }
        // }

    view = save;
}