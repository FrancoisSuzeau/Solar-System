/*
AUTHOR : SUZEAU François

DATE : 21/07/2021

MODULE : Overlay

NAMEFILE : Overlay.hpp

PURPOSE : header of the Overlay class
*/

#ifndef OVERLAY_H
#define OVERLAY_H


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

        #include "../CelestialBody/Geometry/Square.hpp"
        #include "../Text/Text.hpp"
        #include "../Shader/Shader.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Overlay
        {
            
            private:

                Square          m_grey_rect;
                Square          m_black_rect;

                Text            m_track_music;
                Text            m_Author_music;
                Text            m_studio_music;

                
                Text            m_move_info;
                Text            m_position;
                Text            m_speed_info;
                Text            m_speed;


                Text            m_time_info;

                std::string     m_ancient_track;
                float           m_ancient_radius;
                float           m_ancient_speed;
                std::string     m_ancient_time;
                int             m_sec;

            public:
            
                Overlay(TTF_Font *police);
                ~Overlay();

                void displayGeneralOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, Shader *square_shader = nullptr);
                void displayMusicOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, std::string const track, Shader *text_shader = nullptr, Shader *square_shader = nullptr);
                void displayMoveInfoOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, glm::vec3 &position, float const speed, Shader *text_shader = nullptr, Shader *square_shader = nullptr);
                void displayTimeInfoOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, Shader *text_shader = nullptr, Shader *square_shader = nullptr);

                void setMusicInformation(std::string const track);
                void setSpeedInformation(float const speed);
                void setTimeInformation();
        };


#endif