/*
AUTHOR : SUZEAU François

DATE : 04/03/2021

MODULE : ContextManager

NAMEFILE : ContextManager.hpp

PURPOSE :   - Initialize SDL (Image, Mixer, TTF)
            - Initialize OpenGL context
            - Initialize GLew
            - Initialize Initialize ImGui
*/

#include "ContextManager.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
ContextManager::ContextManager()
{
    
}

ContextManager::~ContextManager()
{
    
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** Init **************************************************************************/
/***********************************************************************************************************************************************************************/
bool ContextManager::Init(Sdl_manage &sdl_manager)
{
    sdl_manager.title = "Solar System Simulator";
    // sdl_manager.win_width = 800;
    // sdl_manager.win_height = 800;
    sdl_manager.win_width = GetSystemMetrics(SM_CXSCREEN);
    sdl_manager.win_height = GetSystemMetrics(SM_CYSCREEN);
    /************************************************* initialize SDL ********************************************************/
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << ">> Initialise SDL : ERROR : " << SDL_GetError() << std::endl;
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
    //==================================================================================================================

    if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) < 0)
    {
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        std::cout << ">> Set GL attribute ERROR : MAJOR VERSION " << SDL_GetError() << std::endl;
        return false;
    }
    
    if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) < 0)
    {
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        std::cout << ">> Set GL attribute ERROR : MINOR VERSION " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    /*
        - SDL_GL_CONTEXT_PROFILE_CORE : erradicate all ancient implementation OpenGL fonctionnality
        - SDL_GL_CONTEXT_PROFILE_COMPATIBILITY : compatible with OpenGL 2.1
    */

    //double buffering deprecated in OpenGL 3.3
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //===================================================================================================================

    sdl_manager.window = SDL_CreateWindow(sdl_manager.title.c_str(), 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED,
                            sdl_manager.win_width,
                            sdl_manager.win_height,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(sdl_manager.window == NULL)
    {
        std::cout << ">> Creating window : ERROR : " << SDL_GetError() << std::endl;
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Creating window : SUCCESS" << std::endl;
    //====================================================================================================================

    return true;
}

bool ContextManager::Init(SDL_GLContext &gl_context, SDL_Window *window)
{
    /************************************************* creating an openGL context ********************************************************/
    gl_context = SDL_GL_CreateContext(window);
    if(gl_context == 0)
    {
        std::cout << ">> Creating context OpenGL : ERROR : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Creating context OpenGL : SUCCESS" << std::endl;
    //===================================================================================================================

    return true;
}

bool ContextManager::Init(GLenum init_glew, SDL_GLContext gl_context, SDL_Window *window)
{
    init_glew = glewInit();
    if (init_glew != GLEW_OK)
    {
        std::cout << ">> Initialize Glew : ERROR : " << glewGetErrorString(init_glew) << std::endl;
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Initialize Glew : SUCCESS" << std::endl;
    int major_version;
    int minor_version;

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version);

    std::cout << ">> OpenGL version : " << major_version << "." << minor_version << std::endl;
    glEnable(GL_DEPTH_TEST);
    //===================================================================================================================
    return true;
}

void ContextManager::Init(SDL_GLContext opengl_context, SDL_Window *window, ImGuiIO& io)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, opengl_context);
    ImGui_ImplOpenGL3_Init("#version 400");

    std::cout << ">> Initialize ImGui : SUCCESS" << std::endl;
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** DeInit ************************************************************************/
/***********************************************************************************************************************************************************************/
void ContextManager::DeInit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    std::cout << std::endl;
    std::cout << ">> Destroying ImGui context : SUCCESS" << std::endl;
}

void ContextManager::DeInit(SDL_GLContext opengl_context)
{
    std::string status_msg = ">> Destroying OpenGL Context : ";
    if(opengl_context == 0)
    {
        status_msg += "ERROR";
    }
    else
    {
        SDL_GL_DeleteContext(opengl_context);
        status_msg += "SUCCESS";
    }

    std::cout << std::endl;
    std::cout << status_msg << std::endl;
}

void ContextManager::DeInit(Sdl_manage sdl_manager)
{
    std::string status_msg = ">> Destroying SDL Window : ";
    SDL_DestroyWindow(sdl_manager.window);
    std::string sdl_error(SDL_GetError());
    status_msg += (sdl_error == "") ? "SUCCESS" : sdl_error;

    std::cout << std::endl;
    std::cout << status_msg << std::endl;

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    std::cout << std::endl;
    std::cout << ">> De-init SDL : SUCCESS" << std::endl;
}