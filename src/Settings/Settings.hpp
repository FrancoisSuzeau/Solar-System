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
        #include <SDL2/SDL_ttf.h>
        #include <iostream>
        #include <iomanip>
        #include <sstream>
        #include <string>
        #include <cstring>
        #include <vector>
        #include <cmath>
        #include <ctime>
        #include <Windows.h>
        #include <cassert>

        #include "../CelestialBody/Geometry/Square.hpp"
        #include "../Text/Text.hpp"
        #include "../Input/Input.hpp"
        #include "../Shader/Shader.hpp"
        #include "../OpenGlSketch/RenderData.hpp"

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

        typedef struct button_coord {

                float     x_left;
                float     x_right;
                float     y_up;
                float     y_down;

                int     button_type;

        } button_coord;

        typedef struct data_render {

                glm::vec3 position;
                glm::vec3 scale;

        } data_render;
        

/********************************************************************* class definition *********************************************************************/

        class Settings
        {
            
            private:

                std::vector<button_coord> m_buttons_coord;

                Square          *m_grey_rect;

                std::vector<Text*>      m_texts;
                std::vector<data_render> datas_renders;

                bool            m_mouse_button_pressed;

                int             screen_width;
                int             screen_height;

                glm::vec3            colorGrey;
                glm::vec3            colorBlack;

                void initButtonCoord();
                int checkCoordButton(Input const &input, button_coord coordinate);

                void initRender();

                void renderAllTexts(RenderData &render_data, Shader *text_shader = nullptr);

            public:
            
                Settings(TTF_Font *police);
                ~Settings();

                void displayFrameSettings(RenderData &render_data, Shader *text_shader = nullptr, Shader *square_shader = nullptr);
                int manageButton(Input const &intput);
        };


#endif