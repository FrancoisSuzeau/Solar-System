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
        #include <math.h>
        #include <cassert>

        #if defined(IMGUI_IMPL_OPENGL_ES2)
        #include <SDL_opengles2.h>
        #else
        #include <SDL2/SDL_opengl.h>
        #endif

        #include "RenderData.hpp"
        
        #include "../CelestialBody/System/SystemCreator.hpp"
        #include "../CelestialBody/System/SolarSystemCreator.hpp"
        
        #include "../Input/Input.hpp"
        #include "../Audio/Audio.hpp"
        #include "../Camera/Camera.hpp"
        #include "../StartScreen/StartScreen.hpp"

        #include "../CelestialBody/Geometry/Square.hpp"
        #include "../Overlay/Overlay.hpp"

        #include "../Settings/Settings.hpp"
        #include "../Particule/Particule.hpp"

        #include "../Spaceship/Spaceship.hpp"
        #include "../Framebuffer/Framebuffer.hpp"

        #include "../Saving/Saving.hpp"

        #include "../../lib/imgui/imgui.h"
        #include "../../lib/imgui/imgui_impl_sdl.h"
        #include "../../lib/imgui/imgui_impl_opengl3.h"

        #include "../LensFlare/FlareManager.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class OpenGlSketch
        {
            
            private:

                std::string     m_window_title;
                int             m_window_width;
                int             m_window_height;

                Input           m_input;
                Audio           *aud;

                Camera	*camera;
                
                SDL_Window      *m_window;
                SDL_GLContext   m_openGL_context;
                GLenum          m_initiGLEW;
                std::vector<TTF_Font*>  m_police;

                SystemCreator   *solar_system;

                Framebuffer     *m_framebuffer;

                Spaceship *ship;

                bool speed_key_pressed;
                bool info_key_pressed;

                Settings *m_settings;

                bool menu_app_key_pressed;

                Overlay *m_overlay;

                // Particule *m_particuleGenerator;

                bool is_moving;
                

            public:

                OpenGlSketch();
                OpenGlSketch(std::string window_title, int width, int height);
                ~OpenGlSketch();

                bool    initWindow();
                bool    initGL();
                void    initImGUI();
                void    initFrameBuffer();

                void    mainLoop();
                void    startLoop();
                void    windowProcess(RenderData &render_data);
                void    renderScene(RenderData &render_data);
                void    renderInfo(RenderData &render_data);
                void    renderOverlay(RenderData &render_data);
                void    renderParticles();

                void renderSettings(RenderData &render_data);

        };


#endif