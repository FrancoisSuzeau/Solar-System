/*
AUTHOR : SUZEAU François

DATE : 11/07/2021

MODULE : StarAtmosphere

NAMEFILE : StarAtmosphere.cpp

PURPOSE : class StarAtmosphere
*/

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "StarAtmosphere.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
StarAtmosphere::StarAtmosphere(float size, std::string const name, std::string const texture): Disk(size),
m_texture(texture), m_bytes_coord_size(12 * sizeof(float))
{
    m_color_atmo = vec3(255.0/255.0, 255.0/255.0, 255.0/255.0);

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

StarAtmosphere::StarAtmosphere() : Disk()
{

}

StarAtmosphere::~StarAtmosphere()
{
    
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ load *****************************************************************************/
/***********************************************************************************************************************************************************************/
void StarAtmosphere::load()
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
void StarAtmosphere::display(glm::mat4 &projection, glm::mat4 &modelview, float phi, float theta, glm::vec3 &camPosUpd, glm::mat4 &light_src, glm::vec3 &camPos, Shader *star_atmo_shader)
{
    if(star_atmo_shader != nullptr)
    {
        /************************************************* positionning atmosphere **************************************************************/
        phi = phi * 180 / M_PI;
        theta = theta * 180 / M_PI;

        glm::mat4 save = modelview;
        if((phi < 0) && (camPosUpd[1] > 0))
        {
            modelview = rotate(modelview, -90.0f + phi, vec3(0.0, 0.0, 1.0));
        }
        else if( (phi > 0) && (camPosUpd[1] < 0) )
        {
            modelview = rotate(modelview, -90.0f + phi, vec3(0.0, 0.0, 1.0));
        }
        else if( (phi > 0) && (camPosUpd[1] > 0) )
        {
            modelview = rotate(modelview, 90.0f + phi, vec3(0.0, 0.0, 1.0));
        }
        else if( (phi < 0) && (camPosUpd[1] < 0) )
        {
            modelview = rotate(modelview, 90.0f + phi, vec3(0.0, 0.0, 1.0));
        }

        modelview = rotate(modelview, theta, vec3(1.0, 0.0, 0.0)); 
        
        //==============================================================================================================================
        //Activate the shader
        glUseProgram(star_atmo_shader->getProgramID());

        //lock VAO
        glBindVertexArray(m_vaoID);

            //send matrices to shader
            // glUniformMatrix4fv(glGetUniformLocation(star_atmo_shader->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
            // glUniformMatrix4fv(glGetUniformLocation(star_atmo_shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
            // glUniformMatrix4fv(glGetUniformLocation(star_atmo_shader->getProgramID(), "light_src"), 1, GL_FALSE, value_ptr(light_src));
            star_atmo_shader->setMat4("modelview", modelview);
            star_atmo_shader->setMat4("projection", projection);
            star_atmo_shader->setMat4("light_src", light_src);

            star_atmo_shader->setVec3("viewPos", camPos);
            star_atmo_shader->setVec3("atmoColor", m_color_atmo);

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

        modelview = save;
    }
    
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** displaySunAtmo *************************************************************************/
/***********************************************************************************************************************************************************************/
void StarAtmosphere::displaySunAtmo(glm::mat4 &projection, glm::mat4 &modelview, float phi, float theta, glm::vec3 &camPosUpd, bool hdr, Shader *atmo_shader)
{
    if(atmo_shader != nullptr)
    {
        /************************************************* positionning atmosphere **************************************************************/
        phi = phi * 180 / M_PI;
        theta = theta * 180 / M_PI;

        glm::mat4 save = modelview;
        if((phi < 0) && (camPosUpd[1] > 0))
        {
            modelview = rotate(modelview, -90.0f + phi, vec3(0.0, 0.0, 1.0));
        }
        else if( (phi > 0) && (camPosUpd[1] < 0) )
        {
            modelview = rotate(modelview, -90.0f + phi, vec3(0.0, 0.0, 1.0));
        }
        else if( (phi > 0) && (camPosUpd[1] > 0) )
        {
            modelview = rotate(modelview, 90.0f + phi, vec3(0.0, 0.0, 1.0));
        }
        else if( (phi < 0) && (camPosUpd[1] < 0) )
        {
            modelview = rotate(modelview, 90.0f + phi, vec3(0.0, 0.0, 1.0));
        }

        modelview = rotate(modelview, theta, vec3(1.0, 0.0, 0.0));
        
        //==============================================================================================================================
        //Activate the shader
        glUseProgram(atmo_shader->getProgramID());

        //lock VAO
        glBindVertexArray(m_vaoID);

            //send matrices to shader
            // glUniformMatrix4fv(glGetUniformLocation(atmo_shader->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
            // glUniformMatrix4fv(glGetUniformLocation(atmo_shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
            atmo_shader->setMat4("modelview", modelview);
            atmo_shader->setMat4("projection", projection);

            atmo_shader->setVec3("atmoColor", m_color_atmo);
            atmo_shader->setInt("hdr", hdr);

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

        modelview = save;
    }
    
}