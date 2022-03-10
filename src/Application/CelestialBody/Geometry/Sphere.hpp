/*
AUTHOR : SUZEAU François

DATE : 06/06/2021

MODULE : Forme.Sphere

NAMEFILE : Sphere.h

PURPOSE : header of the Sphere class
*/

#ifndef SPHERE_H
#define SPHERE_H


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

        #include "../CelestialBody.hpp"
        #include "../../OpenGlSketch/RenderData.hpp"

        

/********************************************************************* class definition *********************************************************************/

        class Sphere: public CelestialBody
        {
            
            protected:

                GLuint                          m_vbo;
                GLuint                          m_ibo;
                GLsizei                         m_element_count;
                unsigned int                    m_vertCount;
                GLushort                        *m_tris;
                float                           m_radius;
 
                
            public:

                Sphere(const float radius, const unsigned int longSegs, const unsigned int latSegs);

                Sphere();
                ~Sphere();
                void display(RenderData &render_data) override;
        };


#endif