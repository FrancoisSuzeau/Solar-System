/*
AUTHOR : SUZEAU François

DATE : 04/07/2021

MODULE : FrameBuffer

NAMEFILE : FrameBuffer.hpp

PURPOSE : header of the FrameBuffer class
*/

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H


/********************************************************************* includes *********************************************************************/
        
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_image.h>
        #include <iostream>
        #include <string>
        #include <vector>

        #include <GL/glew.h>

        #include "../Texture/Texture.hpp"

/********************************************************************* class definition *********************************************************************/

        class FrameBuffer
        {
            
            private:

                GLuint                  m_id;
                float                   m_width;
                float                   m_height;

                std::vector<Texture>    m_colorBuffer;
                GLuint                  m_depth_buffer_id;

                
            public:

                FrameBuffer();
                FrameBuffer(int width, int height);
                ~FrameBuffer();

                void createRenderBuffer(GLuint &id, GLenum internal_format);
                bool loadFrameBuffer();

                GLuint getId() const;
                GLuint getColorBufferId(unsigned int index) const;

                int getWidth() const;
                int getHeight() const;
                
        };


#endif