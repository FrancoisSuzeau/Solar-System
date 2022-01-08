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
        #include <iostream>
        #include <iomanip>
        #include <sstream>
        #include <string>
        #include <cstring>
        #include <vector>
        #include <cmath>
        #include <ctime>
        #include <cassert>

        #if defined(IMGUI_IMPL_OPENGL_ES2)
        #include <SDL_opengles2.h>
        #else
        #include <SDL2/SDL_opengl.h>
        #endif

        #include "../CelestialBody/Geometry/Square.hpp"
        #include "../Text/Text.hpp"
        #include "../OpenGlSketch/RenderData.hpp"

        #include "../../lib/imgui/imgui.h"
        #include "../../lib/imgui/imgui_impl_sdl.h"
        #include "../../lib/imgui/imgui_impl_opengl3.h"
        

/********************************************************************* class definition *********************************************************************/

        class Overlay
        {
            
            private:

                Square          m_rect;
                std::vector<Text*> m_texts;

                std::string     m_ancient_track;
                float           m_ancient_radius;
                float           m_ancient_speed;

                glm::vec3 m_colorBlack;
                glm::vec3 m_colorGrey;

                void displaySquares(RenderData &render_data, std::vector<glm::vec3> coordinates);

            public:
            
                Overlay(TTF_Font *police);
                ~Overlay();

                void displayGeneralOverlay(RenderData &render_data);
                void displayMusicOverlay(RenderData &render_data, std::string const track);
                void displayMoveInfoOverlay(RenderData &render_data, glm::vec3 &position, float const speed);
                void displayAppInfo(RenderData &render_data);

                void setMusicInformation(std::string const track);
                void setSpeedInformation(float const speed);
        };


#endif