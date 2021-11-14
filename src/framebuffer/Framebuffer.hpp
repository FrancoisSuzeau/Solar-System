/*
AUTHOR : SUZEAU François

DATE : 14/11/2021

MODULE : Framebuffer

NAMEFILE : Framebuffer.h

PURPOSE : header of the Framebuffer class
*/

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H


/********************************************************************* includes *********************************************************************/

        #include <GL/glew.h>

        #include <iostream>
        #include <string>
        #include <math.h>
        #include <cassert>

        #include "../Shader/Shader.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Framebuffer
        {
            
            private:

                unsigned int quadVAO, quadVBO;
                unsigned int fb_texture;
                unsigned int fb;
                unsigned int depth_rb;

                float quadVertices[18];
                float tex_coord[12];

                int m_bytes_vertices_size;
                int m_bytes_coord_size;

                Shader *screenShader;

                void initVertices();
                bool manageFramebuffer(int width, int height);

            public:

                Framebuffer();
                ~Framebuffer();

                bool initFramebuffer(int width, int height);
                void renderFrame(float exposure, bool hdr);
                void bindFramebuffer();
                void unbindFramebuffer();

                unsigned int getFB() const;

        };


#endif