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

                Shader *screenShader;

                

            public:

                Framebuffer();
                ~Framebuffer();

                void initFramebuffer(int width, int height);

                unsigned int getFB() const;

                void renderFrame(float exposure, bool hdr);

        };


#endif