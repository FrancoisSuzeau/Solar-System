/*
AUTHOR : SUZEAU François

DATE : 21/07/2021

MODULE : Overlay

NAMEFILE : MusicOverlay.hpp

PURPOSE : header of the MusicOverlay class
*/

#ifndef MUSICOVERLAY_H
#define MUSICOVERLAY_H


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
        

/********************************************************************* class definition *********************************************************************/

        class MusicOverlay
        {
            
            private:

                Square          m_grey_rect;
                Square          m_black_rect;

            public:
            
                MusicOverlay();
                ~MusicOverlay();

                void display(glm::mat4 &projection, glm::mat4 &modelview);
        };


#endif