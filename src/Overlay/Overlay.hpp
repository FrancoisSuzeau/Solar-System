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
        #include <iostream>
        #include <string>
        #include <cstring>
        #include <vector>
        #include <cmath>

        
        #include "../Texture/Texture.hpp"
        #include "../CelestialBody/Geometry/Square.hpp"
        #include "../Text/Text.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Overlay
        {
            
            private:

                Square          m_grey_rect;
                Square          m_black_rect;

                Text            m_text_music;
                Text            m_move_info;
                Text            m_time_info;

            public:
            
                Overlay();
                ~Overlay();

                void displayGeneralOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr);
                void displayMusicOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr);
                void displayMoveInfoOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr);
                void displayTimeInfoOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr);
        };


#endif