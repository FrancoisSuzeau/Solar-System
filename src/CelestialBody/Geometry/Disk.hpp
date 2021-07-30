/*
AUTHOR : SUZEAU François

DATE : 10/06/2021

MODULE : CelestialBody.Geometry

NAMEFILE : Disk.h

PURPOSE : header of the Disk class
*/

#ifndef DISK_H
#define DISK_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <GL/glew.h>
        #include <SDL2/SDL.h>
        #include <iostream>
        #include <string>
        #include <cstring>

        #include "../CelestialBody.hpp"

        

/********************************************************************* class definition *********************************************************************/

        class Disk: public CelestialBody
        {
            
            protected:

                float   m_vertices[18];
                float   m_colors[18];

                GLuint  m_vboID;
                int     m_bytes_vertices_size;
                int     m_bytes_colors_size;

                GLuint  m_vaoID;
                
            public:

                Disk(float size, std::string const vertex_shader, std::string const frag_shader);
                Disk();
                ~Disk();

                void load();
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr);
                
                void updateVBO(void *data, int size_bytes, int offset);
                
        };


#endif