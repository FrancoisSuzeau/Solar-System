/*
AUTHOR : SUZEAU François

DATE : 05/07/2021

MODULE : Atmosphere

NAMEFILE : Atmosphere.h

PURPOSE : header of the Atmosphere class
*/

#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H


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

        #include "../CelestialBody/Geometry/Sphere.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Atmosphere
        {
            
            private:

                glm::vec3       m_color_atmo;

                Sphere                          *sphere_atmosphere;
                float                           m_size;
                std::string                     name_planete_host;

            public:
            
                Atmosphere(float size, std::string const name);
                Atmosphere();
                ~Atmosphere();

                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *atmo_shader = nullptr, Shader *ring_shader = nullptr);
        };


#endif