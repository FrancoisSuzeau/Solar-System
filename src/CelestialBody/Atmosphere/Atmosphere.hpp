/*
AUTHOR : SUZEAU François

DATE : 02/07/2021

MODULE : CelestialObject.Atmosphere

NAMEFILE : Atmosphere.h

PURPOSE : header of the Atmosphere class
*/

#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H


/********************************************************************* includes *********************************************************************/

        #include "../../Texture/Texture.hpp"
        #include "../Geometry/Disk.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Atmosphere: public Disk
        {

            private:

                Texture         m_texture;
                float           m_coord[12];
                int             m_bytes_coord_size;
                

            public:
            
                Atmosphere(float size, std::string const texture);
                Atmosphere();
                ~Atmosphere();

                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos);
                void load();
                
        };


#endif