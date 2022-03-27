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
    
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** clean **********************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::clean()
{
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteFramebuffers(1, &color_fb_id);
    // glDeleteFramebuffers(2, ping_pongFBO);
    glDeleteRenderbuffers(1, &render_buffer_id);
    // glDeleteTextures(2, colorBuffers);
    // glDeleteTextures(2, ping_pong_text);

    if((glIsRenderbuffer(render_buffer_id) == GL_FALSE) && 
    (glIsFramebuffer(color_fb_id) == GL_FALSE) &&
    /*(glIsFramebuffer(ping_pongFBO[0]) == GL_FALSE) &&
    (glIsFramebuffer(ping_pongFBO[1]) == GL_FALSE) &&
    (glIsTexture(colorBuffers[0]) == GL_FALSE) &&
    (glIsTexture(colorBuffers[1]) == GL_FALSE) &&
    (glIsTexture(ping_pong_text[0]) == GL_FALSE) &&
    (glIsTexture(ping_pong_text[1]) == GL_FALSE) &&*/
    (glIsBuffer(quadVBO) == GL_FALSE) && 
    (glIsVertexArray(quadVAO) == GL_FALSE))
    {
        std::cout << ">> FRAMEBUFFER : DESTROY COMPLETE" << std::endl;
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
/*********************************************************************** initFramebuffers ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::initFramebuffers(int width, int height)
{
    this->initVertices();

    /************************************************* VBO management ********************************************************/

    //generate Vertex Buffer Object ID
    glGenBuffers(1, &quadVBO);
    assert(quadVBO != 0);

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
    //generate Vertex Array Object ID
    glGenVertexArrays(1, &quadVAO);
    assert(quadVAO != 0);

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

    this->manageFramebuffers(width, height);
}

// /***********************************************************************************************************************************************************************/
// /****************************************************************** manageColorBuffer **********************************************************************************/
// /***********************************************************************************************************************************************************************/
void Framebuffer::manageColorBuffer(int width, int height)
{   
    glGenTextures(1, &texture_id);
    assert(texture_id != 0);

    glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glBindTexture(GL_TEXTURE_2D, 0);


    // glGenTextures(2, colorBuffers);
    // for(unsigned int i = 0; i < 2; i++)
    // {
    //     glActiveTexture(GL_TEXTURE0 + i);
    //     glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);

    //         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    //         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //         glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    // }

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, 0);

    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, 0);

    
}

/***********************************************************************************************************************************************************************/
// /****************************************************************** manageDepthMap **********************************************************************************/
// /***********************************************************************************************************************************************************************/
void Framebuffer::manageDepthMap(int width, int height)
{   
    glGenTextures(1, &depth_map);
    assert(depth_map != 0);

    glBindTexture(GL_TEXTURE_2D, depth_map);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

    glBindTexture(GL_TEXTURE_2D, 0);

}

/***********************************************************************************************************************************************************************/
/****************************************************************** manageDepthBuffer **********************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::manageRenderBuffer(int width, int height)
{
    glGenRenderbuffers(1, &render_buffer_id);
    assert(render_buffer_id != 0);

    glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_id);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_buffer_id);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // Tell OpenGL we need to draw to both attachments
	// unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	// glDrawBuffers(2, attachments);
}

/***********************************************************************************************************************************************************************/
/****************************************************************** managePingPongFBO **********************************************************************************/
/***********************************************************************************************************************************************************************/
// void Framebuffer::managePinPongFBO(int width, int height)
// {
//     glGenFramebuffers(2, ping_pongFBO);
// 	glGenTextures(2, ping_pong_text);
//     for (unsigned int i = 0; i < 2; i++)
// 	{
// 		glBindFramebuffer(GL_FRAMEBUFFER, ping_pongFBO[i]);

//         glActiveTexture(GL_TEXTURE0 + i);
// 		glBindTexture(GL_TEXTURE_2D, ping_pong_text[i]);
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ping_pong_text[i], 0);

