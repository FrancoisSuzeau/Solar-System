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

                static void DeInit(SDL_GLContext opengl_context);
                static void DeInit(Sdl_manage sdl_manager);
        };


#endif