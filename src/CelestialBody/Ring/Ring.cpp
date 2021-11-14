/*
AUTHOR : SUZEAU François

DATE : 10/06/2021

MODULE : CelestialObject.Ring

NAMEFILE : Ring.h

PURPOSE : class Ring
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Ring.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Ring::Ring(float size, std::string const texture, init_data data): Disk(size),
m_texture(texture), m_bytes_coord_size(12 * sizeof(float))
{
    
    assert(m_texture.loadTexture());

    m_rotation_angle = 0.0f;
    m_speed_rotation = 0.1f;

    if(data.name == "Saturn")
    {
        m_inclinaison_angle = 26.73f;
        m_real_size = 300.0f;
    }
    else if(data.name == "Uranus")
    {
        m_inclinaison_angle = 97.77f;
        m_real_size = 100.0f;
    }
    else if(data.name == "Neptune")
    {
        m_inclinaison_angle = 26.32f;
        m_real_size = 100.0f;
    }

    float temp_coord[] = {0, 0,   1, 0,   1, 1,
                          0, 0,   0, 1,   1, 1,
                          
                          };

    for (int i(0); i < 12; i++)
    {
        m_coord[i] = temp_coord[i];
    }

    this->load();
    
}

Ring::Ring() : Disk()
{

}

Ring::~Ring()
{
    
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ load *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Ring::load()
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
/****************************************************************************** updatePosRing **************************************************************************/
/***********************************************************************************************************************************************************************/
void Ring::updatePosRing(glm::vec3 planPos)
{
    m_current_position = planPos;
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ display **************************************************************************/
/***********************************************************************************************************************************************************************/
void Ring::display(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, bool hdr, Shader *ring_shader)
{
    if(ring_shader != nullptr)
    {
        //Activate the shader
        glUseProgram(ring_shader->getProgramID());

        //lock VAO
        glBindVertexArray(m_vaoID);

            ring_shader->setMat4("view", view);
            ring_shader->setMat4("projection", projection);
            ring_shader->setMat4("model", m_model_mat);

            ring_shader->setVec3("viewPos", camPos);
            ring_shader->setInt("hdr", hdr);

            //lock texture
            glBindTexture(GL_TEXTURE_2D, m_texture.getID());

            //display the form
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //unlock texture
            glBindTexture(GL_TEXTURE_2D, 0);

        //unlock VAO
        glBindVertexArray(0);

        glUseProgram(0);
    }
    
}

//NOT CONCERN 
void Ring::displayInfo(glm::mat4 &projection, glm::mat4 &view, bool hdr)
{
    
}