// 		auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
// 		if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
//         {
//             std::cout << "ERROR::FRAMEBUFFER:: Ping Pong framebuffer is not complete >> " << fboStatus << std::endl;
//         }
//         std::cout << "FRAMEBUFFER:: Ping Pong Framebuffer is complete!" << std::endl;
    
// 		glBindFramebuffer(GL_FRAMEBUFFER, 0);
// 	}

//     glActiveTexture(GL_TEXTURE0);
// 	glBindTexture(GL_TEXTURE_2D, 0);

//     glActiveTexture(GL_TEXTURE1);
// 	glBindTexture(GL_TEXTURE_2D, 0);
// }

/***********************************************************************************************************************************************************************/
/****************************************************************** checkFramebufferStatus **********************************************************************************/
/***********************************************************************************************************************************************************************/
bool Framebuffer::checkFramebufferStatus(std::string const framebuffer_type)
{
    auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    std::string status_msg = ">> FRAMEBUFFER : " + framebuffer_type + " framebuffer is ";
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        status_msg += "NOT complete !";
        std::cout << status_msg  << status << std::endl;
        return false;
    }
    status_msg += "complete !";
    std::cout << status_msg << std::endl;
    return true;
}

/***********************************************************************************************************************************************************************/
/****************************************************************** manageFramebuffers **********************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::manageFramebuffers(int width, int height)
{
    glGenFramebuffers(1, &depth_fb_id);
    assert(depth_fb_id != 0);

    glBindFramebuffer(GL_FRAMEBUFFER, depth_fb_id);

        this->manageDepthMap(width, height);

        assert(this->checkFramebufferStatus("Depth"));

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenFramebuffers(1, &color_fb_id);
    assert(color_fb_id != 0);

    glBindFramebuffer(GL_FRAMEBUFFER, color_fb_id);

        this->manageColorBuffer(width, height);
        
        this->manageRenderBuffer(width, height);

        assert(this->checkFramebufferStatus("Color"));

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // this->managePinPongFBO(width, height);

    //===================================================================================================================
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** renderFrame ***********************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::renderFrame(DataManager &data_manager)
{
    bool horizontal = true;
    // this->drawBlur(data_manager, horizontal);
    this->drawScreenTexture(data_manager, horizontal);
}

/***********************************************************************************************************************************************************************/
/************************************************************************* drawBlur ************************************************************************************/
/***********************************************************************************************************************************************************************/
// void Framebuffer::drawBlur(DataManager &data_manager, bool &horizontal)
// {
//     bool first_it = true;
    
//     unsigned int amount = data_manager.getBloomStr();

//         glUseProgram(data_manager.getShader("blur")->getProgramID());

//         if(data_manager.getBloom())
//         {
//             for (unsigned int i = 0; i < amount; i++)
//             {
//                 glBindFramebuffer(GL_FRAMEBUFFER, ping_pongFBO[horizontal]);
                
//                 data_manager.getShader("blur")->setInt("horizontal", horizontal);
//                 data_manager.getShader("blur")->setTexture("screenTexture", 0);

//                 if(first_it)
//                 {
//                     glActiveTexture(GL_TEXTURE0);
//                     glBindTexture(GL_TEXTURE_2D, colorBuffers[1]);
//                     first_it = false;
//                 }
//                 else
//                 {
//                     glActiveTexture(GL_TEXTURE0);
//                     glBindTexture(GL_TEXTURE_2D, ping_pong_text[!horizontal]);
//                 }
//                 glBindVertexArray(quadVAO);

//                     glDrawArrays(GL_TRIANGLES, 0, 6);

//                     glActiveTexture(GL_TEXTURE0);
//                     glBindTexture(GL_TEXTURE_2D, 0);
                    

//                 glBindVertexArray(0);
                
//                 horizontal = !horizontal;
                
//             }
//         }

        

//     glUseProgram(0);

//     glBindFramebuffer(GL_FRAMEBUFFER, 0);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// }

