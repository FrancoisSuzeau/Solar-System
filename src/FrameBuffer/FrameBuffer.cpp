/*
AUTHOR : SUZEAU François

DATE : 04/07/2021

MODULE : FrameBuffer

NAMEFILE : FrameBuffer.hpp

PURPOSE :   header of the frame buffer class
*/

#include "FrameBuffer.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
FrameBuffer::FrameBuffer(): m_id(0), m_width(0), m_height(0), m_colorBuffer(0), m_depth_buffer_id(0)
{

}

FrameBuffer::FrameBuffer(int width, int height): m_id(0), m_width(width), m_height(height), m_colorBuffer(0), m_depth_buffer_id(0)
{
    
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_id);
    glDeleteRenderbuffers(1, &m_depth_buffer_id);

    m_colorBuffer.clear();
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** createRenderBuffer ***********************************************************************/
/***********************************************************************************************************************************************************************/
void FrameBuffer::createRenderBuffer(GLuint &id, GLenum internal_format)
{
    //destroying potentiel ancient render buffer id
    if(glIsRenderbuffer(id) == GL_TRUE)
    {
        glDeleteRenderbuffers(1, &id);
    }

    //generate id
    glGenRenderbuffers(1, &id);

    //lock render buffer
    glBindRenderbuffer(GL_RENDERBUFFER, id);

        //configure render buffer
        glRenderbufferStorage(GL_RENDERBUFFER, internal_format, m_width, m_height);

    //unlock render buffer
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** loadFrameBuffer ************************************************************************/
/***********************************************************************************************************************************************************************/
bool FrameBuffer::loadFrameBuffer()
{
    //destroying potentiel ancient render buffer id
    if(glIsFramebuffer(m_id) == GL_TRUE)
    {
        glDeleteFramebuffers(1, &m_id);

        m_colorBuffer.clear();
    }

    //generate id
    glGenFramebuffers(1, &m_id);

    //lock frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

        //Creating color buffer
        Texture colorBuffer(m_width, m_height, GL_RGBA, GL_RGBA, true);
        colorBuffer.loadEmptyTexture();
        m_colorBuffer.push_back(colorBuffer);

        //creating detph and stencil buffer
        createRenderBuffer(m_depth_buffer_id, GL_DEPTH24_STENCIL8);

        //associate color buffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorBuffer[0].getID(), 0);

        //associate Depth and stencil buffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depth_buffer_id);

        //checking FBO integrity
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            //free buffers
            glDeleteFramebuffers(1, &m_id);
            glDeleteRenderbuffers(1, &m_depth_buffer_id);

            m_colorBuffer.clear();

            std::cout << ">> Frame buffer construct : ERROR" << std::endl;

            return false;
        }

    //unlock frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** getters ****************************************************************************/
/***********************************************************************************************************************************************************************/
GLuint FrameBuffer::getId() const
{
    return m_id;
}

GLuint FrameBuffer::getColorBufferId(unsigned int index) const
{
    return m_colorBuffer[index].getID();
}

int FrameBuffer::getWidth() const
{
    return m_width;
}

int FrameBuffer::getHeight() const
{
    return m_height;
}