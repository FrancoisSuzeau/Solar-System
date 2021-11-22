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

                // unsigned int colorBuffer;
                unsigned int fb;
                unsigned int depth_rb;
                
                unsigned int colorBuffers[2];
                unsigned int ping_pongFBO[2];
                unsigned int ping_pong_text[2];

                float quadVertices[18];
                float tex_coord[12];

                int m_bytes_vertices_size;
                int m_bytes_coord_size;

                Shader *screenShader;
                Shader *blurShader;

                void initVertices();
                bool manageFramebuffer(int width, int height);
                void manageColorBuffer(int width, int height);
                void manageDepthBuffer(int width, int height);
                void managePinPongFBO(int width, int height);

                void drawBlur(float exposure, bool hdr, bool bloom);
                void drawScreenTexture(float exposure, bool hdr);

            public:

                Framebuffer();
                ~Framebuffer();

                bool initFramebuffer(int width, int height);
                void renderFrame(float exposure, bool hdr, bool bloom);
                void bindFramebuffer();
                void unbindFramebuffer();

                unsigned int getFB() const;

        };


#endif