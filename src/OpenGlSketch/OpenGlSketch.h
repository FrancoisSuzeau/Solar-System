/*
AUTHOR : SUZEAU François

DATE : 26/05/2021

MODULE : OpenGlSketch

NAMEFILE : OpenGlSketch.h

PURPOSE : header of the OpenGlSketch class
*/

#ifndef OPENGLSKETCH_H
#define OPENGLSKETCH_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <GL/glew.h>
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_mixer.h>
        #include <SDL2/SDL_ttf.h>
        #include <iostream>
        #include <string>

        
        #include "../CelestialBody/Star/Star.h"
        #include "../CelestialBody/Skybox/Skybox.h"
        #include "../CelestialBody/System/SystemCreator.h"
        #include "../CelestialBody/System/SolarSystemCreator.h"
        
        #include "../Input/Input.h"
        #include "../Audio/Audio.h"
        #include "../Camera/Camera.h"
        

/********************************************************************* class definition *********************************************************************/

        class OpenGlSketch
        {
            
            private:

                std::string     m_window_title;
                int             m_window_width;
                int             m_window_height;

                Input m_input;
                
                SDL_Window      *m_window;
                SDL_GLContext   m_openGL_context;
                GLenum          m_initiGLEW;

                


            public:

                OpenGlSketch();
                OpenGlSketch(std::string window_title, int width, int height);
                ~OpenGlSketch();

                bool    initWindow();
                bool    initGL();
                void    mainLoop();

        };


#endif