/*
AUTHOR : SUZEAU François

DATE : 10/06/2021

MODULE : CelestialObject.Ring

NAMEFILE : Ring.h

PURPOSE : header of the Ring class
*/

#ifndef RING_H
#define RING_H


/********************************************************************* includes *********************************************************************/

        #include "../../Texture/Texture.hpp"
        #include "../Geometry/Disk.hpp"
        #include "../../Shader/Shader.hpp"

        #include <string>
        #include <vector>
        #include <iostream>
        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        

/********************************************************************* class definition *********************************************************************/

        class Ring: public Disk
        {

            private:

                Texture         m_texture;
                float           m_coord[12];
                int             m_bytes_coord_size;

            public:
            
                Ring(float size, std::string const texture);
                Ring();
                ~Ring();

                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *ring_shader = nullptr);
                void displayInfo(glm::mat4 &projection, glm::mat4 &modelview, bool hdr);
                void load();
                
        };


#endif