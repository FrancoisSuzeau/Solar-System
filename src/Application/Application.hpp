/*
AUTHOR : SUZEAU François

DATE : 26/05/2021

MODULE : Application

NAMEFILE : Application.hpp

PURPOSE : header of the Application class
*/

#ifndef APPLICATION_H
#define APPLICATION_H


/********************************************************************* preprocessing *********************************************************************/
        
        #include <SDL2/SDL.h>

        #include <iostream>
        
        #include "DataManager.hpp"
        #include "../InOut/Input/Input.hpp"
        #include "Settings/Settings.hpp"

        #define BEGIN   0
        #define END     1
        

/********************************************************************* class definition *********************************************************************/

        class Application
        {
            
            private:

                // Input           m_input;
                // Audio           *aud;
                // Camera	*camera;
                // std::vector<TTF_Font*>  m_police;
                // SystemCreator   *solar_system;
                // Framebuffer     *m_framebuffer;
                // Spaceship *ship;
                // bool speed_key_pressed;
                // bool info_key_pressed;
                // Settings *m_settings;
                // Overlay *m_overlay;
                // ParticuleManager *m_particule_manager;
                // bool is_moving;

                DataManager             m_data_manager;
                Input                   *m_input;
                Settings                m_setting;
                SDL_Window              *m_window;

                bool menu_app_key_pressed;
                bool render_menu;

                unsigned int frame_rate;
                Uint32 start_loop, end_loop, time_past;

                void    inputProcess();
                void    fpsCalculation(int moment);

                void    renderSettings();
                

            public:

                Application(int width, int height, SDL_Window *window, Input *input);
                ~Application();

                void    mainLoop();
                
                // void    initFrameBuffer();
                // void    startLoop();
                // void    renderScene(RenderData &render_data);
                // void    renderInfo(RenderData &render_data);
                // void    renderOverlay(RenderData &render_data);
                // void    renderParticles(RenderData &render_data);

                

        };


#endif