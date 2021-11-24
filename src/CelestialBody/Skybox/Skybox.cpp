/*
AUTHOR : SUZEAU François

DATE : 13/06/2021

MODULE : CelestialObject.Skybox

NAMEFILE : Skybox.cpp

PURPOSE : class Skybox
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Skybox.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Skybox::Skybox()
{
    Shader s("../src/Shader/Shaders/skybox.vert", "../src/Shader/Shaders/skybox.frag");
    m_shader = s;
    
    GLfloat skyboxVertices[108] = 
    {
        // positions          
        -2.0f,  2.0f, -2.0f,
        -2.0f, -2.0f, -2.0f,
        2.0f, -2.0f, -2.0f,
        2.0f, -2.0f, -2.0f,
        2.0f,  2.0f, -2.0f,
        -2.0f,  2.0f, -2.0f,

        -2.0f, -2.0f,  2.0f,
        -2.0f, -2.0f, -2.0f,
        -2.0f,  2.0f, -2.0f,
        -2.0f,  2.0f, -2.0f,
        -2.0f,  2.0f,  2.0f,
        -2.0f, -2.0f,  2.0f,

        2.0f, -2.0f, -2.0f,
        2.0f, -2.0f,  2.0f,
        2.0f,  2.0f,  2.0f,
        2.0f,  2.0f,  2.0f,
        2.0f,  2.0f, -2.0f,
        2.0f, -2.0f, -2.0f,

        -2.0f, -2.0f,  2.0f,
        -2.0f,  2.0f,  2.0f,
        2.0f,  2.0f,  2.0f,
        2.0f,  2.0f,  2.0f,
        2.0f, -2.0f,  2.0f,
        -2.0f, -2.0f,  2.0f,

        -2.0f,  2.0f, -2.0f,
        2.0f,  2.0f, -2.0f,
        2.0f,  2.0f,  2.0f,
        2.0f,  2.0f,  2.0f,
        -2.0f,  2.0f,  2.0f,
        -2.0f,  2.0f, -2.0f,

        -2.0f, -2.0f, -2.0f,
        -2.0f, -2.0f,  2.0f,
        2.0f, -2.0f, -2.0f,
        2.0f, -2.0f, -2.0f,
        -2.0f, -2.0f,  2.0f,
        2.0f, -2.0f,  2.0f
    };

    glGenVertexArrays(1, &m_vaoID);
    glGenBuffers(1, &m_vboID);
    glBindVertexArray(m_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_faces = {

            "../assets/textures/SkyboxMap/right.png",
            "../assets/textures/SkyboxMap/left.png",
            "../assets/textures/SkyboxMap/up.png",
            "../assets/textures/SkyboxMap/bottom.png",
            "../assets/textures/SkyboxMap/front.png",
            "../assets/textures/SkyboxMap/back.png"

                };
    m_texture_id = this->loadSybox();
}

Skybox::~Skybox()
{
    glDeleteTextures(1, &m_texture_id);
    //destroy VBO
    glDeleteBuffers(1, &m_vboID);
    
    //destroy VAO
    glDeleteVertexArrays(1, &m_vaoID);

    if((glIsTexture(m_texture_id) == GL_FALSE) && 
    (glIsBuffer(m_vboID) == GL_FALSE) && 
    (glIsVertexArray(m_vaoID) == GL_FALSE))
    {
        std::cout << "SKYBOX :: delete >>> SUCESS" << std::endl;
    }

}

/***********************************************************************************************************************************************************************/
/************************************************************************************ load *****************************************************************************/
/***********************************************************************************************************************************************************************/
unsigned int Skybox::loadSybox()
{
    /************************************************* destroying ancien ID *********************************************/
    if(glIsTexture(m_texture_id) == GL_TRUE)
    {
        glDeleteTextures(1, &m_texture_id);
    }
    //===================================================================================================================

    /************************************************* generate ID ********************************************************/
    unsigned int textID;
    glGenTextures(1, &textID);
    //===================================================================================================================

    /************************************************* lock object ********************************************************/
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textID);
    //=====================================================================================================================
    
    /************************************************* load the file ********************************************************/
    for (unsigned int i(0); i < m_faces.size(); i++)
    {
        SDL_Surface *picture_SDL = IMG_Load(m_faces[i].c_str());
        if(picture_SDL == 0)
        {
            std::cout << ">> Loading file img : ERROR : " << SDL_GetError() << std::endl;
            //return false;
        }
        std::cout << ">> Loading file " << m_faces[i] << " : SUCCESS" << std::endl;
        //===================================================================================================================

        /************************************************* copying pixels **************************************************************/
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, picture_SDL->w, picture_SDL->h, 0, GL_RGB, GL_UNSIGNED_BYTE, picture_SDL->pixels);
        SDL_FreeSurface(picture_SDL);
        //==============================================================================================================================
    }
    
    /************************************************* applying layer ********************************************************/
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    //=====================================================================================================================

    /************************************************* unlock object ********************************************************/
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    //=====================================================================================================================

    return textID;
    //return true;

}

/***********************************************************************************************************************************************************************/
/********************************************************************************* display *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Skybox::display(glm::mat4 &projection, glm::mat4 &view, bool hdr)
{   
    
    glDepthFunc(GL_LEQUAL);

    glUseProgram(m_shader.getProgramID());

    //lock vao
        glBindVertexArray(m_vaoID);

        glm::mat4 save = view;

        view = glm::mat4(glm::mat3(view));
        //send matrices to shader
        // glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "view"), 1, GL_FALSE, value_ptr(view));
        // glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        m_shader.setMat4("view", view);
        m_shader.setMat4("projection", projection);

        //Send texture unit to shader
        //glUniform1i(glGetUniformLocation(m_shader.getProgramID(), "skybox"), 0);
        m_shader.setTexture("skybox", 0);
        m_shader.setInt("hdr", hdr);

        //lock texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);

        //display the form
        
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //unlock texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


        // glDisableVertexAttribArray(2);
        // glDisableVertexAttribArray(0);

    //unlock VAO
    glBindVertexArray(0);

    glUseProgram(0);

    glDepthFunc(GL_LESS);
    

    view = save;
}

