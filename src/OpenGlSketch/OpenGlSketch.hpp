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
        #include "../Overlay/Overlay.hpp"

        #include "../Shader/Shader.hpp"

        #include "../Settings/Settings.hpp"
        #include "../Particule/Particule.hpp"
        

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

                mat4 projection;
                mat4 model_view;
                mat4 save_model_view;
                
                SDL_Window      *m_window;
                SDL_GLContext   m_openGL_context;
                GLenum          m_initiGLEW;
                std::vector<TTF_Font*>  m_police;

                SystemCreator   *solar_system;

                unsigned int quadVAO, quadVBO;
                unsigned int fb_texture;
                unsigned int fb;
                unsigned int depth_rb;

                Shader *screenShader;
                Shader *text_shader;
                Shader *square_shader;

                bool hdr;
                bool hdr_key_pressed;
                float exposure;

                bool pause_music;
                bool speed_key_pressed;
                int volume;

                Settings *m_settings;
                bool menu;
                bool menu_app_key_pressed;

                bool info_render;
                bool info_render_key_pressed;

                unsigned int frame_rate;
                Uint32 start_loop, end_loop, time_past;

                bool m_terminate;

                bool m_overlay_display;
                bool m_name_display;



                // unsigned int colorBuffers[2];
                // unsigned int rboDepth;
                // unsigned int pingpongFBO[2];
                // unsigned int pingpongColorbuffers[2];
                // Shader *shaderBlur;

                Overlay *m_overlay;

                Particule *m_particuleGenerator;

                bool is_moving;
                

            public:

                OpenGlSketch();
                OpenGlSketch(std::string window_title, int width, int height);
                ~OpenGlSketch();

                bool    initWindow();
                bool    initGL();
                void    mainLoop();
                void    startLoop();
                void    windowProcess();
                void    renderScene();
                void    renderInfo();
                void    renderOverlay();
                void    renderParticles();

                void initFrameBuffer();
                void renderSettings();

        };


#endif