/*
AUTHOR : SUZEAU François

DATE : 06/06/2021

MODULE : Objects::BasicObjects

NAMEFILE : Sphere.hpp

PURPOSE : header of the Sphere class
*/

#ifndef SPHERE_H
#define SPHERE_H


/********************************************************************* includes *********************************************************************/

        #include "../Object.hpp"

/********************************************************************* class definition *********************************************************************/

        class Sphere: public Object
        {
            
            protected:

                // GLuint                          m_vbo;
                // GLuint                          m_ibo;
                // GLsizei                         m_element_count;
                // unsigned int                    m_vertCount;
                // GLushort                        *m_tris;
                // float                           m_radius;
 
                
            public:

                Sphere(float size);
                ~Sphere();

                void transform() override;
        };


#endif