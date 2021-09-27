/*
AUTHOR : SUZEAU François

DATE : 11/07/2021

MODULE : Atmosphere

NAMEFILE : StarAtmosphere.h

PURPOSE : header of the StarAtmosphere class
*/

#ifndef SUNATMO_H
#define SUNATMO_H


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
        #include "../CelestialBody/Geometry/Disk.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class StarAtmosphere: public Disk
        {
            
            private:

                Texture         m_texture;
                float           m_coord[12];
                int             m_bytes_coord_size;
                glm::vec3       m_color_atmo;

                Shader          *m_shader_sun;

            public:
            
                StarAtmosphere(float size, std::string const name, std::string const texture);
                StarAtmosphere();
                ~StarAtmosphere();

                void display(glm::mat4 &projection, glm::mat4 &modelview, float phi, float theta, glm::vec3 &camPosUpd, glm::mat4 &light_src, glm::vec3 &camPos, Shader *star_atmo_shader = nullptr, Shader *ring_shader = nullptr);
                void displaySunAtmo(glm::mat4 &projection, glm::mat4 &modelview, float phi, float theta, glm::vec3 &camPosUpd, bool hdr, Shader *atmo_shader = nullptr);
                void load();
        };


#endif