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
/*************************************************************************************** startLoop *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::startLoop()
{
    /************************************************* Variables ********************************************************/
    StartScreen *startScreen = new StartScreen();
    Camera      *startScreen_cam = new Camera(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0), 0.5, 0.9);

    aud = new Audio();

    solar_system = new SolarSystemCreator();

    Square      *square = new Square(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag");

    int nb_loaded(0);

    mat4 projection;
    mat4 model_view;
    mat4 save_model_view;     
    //===================================================================================================================

    m_input.displayPointer(false);
    m_input.capturePointer(true);

    //initialize modelview and projection matrix
    projection = perspective(70.0, (double)m_window_width / m_window_height, 1.0, 100.0);
    model_view = mat4(1.0);

    //loading system and making start screen
    while(nb_loaded < 9)
    {

        //cleaning the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        startScreen_cam->lookAt(model_view);

        //save the modelview matrix
        save_model_view = model_view;

            model_view = translate(model_view, vec3(0.0, 0.5, 2.6));
            startScreen->drawStartScreen(projection, model_view);

        //restaure the modelview matrix
        model_view = save_model_view;
        
            square->drawLoad(nb_loaded, projection, model_view);

        //restaure the modelview matrix
        model_view = save_model_view;

        //actualising the window
        SDL_GL_SwapWindow(m_window);

        if(nb_loaded == 0)
        {
            solar_system->MakingSystem("Solar System", 8);
            nb_loaded++;
        }
        if(nb_loaded < 9)
        {
            nb_loaded += solar_system->loadSystem(nb_loaded);
        }
        
    }

    SDL_Delay(1000);

    delete startScreen;
    delete startScreen_cam;
    delete square;

}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** mainLoop **********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::mainLoop()
{
    /************************************************* Variables ********************************************************/
    //Audio aud;
    bool pause(false); 
    int change(0);

    unsigned int frame_rate(1000 / 50);
    Uint32 start_loop(0), end_loop(0), time_past(0);

    Camera	*camera = new Camera(vec3(150, 150, 150), vec3(0, 0, 0), vec3(0, 0, 1), 0.5, 0.9);
    mat4 projection;
    mat4 model_view;
    mat4 save_model_view;
    aud = new Audio();
    solar_system = new SolarSystemCreator();
    //===================================================================================================================
    
    m_input.displayPointer(false);
    m_input.capturePointer(true);
    
    //initialize modelview and projection matrix
    projection = perspective(70.0, (double)m_window_width / m_window_height, 1.0, 500.0);
    model_view = mat4(1.0);

    //load and play the music
    aud->loadMusic();
    aud->playMusic();

    solar_system->MakingSystem("Solar System", 8);
    solar_system->loadSystem(1);

    while(!m_input.getTerminate())
    {   
        start_loop = SDL_GetTicks();
        
        /************************************************* managing events ********************************************************/
        m_input.updateEvents();

        if(m_input.getKey(SDL_SCANCODE_ESCAPE))
        {
            break;
        }

        if(m_input.getKey(SDL_SCANCODE_DOWN))
        {
            change = -1;
        }
        if(m_input.getKey(SDL_SCANCODE_UP))
        {
            change = 1;
        }

        if(m_input.getKey(SDL_SCANCODE_SPACE))
        {
            pause = true;
        }
        //===================================================================================================================

        aud->volume(change);
        aud->pause(pause);
        pause = false;
        change = 0;

        camera->move(m_input);

        //cleaning the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        camera->lookAt(model_view);
        
        glm::vec3 camPos = camera->getPosition();

        //save the modelview matrix
        save_model_view = model_view;

        /************************************************* SKYBOX RENDER ********************************************************/

            solar_system->drawSkybox(projection, model_view);

        //restaure the modelview matrix
        model_view = save_model_view;

        /************************************************* SOLAR SYSTEM RENDER ********************************************************/
        
            solar_system->drawSystem(projection, model_view, camPos);

        //restaure the modelview matrix
        model_view = save_model_view;

        /************************************************* NAME BODY RENDER ********************************************************/

            //solar_system->displayName(projection, model_view, camPos);

        //restaure the modelview matrix
        model_view = save_model_view;

        /************************************************* swapping windows ********************************************************/
        
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

    delete solar_system;
    delete camera;
    delete aud;
}
