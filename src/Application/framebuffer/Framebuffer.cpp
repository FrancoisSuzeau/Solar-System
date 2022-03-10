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
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteFramebuffers(1, &fb);
    glDeleteFramebuffers(2, ping_pongFBO);
    glDeleteRenderbuffers(1, &depth_rb);
    glDeleteTextures(2, colorBuffers);
    glDeleteTextures(2, ping_pong_text);

    if((glIsRenderbuffer(depth_rb) == GL_FALSE) && 
    (glIsFramebuffer(fb) == GL_FALSE) &&
    (glIsFramebuffer(ping_pongFBO[0]) == GL_FALSE) &&
    (glIsFramebuffer(ping_pongFBO[1]) == GL_FALSE) &&
    (glIsTexture(colorBuffers[0]) == GL_FALSE) &&
    (glIsTexture(colorBuffers[1]) == GL_FALSE) &&
    (glIsTexture(ping_pong_text[0]) == GL_FALSE) &&
    (glIsTexture(ping_pong_text[1]) == GL_FALSE) &&
    (glIsBuffer(quadVBO) == GL_FALSE) && 
    (glIsVertexArray(quadVAO) == GL_FALSE))
    {
        std::cout << "FRAMEBUFFER :: delete >>> SUCESS" << std::endl;
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** initVertices **********************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::initVertices()
{
    float vertices[] = {-1.0f, -1.0f, -1.0f,   1.0f, -1.0f, -1.0f,   1.0f, 1.0f, -1.0f,   
                        -1.0f, -1.0f, -1.0f,   -1.0f, 1.0f, -1.0f,   1.0f, 1.0f, -1.0f   
    };

    float coord[] = {0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
                          0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f
                          };

    m_bytes_vertices_size = 18 * sizeof(float);
    m_bytes_coord_size = 12 * sizeof(float);

    for (int i = 0; i < 18; i++)
    {
        quadVertices[i] = vertices[i];
    }

    for (int i = 0; i < 12; i++)
    {
        tex_coord[i] = coord[i];
    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** initFramebuffer *******************************************************************************/
/***********************************************************************************************************************************************************************/
bool Framebuffer::initFramebuffer(int width, int height)
{
    this->initVertices();

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
        glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_coord_size, 0, GL_STATIC_DRAW);
        /*
            - GL_STATIC_DRAW : data with few updating
            - GL_DYNAMIC_DRAW : data with frequently updating (many times per second but not each frame
            - GL_STREAM_DRAW : data with each frame updating
        there is 6 other possible values
        */

       //vertices transfert$
       glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, quadVertices);
       glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_coord_size, tex_coord);

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

    return this->manageFramebuffer(width, height);
}

/***********************************************************************************************************************************************************************/
/****************************************************************** manageColorBuffer **********************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::manageColorBuffer(int width, int height)
{   
    glGenTextures(2, colorBuffers);
    for(unsigned int i = 0; i < 2; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    
}

/***********************************************************************************************************************************************************************/
/****************************************************************** manageDepthBuffer **********************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::manageDepthBuffer(int width, int height)
{
    glGenRenderbuffers(1, &depth_rb);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_rb);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_rb);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // Tell OpenGL we need to draw to both attachments
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
}

/***********************************************************************************************************************************************************************/
/****************************************************************** managePingPongFBO **********************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::managePinPongFBO(int width, int height)
{
    glGenFramebuffers(2, ping_pongFBO);
	glGenTextures(2, ping_pong_text);
    for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ping_pongFBO[i]);

        glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, ping_pong_text[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ping_pong_text[i], 0);

		auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "ERROR::FRAMEBUFFER:: Ping Pong framebuffer is not complete >> " << fboStatus << std::endl;
        }
        std::cout << "FRAMEBUFFER:: Ping Pong Framebuffer is complete!" << std::endl;
    
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
}

/***********************************************************************************************************************************************************************/
/****************************************************************** manageFramebuffer **********************************************************************************/
/***********************************************************************************************************************************************************************/
bool Framebuffer::manageFramebuffer(int width, int height)
{
    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);

        this->manageColorBuffer(width, height);
        this->manageDepthBuffer(width, height);

        auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        
        if (status != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete >> " << status << std::endl;
            return false;
        }

        std::cout << "FRAMEBUFFER:: Framebuffer is complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    this->managePinPongFBO(width, height);

    //===================================================================================================================

    return true;
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** renderFrame ***********************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::renderFrame(RenderData &render_data)
{
    bool horizontal = true;
    this->drawBlur(render_data, horizontal);
    this->drawScreenTexture(render_data, horizontal);
}

/***********************************************************************************************************************************************************************/
/************************************************************************* drawBlur ************************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::drawBlur(RenderData &render_data, bool &horizontal)
{
    bool first_it = true;
    
    unsigned int amount = render_data.getBloomStr();

        glUseProgram(render_data.getShader("blur")->getProgramID());

        if(render_data.getBloom())
        {
            for (unsigned int i = 0; i < amount; i++)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, ping_pongFBO[horizontal]);
                
                render_data.getShader("blur")->setInt("horizontal", horizontal);
                render_data.getShader("blur")->setTexture("screenTexture", 0);

                if(first_it)
                {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, colorBuffers[1]);
                    first_it = false;
                }
                else
                {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, ping_pong_text[!horizontal]);
                }
                glBindVertexArray(quadVAO);

                    glDrawArrays(GL_TRIANGLES, 0, 6);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    

                glBindVertexArray(0);
                
                horizontal = !horizontal;
                
            }
        }

        

    glUseProgram(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

/***********************************************************************************************************************************************************************/
/**************************************************************** drawScreenTexture ************************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::drawScreenTexture(RenderData &render_data, bool &horizontal)
{
    if(render_data.getShader("screen") != nullptr)
    {
        glUseProgram(render_data.getShader("screen")->getProgramID());

            render_data.getShader("screen")->setFloat("exposure", render_data.getExposure());
            render_data.getShader("screen")->setInt("hdr", render_data.getHDR());
            render_data.getShader("screen")->setInt("bloom", render_data.getBloom());

            render_data.getShader("screen")->setTexture("screenTexture", 0);
            render_data.getShader("screen")->setTexture("bloomTexture", 1);
            render_data.getShader("screen")->setFloat("gamma", 2.2);

            glBindVertexArray(quadVAO);
                
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);

                if(render_data.getBloom())
                {
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, ping_pong_text[!horizontal]);
                }  
                
                glDrawArrays(GL_TRIANGLES, 0, 6);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, 0);

                if(render_data.getBloom())
                {
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, 0);
                }

            glBindVertexArray(0);

            
        glUseProgram(0);
    }
}

/***********************************************************************************************************************************************************************/
/****************************************************************** bindFramebuffer ************************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::bindFramebuffer()
{

    glBindFramebuffer(GL_FRAMEBUFFER, this->getFB());

    //make sure we clear the framebuffer's content
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //cleaning the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
}

/***********************************************************************************************************************************************************************/
/**************************************************************** unbindFramebuffer ************************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::unbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //make sure we clear the framebuffer's content
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** getter ****************************************************************************************/
/***********************************************************************************************************************************************************************/
unsigned int Framebuffer::getFB() const
{
    return fb;
}