/***********************************************************************************************************************************************************************/
/**************************************************************** drawScreenTexture ************************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::drawScreenTexture(DataManager &data_manager, bool &horizontal)
{
    glUseProgram(data_manager.getShader("depth_map")->getProgramID());

        data_manager.getShader("depth_map")->setMat4("light_space_matrix", data_manager.getLightSpaceMatrix());

        // data_manager.getShader("depth_map")->setMat4("projection", data_manager.getProjMat());
        // data_manager.getShader("depth_map")->setMat4("view", data_manager.getViewMat());

    glUseProgram(0);
    
    if(data_manager.getShader("screen") != nullptr)
    {
        glUseProgram(data_manager.getShader("screen")->getProgramID());

            // data_manager.getShader("screen")->setFloat("exposure", data_manager.getExposure());
            // data_manager.getShader("screen")->setInt("hdr", data_manager.getHDR());
            // data_manager.getShader("screen")->setInt("bloom", data_manager.getBloom());

            data_manager.getShader("screen")->setTexture("depth_texture", 0);
            data_manager.getShader("screen")->setTexture("screen_texture", 1);
            data_manager.getShader("screen")->setFloat("near", data_manager.getNear());
            data_manager.getShader("screen")->setFloat("far", data_manager.getFar());
            data_manager.getShader("screen")->setInt("render_depth", data_manager.getDepthRender());
            // data_manager.getShader("screen")->setTexture("bloom_texture", 2);
            // data_manager.getShader("screen")->setFloat("gamma", 2.2);

            glBindVertexArray(quadVAO);
                
                

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, depth_map);

                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, texture_id);

                // glActiveTexture(GL_TEXTURE1);
                // glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);

                // if(data_manager.getBloom())
                // {
                //     glActiveTexture(GL_TEXTURE2);
                //     glBindTexture(GL_TEXTURE_2D, ping_pong_text[!horizontal]);
                // }  
                
                glDrawArrays(GL_TRIANGLES, 0, 6);

                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, 0);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, 0);

                // if(data_manager.getBloom())
                // {
                //     glActiveTexture(GL_TEXTURE2);
                //     glBindTexture(GL_TEXTURE_2D, 0);
                // }

            glBindVertexArray(0);

            
        glUseProgram(0);
    }

    this->renderDebugWindow(data_manager);
    data_manager.setDepthMapTexture(depth_map);
    
}

/***********************************************************************************************************************************************************************/
/**************************************************************** renderDebugWindow ************************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::renderDebugWindow(DataManager &data_manager)
{
    if(data_manager.getDepthRender())
    {
        ImGuiWindowFlags window_flags = 0;
        
        window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(data_manager.getWidth()/2 - 90, data_manager.getHeight()/2 - 90));
        ImGui::Begin("Depth Map Render", nullptr, window_flags);
        ImGui::Image((void*) texture_id, ImVec2(data_manager.getWidth()/2 - 90, data_manager.getHeight()/2 - 95), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }
}

/***********************************************************************************************************************************************************************/
/****************************************************************** bindFramebuffer ************************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::bindFramebuffer(int type)
{

    glBindFramebuffer(GL_FRAMEBUFFER, this->getFB(type));

    //make sure we clear the framebuffer's content
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    //cleaning the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClear(GL_DEPTH_BUFFER_BIT);

    // glEnable(GL_DEPTH_TEST);
}

/***********************************************************************************************************************************************************************/
/**************************************************************** unbindFramebuffer ************************************************************************************/
/***********************************************************************************************************************************************************************/
void Framebuffer::unbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //make sure we clear the framebuffer's content
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** getter ****************************************************************************************/
/***********************************************************************************************************************************************************************/
unsigned int Framebuffer::getFB(int type) const
{
    unsigned int fb = 0;
    switch (type)
    {
        case COLOR_FBO:
            fb = color_fb_id;
            break;
        case DEPTH_FBO:
            fb = depth_fb_id;
            break;
        default:
            break;
    }
    return fb;
}