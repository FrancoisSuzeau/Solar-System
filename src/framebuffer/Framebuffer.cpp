/*
AUTHOR : SUZEAU François

DATE : 14/11/2021

MODULE : Framebuffer

NAMEFILE : Framebuffer.h

PURPOSE :   
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Framebuffer.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Framebuffer::Framebuffer()
{

}

Framebuffer::~Framebuffer()
{
    if(screenShader != nullptr)
    {
        delete screenShader;
    }

    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteFramebuffers(1, &fb);
    glDeleteRenderbuffers(1, &depth_rb);
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** initFramebuffer *******************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::initFramebuffer(int width, int height)
{
    float quadVertices[] = {-1.0f, -1.0f, -1.0f,   1.0f, -1.0f, -1.0f,   1.0f, 1.0f, -1.0f,   
                        -1.0f, -1.0f, -1.0f,   -1.0f, 1.0f, -1.0f,   1.0f, 1.0f, -1.0f   

    };

    float temp_coord[] = {0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
                          0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f
                          
                          };

    int m_bytes_vertices_size = 18 * sizeof(float);
    int m_bytes_coord_size = 12 * sizeof(float);

    /************************************************* VBO management ********************************************************/
    //destroy a possible ancient VBO
    if(glIsBuffer(quadVBO) == GL_TRUE)
    {
        glDeleteBuffers(1, &quadVBO);
    }

    //generate Vertex Buffer Object ID
    glGenBuffers(1, &quadVBO);

    //lock VBO
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

        //memory allocation
        glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_coord_size, 0, GL_DYNAMIC_DRAW);
        /*
            - GL_STATIC_DRAW : data with few updating
            - GL_DYNAMIC_DRAW : data with frequently updating (many times per second but not each frame
            - GL_STREAM_DRAW : data with each frame updating
        there is 6 other possible values
        */

       //vertices transfert$
       glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, quadVertices);
       glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_coord_size, temp_coord);

       //unlock VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //===================================================================================================================

    /************************************************* VAO management ********************************************************/
    //destroy a possible ancient VAO
    if(glIsVertexArray(quadVAO) == GL_TRUE)
    {
        glDeleteVertexArrays(1, &quadVAO);
    }
    //generate Vertex Array Object ID
    glGenVertexArrays(1, &quadVAO);

    //lock VAO
    glBindVertexArray(quadVAO);

        //lock VBO
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

        //acces to the vertices in video memory
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);

        //acces to the colors in video memory
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));
        glEnableVertexAttribArray(2);

        //unlock VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    //unlock VAO
    glBindVertexArray(0);
    //===================================================================================================================

    /************************************************* Framebuffer management ********************************************************/
    
    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);

    //ONLY HDR THAT WORKS !
    // Create a texture to render to
    glGenTextures(1, &fb_texture);

    glBindTexture(GL_TEXTURE_2D, fb_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // NULL means reserve texture memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    // Attach the texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb_texture, 0);

    glGenRenderbuffers(1, &depth_rb);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_rb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_rb);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //===================================================================================================================


    screenShader = new Shader("../src/Shader/Shaders/screenShader.vert", "../src/Shader/Shaders/screenShader.frag");
    assert(screenShader);

    assert(screenShader->loadShader());

}

/***********************************************************************************************************************************************************************/
/*********************************************************************** renderFrame ***********************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::renderFrame(float exposure, bool hdr)
{
    if(screenShader != nullptr)
    {
        glUseProgram(screenShader->getProgramID());

            glBindVertexArray(quadVAO);

                screenShader->setTexture("screenTexture", 0);
                screenShader->setFloat("exposure", exposure);
                screenShader->setInt("hdr", hdr);

                glBindTexture(GL_TEXTURE_2D, fb_texture);	// use the color attachment texture as the texture of the quad plane
                glDrawArrays(GL_TRIANGLES, 0, 6);

                glBindTexture(GL_TEXTURE_2D, 0);

            glBindVertexArray(0);
        glUseProgram(0);
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** getter ****************************************************************************************/
/***********************************************************************************************************************************************************************/
unsigned int Framebuffer::getFB() const
{
    return fb;
}