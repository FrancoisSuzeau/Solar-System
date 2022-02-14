/*
AUTHOR : SUZEAU François

DATE : 27/09/2021

MODULE : Particule

NAMEFILE : Particule.hpp

PURPOSE : header of the Particule class
*/

#ifndef PARTICULE_H
#define PARTICULE_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <glm/gtc/matrix_inverse.hpp>
        #include <glm/gtx/string_cast.hpp>

        #include <iostream>
        #include <string>
        #include <math.h>
        #include <Windows.h>
        #include <cassert>
        
        #include "../OpenGlSketch/RenderData.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Particule
        {
            
            private:

                
                GLuint                          m_vbo;
                GLuint                          m_ibo;
                GLsizei                         m_element_count;
                unsigned int                    m_vertCount;
                GLushort                        *m_tris;
                float                           m_radius;

                glm::mat4                       transform_mat;
                glm::vec3                       position;
                glm::vec3                       scale;


            public:
            
                Particule(const float radius, const unsigned int longSegs, const unsigned int latSegs);
                ~Particule();

                void setPositionParticule(glm::vec3 new_pos);
                void transformMat();
                void renderParticule(RenderData &render_data);

        };


#endif