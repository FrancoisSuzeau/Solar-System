/*
AUTHOR : SUZEAU François

DATE : 25/05/2021

NAMEFILE : Main.cpp

PURPOSE : main loop of the executable
*/

#include "ContextManager.hpp"
#include <cassert>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    Sdl_manage sdl_manager;
    SDL_GLContext opengl_context = 0;
    GLenum init_glew = 0;

    bool status = ContextManager::Init(sdl_manager);
    assert(status);
    status = ContextManager::Init(opengl_context, sdl_manager.window);
    assert(status);
    status = ContextManager::Init(init_glew, opengl_context, sdl_manager.window);
    assert(status);

    ContextManager::DeInit(opengl_context);
    ContextManager::DeInit(sdl_manager);

    // OpenGlSketch sketch("Solar System", cx, cy);

    // sketch.initImGUI();
  
    // sketch.startLoop();

    // sketch.initFrameBuffer();
    
    // sketch.mainLoop();
    
    return EXIT_SUCCESS;

}