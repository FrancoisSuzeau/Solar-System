/*
AUTHOR : SUZEAU François

DATE : 11/07/2021

MODULE : CelestialBody.Geometry

NAMEFILE : Disk2.h

PURPOSE : header of the Disk2 class
*/

#ifndef DISK2_H
#define DISK2_H


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

        class Disk2: public CelestialBody
        {
            
            protected:

                float   m_vertices[18];
                float   m_colors[18];

                GLuint  m_vboID;
                int     m_bytes_vertices_size;
                int     m_bytes_colors_size;

                GLuint  m_vaoID;
                
            public:

                Disk2(float size, std::string const vertex_shader, std::string const frag_shader);
                Disk2();
                ~Disk2();

                void load();
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr);
                
                void updateVBO(void *data, int size_bytes, int offset);
                
        };


#endif