/*
AUTHOR : SUZEAU François

DATE : 02/08/2021

MODULE : Settings

NAMEFILE : Settings.hpp

PURPOSE : header of the Settings class
*/

#ifndef SETTINGS_H
#define SETTINGS_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <glm/gtc/matrix_inverse.hpp>
        #include <glm/gtx/string_cast.hpp>

        #include <GL/glew.h>
        #include <SDL2/SDL.h>
        #include <iostream>
        #include <iomanip>
        #include <sstream>
        #include <string>
        #include <cstring>
        #include <vector>
        #include <cmath>
        #include <ctime>
        #include <Windows.h>
        
        #include "../CelestialBody/Geometry/Square.hpp"
        #include "../Text/Text.hpp"
        #include "../Input/Input.hpp"

        namespace ButtonChoice
        {
                typedef enum
                {
                        NONE,
                        QUIT,
                        HDR_ON,
                        HDR_OFF,
                        EXPOSURE_DEC,
                        EXPOSURE_INC,
                        SPEED_DEC,
                        SPEED_INC,
                        MUSIC_ON,
                        MUSIC_OFF,
                        MUSIC_DEC,
                        MUSIC_INC,
                        OVERLAY_ON,
                        OVERLAY_OFF,
                        PLANETE_INFO_ON,
                        PLANETE_INFO_OFF,
                        SHOW_NAME_ON,
                        SHOW_NAME_OFF

                }Button;
        }
        

/********************************************************************* class definition *********************************************************************/

        class Settings
        {
            
            private:

                Square          m_grey_rect;
                Square          m_black_rect;

                Text            m_titre;
                Text            m_quit;
                Text            m_hdr;
                Text            m_exposure;
                Text            m_speed;
                Text            m_music_playing;
                Text            m_music_volume;
                Text            m_overlay_display;
                Text            m_info_planete;
                Text            display_name_plan;

                bool            m_mouse_button_pressed;

                int             screen_width;
                int             screen_height;

            public:
            
                Settings(TTF_Font *police);
                ~Settings();

                void displayFrameSettings(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, Shader *text_shader = nullptr, Shader *square_shader = nullptr);
                int manageButton(Input const &intput);
        };


#endif