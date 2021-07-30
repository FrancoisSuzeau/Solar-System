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

        
        
        #include "../CelestialBody/System/SystemCreator.hpp"
        #include "../CelestialBody/System/SolarSystemCreator.hpp"
        
        #include "../Input/Input.hpp"
        #include "../Audio/Audio.hpp"
        #include "../Camera/Camera.hpp"
        #include "../StartScreen/StartScreen.hpp"

        #include "../CelestialBody/Geometry/Square.hpp"
        //#include "../MusicOverlay/MusicOverlay.hpp"

        #include "../Shader/Shader.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class OpenGlSketch
        {
            
            private:

                std::string     m_window_title;
                int             m_window_width;
                int             m_window_height;

                Input           m_input;
                Audio           *aud;
                
                SDL_Window      *m_window;
                SDL_GLContext   m_openGL_context;
                GLenum          m_initiGLEW;

                SystemCreator   *solar_system;

                unsigned int quadVAO, quadVBO;
                unsigned int fb_texture;
                unsigned int fb;
                unsigned int depth_rb;

                Shader *screenShader;

                // unsigned int colorBuffers[2];
                // unsigned int rboDepth;
                // unsigned int pingpongFBO[2];
                // unsigned int pingpongColorbuffers[2];
                // Shader *shaderBlur;
                

            public:

                OpenGlSketch();
                OpenGlSketch(std::string window_title, int width, int height);
                ~OpenGlSketch();

                bool    initWindow();
                bool    initGL();
                void    mainLoop();
                void    startLoop();

                void initFrameBuffer();

        };


#endif