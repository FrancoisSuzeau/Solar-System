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
        #include "../OpenGlSketch/RenderData.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Framebuffer
        {
            
            private:

                unsigned int quadVAO, quadVBO;
                
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

                void drawBlur(RenderData &render_data, bool &horizontal);
                void drawScreenTexture(RenderData &render_data, bool &horizontal);

            public:

                Framebuffer();
                ~Framebuffer();

                bool initFramebuffer(int width, int height);
                void renderFrame(RenderData &render_data);
                void bindFramebuffer();
                void unbindFramebuffer();

                unsigned int getFB() const;

        };


#endif