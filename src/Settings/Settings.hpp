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

        
        #include "../Texture/Texture.hpp"
        #include "../CelestialBody/Geometry/Square.hpp"
        #include "../Text/Text.hpp"
        #include "../Input/Input.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Settings
        {
            
            private:

                Square          m_grey_rect;
                Square          m_black_rect;

                Text            m_titre;
                Text            m_quit;

                glm::vec3       m_quit_pos;

            public:
            
                Settings();
                ~Settings();

                void displayFrameSettings(glm::mat4 &projection, glm::mat4 &modelview, bool hdr);
                bool quitSimulation(Input const &intput);
        };


#endif