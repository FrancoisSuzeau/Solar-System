/*
AUTHOR : SUZEAU François

DATE : 25/05/2021

NAMEFILE : Main.cpp

PURPOSE : 
*/

#include "ContextManager.hpp"
#include "Application/Application.hpp"
#include <cassert>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    Sdl_manage sdl_manager;
    SDL_GLContext opengl_context = 0;
    GLenum init_glew = 0;
    ImGuiIO io;
    bool status;

    status = ContextManager::Init(sdl_manager);
    assert(status);
    status = ContextManager::Init(opengl_context, sdl_manager.window);
    assert(status);
    status = ContextManager::Init(init_glew, opengl_context, sdl_manager.window);
    assert(status);
    ContextManager::Init(opengl_context, sdl_manager.window, io);

    Input *input = new Input();
    assert(input);
    Audio *audio = new Audio();
    assert(audio);
    
    Application scene(sdl_manager.win_width, sdl_manager.win_height, sdl_manager.window, input, audio);

    scene.loadAssets();
    scene.mainLoop();

    delete input;
    input = nullptr;
    delete audio;
    audio = nullptr;

    ContextManager::DeInit();
    ContextManager::DeInit(opengl_context);
    ContextManager::DeInit(sdl_manager);
    
    return EXIT_SUCCESS;

}