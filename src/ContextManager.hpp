/*
AUTHOR : SUZEAU François

DATE : 04/03/2022

MODULE : ContextManager

NAMEFILE : ContextManager.hpp

PURPOSE : header of the ContextManager class
*/

#ifndef CONTEXT_H
#define CONTEXT_H


/********************************************************************* includes *********************************************************************/

        #include <GL/glew.h>

        #include <SDL2/SDL.h>
        #include <SDL2/SDL_mixer.h>
        #include <SDL2/SDL_ttf.h>

        #include <iostream>
        #include <string>
        #include <windows.h>

        #define  IMGUI_INITIALIZE 0
        #if defined(IMGUI_IMPL_OPENGL_ES2)
        #include <SDL_opengles2.h>
        #else
        #include <SDL2/SDL_opengl.h>
        #endif
        #include "../lib/imgui/imgui.h"
        #include "../lib/imgui/imgui_impl_sdl.h"
        #include "../lib/imgui/imgui_impl_opengl3.h"

        #include "ErrorHandler/ErrorHandler.hpp"
        

/********************************************************************* class definition *********************************************************************/

        typedef struct Sdl_manage {

                SDL_Window      *window = NULL;
                std::string     title;
                int             win_width;
                int             win_height;

        } Sdl_manage;

        class ContextManager
        {
            
            private:

                //This class cannot be instanced
                ContextManager();
                ~ContextManager();

            public:

                static bool Init(Sdl_manage &sdl_manager);
                static bool Init(SDL_GLContext &opengl_context, SDL_Window *window);
                static bool Init(GLenum init_glew, SDL_GLContext gl_context, SDL_Window *window);
                static void Init(SDL_GLContext opengl_context, SDL_Window *window, ImGuiIO& io);

                static void DeInit();
                static void DeInit(SDL_GLContext opengl_context);
                static void DeInit(Sdl_manage sdl_manager);
                
        };


#endif