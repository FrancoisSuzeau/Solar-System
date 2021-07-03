/*
AUTHOR : SUZEAU François

DATE : 02/07/2021

MODULE : CelestialObject.Atmosphere

NAMEFILE : Atmosphere.h

PURPOSE : class Atmosphere
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Atmosphere.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Atmosphere::Atmosphere(float size, std::string const texture): Disk(size, "../src/Shader/Shaders/atmosShader.vert", "../src/Shader/Shaders/atmosShader.frag"),
m_texture(texture), m_bytes_coord_size(12 * sizeof(float))
{
    // this->setShader("../src/Shader/Shaders/texture.vert", "../src/Shader/Shaders/texture.frag");
    // m_shader.loader();
    
    m_texture.loadTexture();

    float temp_coord[] = {0, 0,   1, 0,   1, 1,
                          0, 0,   0, 1,   1, 1,
                          
                          };

    for (int i(0); i < 12; i++)
    {
        m_coord[i] = temp_coord[i];
    }

    this->load();
    
}

Atmosphere::Atmosphere() : Disk()
{

}

Atmosphere::~Atmosphere()
{
    
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ load *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Atmosphere::load()
{
    /************************************************* VBO management ********************************************************/
    //destroy an possible ancient VBO
    if(glIsBuffer(m_vboID) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_vboID);
    }

    //generate Vertex Buffer Object ID
    glGenBuffers(1, &m_vboID);

    //lock VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);


        //memory allocation
        glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_coord_size, 0, GL_DYNAMIC_DRAW);
        /*
            - GL_STATIC_DRAW : data with few updating
            - GL_DYNAMIC_DRAW : data with frequently updating (many times per second but not each frame
            - GL_STREAM_DRAW : data with each frame updating
        there is 6 other possible values
        */

       //vertices transfert$
       glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices);
       glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_coord_size, m_coord);


    //unlock VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //===================================================================================================================

    /************************************************* VAO management ********************************************************/
    if(glIsVertexArray(m_vaoID) == GL_TRUE)
    {
        glDeleteVertexArrays(1, &m_vaoID);
    }
    //generate Vertex Array Object ID
    glGenVertexArrays(1, &m_vaoID);

    //lock VAO
    glBindVertexArray(m_vaoID);

        //lock VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        //access to vertices in video memory
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);

        //acces to coordonates texture in video memory
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));
        glEnableVertexAttribArray(2);

        //unlock VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    //unlock VAO
    glBindVertexArray(0);
    //===================================================================================================================

}

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayCrate **************************************************************************/
/***********************************************************************************************************************************************************************/
void Atmosphere::display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos)
{
    //Activate the shader
    glUseProgram(m_shader.getProgramID());

    //lock VAO
    glBindVertexArray(m_vaoID);

        //send matrices to shader
        // glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
        // glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        // glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "light_src"), 1, GL_FALSE, value_ptr(light_src));
        m_shader.setMat4("modelview", modelview);
        m_shader.setMat4("projection", projection);
        m_shader.setMat4("light_src", light_src);

        m_shader.setVec3("viewPos", camPos);

        //lock texture
        glBindTexture(GL_TEXTURE_2D, m_texture.getID());

        //display the form
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //unlock texture
        glBindTexture(GL_TEXTURE_2D, 0);


        // glDisableVertexAttribArray(2);
        // glDisableVertexAttribArray(0);

    //unlock VAO
    glBindVertexArray(0);

    glUseProgram(0);
}