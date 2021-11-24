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
        #include <cassert>

        #include "../CelestialBody/Geometry/Square.hpp"
        #include "../Text/Text.hpp"
        #include "../Shader/Shader.hpp"
        #include "../OpenGlSketch/RenderData.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Overlay
        {
            
            private:

                Square          m_rect;
                std::vector<Text*> m_texts;

                std::string     m_ancient_track;
                float           m_ancient_radius;
                float           m_ancient_speed;
                std::string     m_ancient_time;
                int             m_sec;

                glm::vec3 m_colorBlack;
                glm::vec3 m_colorGrey;

                void displaySquares(RenderData &render_data, std::vector<glm::vec3> coordinates, Shader *square_shader = nullptr);

            public:
            
                Overlay(TTF_Font *police);
                ~Overlay();

                void displayGeneralOverlay(RenderData &render_data, Shader *square_shader = nullptr);
                void displayMusicOverlay(RenderData &render_data, std::string const track, Shader *text_shader = nullptr, Shader *square_shader = nullptr);
                void displayMoveInfoOverlay(glm::mat4 &projection, glm::mat4 &view, bool hdr, glm::vec3 &position, float const speed, Shader *text_shader = nullptr, Shader *square_shader = nullptr);
                void displayTimeInfoOverlay(glm::mat4 &projection, glm::mat4 &view, bool hdr, Shader *text_shader = nullptr, Shader *square_shader = nullptr);

                void setMusicInformation(std::string const track);
                void setSpeedInformation(float const speed);
                void setTimeInformation();
        };


#endif