/*
AUTHOR : SUZEAU François

DATE : 29/06/2021

MODULE : CelestialBody.Geometry

NAMEFILE : Square.h

PURPOSE : header of the Square class
*/

#ifndef SQUARE_H
#define SQUARE_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <GL/glew.h>
        #include <SDL2/SDL.h>
        #include <iostream>
        #include <string>
        #include <cstring>

/********************************************************************* class definition *********************************************************************/

        class Square
        {
            
            private:

                float       m_real_size;
                float       m_size;
                
                float   m_vertices[18];
                float   m_colors[18];

                GLuint  m_vboID;
                int     m_bytes_vertices_size;
                int     m_bytes_colors_size;

                GLuint  m_vaoID;

                glm::mat4 m_model_mat;
                
            public:

                Square(float size, float const color);
                Square();
                ~Square();

                // void load();
                // void display(RenderData &render_data, glm::vec3 color);
                // void drawLoad(int count, RenderData &render_data, glm::vec3 color);

                // void updatePosition(glm::vec3 position);
                
                // void updateVBO(void *data, int size_bytes, int offset);
                
        };


#endif