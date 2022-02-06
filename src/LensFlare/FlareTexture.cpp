/*
AUTHOR : SUZEAU François

DATE : 06/02/2021

MODULE : FlareTexture

NAMEFILE : FlareTexture.cpp

PURPOSE : class FlareTexture
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "FlareTexture.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
FlareTexture::FlareTexture(float size, std::string const text_path, glm::vec3 pos) : Disk(size),
m_texture(text_path), m_bytes_coord_size(12 * sizeof(float))
{
    assert(m_texture.loadTexture());

    float temp_coord[] = {0, 0,   1, 0,   1, 1,
                          0, 0,   0, 1,   1, 1,
                          
                          };

    for (int i(0); i < 12; i++)
    {
        m_coord[i] = temp_coord[i];
    }

    this->load();

    m_inclinaison_angle = 90.0f;
    m_real_size = 1.0f;

    transform_mat = glm::mat4(1.0f);

    m_pos = pos;
}

FlareTexture::FlareTexture() : Disk()
{

}

FlareTexture::~FlareTexture()
{

}

/***********************************************************************************************************************************************************************/
/************************************************************************************ load *****************************************************************************/
/***********************************************************************************************************************************************************************/
void FlareTexture::load()
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
/************************************************************************************ display **************************************************************************/
/***********************************************************************************************************************************************************************/
void FlareTexture::display(RenderData &render_data)
{
    if(render_data.getShader("flare") != nullptr)
    {
        // std::cout << "here" << std::endl;
        //Activate the shader
        glUseProgram(render_data.getShader("flare")->getProgramID());

        //lock VAO
        glBindVertexArray(m_vaoID);

            render_data.getShader("flare")->setMat4("view", render_data.getViewMat());
            render_data.getShader("flare")->setMat4("projection", render_data.getProjectionMat());
            render_data.getShader("flare")->setMat4("model", transform_mat);

            render_data.getShader("flare")->setTexture("texture0", 0);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_texture.getID());

            
            //display the form
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);

        //unlock VAO
        glBindVertexArray(0);

        glUseProgram(0);
    }
}

void FlareTexture::setPositionFlareText(glm::vec3 new_pos)
{
    m_pos = new_pos;
}

void FlareTexture::transformMat()
{
    transform_mat = glm::mat4(1.0f);

    transform_mat = glm::translate(transform_mat, m_pos);
}