/*
AUTHOR : SUZEAU François

DATE : 10/06/2021

MODULE : CelestialObject.Geometry

NAMEFILE : Disk.h

PURPOSE : class Disk
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Disk.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Disk::Disk(float size) : m_vboID(0), m_bytes_colors_size(18 * sizeof(float))
{
    m_bytes_vertices_size = 18 * sizeof(float);
    m_size = size;
    m_size /= 2;
    float verticesTmp[] = {-m_size, -m_size, 0.0f,   m_size, -m_size, 0.0f,   m_size, m_size, 0.0f,   
                        -m_size, -m_size, 0.0f,   -m_size, m_size, 0.0f,   m_size, m_size, 0.0f,   

                        };


    float colorsTmp[] = {1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
                        
                        };

    for (int i(0); i < 18; i++)
    {
        m_vertices[i] = verticesTmp[i];
        m_colors[i] = colorsTmp[i];
    }

    this->load();

}

Disk::Disk()
{
    
}

Disk::~Disk()
{
    //destroy VBO
    glDeleteBuffers(1, &m_vboID);
    
    //destroy VAO
    glDeleteVertexArrays(1, &m_vaoID);
    if( (glIsBuffer(m_vboID) == GL_FALSE) && (glIsVertexArray(m_vaoID) == GL_FALSE))
    {
        std::cout << "DISK :: delete >>> SUCESS" << std::endl;
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* display *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Disk::display(RenderData &render_data, glm::vec3 &camPos)
{
    if(render_data.getShader("square") != nullptr)
    {
        glUseProgram(render_data.getShader("square")->getProgramID());

            glBindVertexArray(m_vaoID);

            render_data.getShader("square")->setMat4("projection", render_data.getProjectionMat());
            render_data.getShader("square")->setMat4("view", render_data.getViewMat());

            glDrawArrays(GL_TRIANGLES, 0, 6);

            glBindVertexArray(0);

        glUseProgram(0);
    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** load ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Disk::load()
{
    /************************************************* VBO management ********************************************************/
    //destroy a possible ancient VBO
    if(glIsBuffer(m_vboID) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_vboID);
    }

    //generate Vertex Buffer Object ID
    glGenBuffers(1, &m_vboID);

    //lock VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        //memory allocation
        glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_colors_size, 0, GL_STATIC_DRAW);
        /*
            - GL_STATIC_DRAW : data with few updating
            - GL_DYNAMIC_DRAW : data with frequently updating (many times per second but not each frame
            - GL_STREAM_DRAW : data with each frame updating
        there is 6 other possible values
        */

       //vertices transfert$
       glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices);
       glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_colors_size, m_colors);


    //unlock VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //===================================================================================================================

    /************************************************* VAO management ********************************************************/
    //destroy a possible ancient VAO
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

        //acces to the vertices in video memory
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);

        //acces to the colors in video memory
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));
        glEnableVertexAttribArray(1);

        //unlock VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    //unlock VAO
    glBindVertexArray(0);
    //===================================================================================================================

}