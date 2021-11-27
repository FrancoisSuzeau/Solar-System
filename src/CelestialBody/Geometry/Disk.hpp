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
        #include "../../Shader/Shader.hpp"

        

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

                Disk(float size);
                Disk();
                ~Disk();

                void load();
                void display(RenderData &render_data, glm::vec3 &camPos, Shader *disk_shader = nullptr, Shader *ring_shader = nullptr);
        };


#endif