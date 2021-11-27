/*
AUTHOR : SUZEAU François

DATE : 07/06/2021

MODULE : CelestialBody.AtmoPlanete

NAMEFILE : AtmoPlanete.cpp

PURPOSE : class AtmoPlanete
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)0 + (offset))
#endif
#define VERT_NUM_FLOATS 8


#include "AtmoPlanete.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
AtmoPlanete::AtmoPlanete(init_data data, TTF_Font *police) : SimplePlanete(data, police)
{

    /************************************************* add atmosphere texture ********************************************************/
    std::string tmp = "null";
    if(m_name == "Mars")
    {
        tmp = "../assets/textures/CelestialBody/MarsCloud.png";
        m_oppacity = 0.3;
    }
    else if(m_name == "Earth")
    {
        tmp = "../assets/textures/CelestialBody/CloudMap.jpg";
        m_oppacity = 0.3;
    }
    else if(m_name == "Venus")
    {
        tmp = "../assets/textures/CelestialBody/VenusCloud.jpg";
        m_oppacity = 0.115;
    }
    if(tmp != "null")
    {
        m_cloud_texture = new Texture(tmp);
        assert(m_cloud_texture);
        assert(m_cloud_texture->loadTexture());
    }
    
    //===================================================================================================================================
    
}

AtmoPlanete::AtmoPlanete() : SimplePlanete(), m_cloud_texture(), m_oppacity(0)
{

}

AtmoPlanete::~AtmoPlanete()
{
    if( (m_name == "Mars") || (m_name == "Venus") )
    {
        if(m_atmosphere != nullptr)
        {
            delete m_atmosphere;
        }
    }

    if(m_cloud_texture != nullptr)
    {
        delete m_cloud_texture;
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* display *******************************************************************************/
/***********************************************************************************************************************************************************************/
void AtmoPlanete::display(RenderData &render_data, glm::vec3 &camPos, Shader *atmo_plan_shader, Shader *ring_shader)
{
    if(atmo_plan_shader != nullptr)
    {
        //Activate the shader
        glUseProgram(atmo_plan_shader->getProgramID());

        //lock VBO and Index Buffer Object
        glBindBuffer(GL_ARRAY_BUFFER,         m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
        glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
        glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));

            atmo_plan_shader->setMat4("view", render_data.getViewMat());
            atmo_plan_shader->setMat4("projection", render_data.getProjectionMat());
            atmo_plan_shader->setMat4("model", m_model_mat);
            
            atmo_plan_shader->setTexture("material.cloud", 0);
            atmo_plan_shader->setTexture("material.terrain", 1);
            
            if(m_name == "Venus")
            {
                atmo_plan_shader->setInt("material.shininess", 16);
            }
            else
            {
                atmo_plan_shader->setInt("material.shininess", 32);
            }

            atmo_plan_shader->setFloat("oppacity", m_oppacity);

            atmo_plan_shader->setVec3("viewPos", camPos);

            atmo_plan_shader->setInt("hdr", render_data.getHDR());

            if(m_normal_surface != nullptr)
            {
                atmo_plan_shader->setInt("has_normal", true);
                atmo_plan_shader->setTexture("material.normalMap", 2);
                
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, m_normal_surface->getID());
            }
            else
            {
                atmo_plan_shader->setInt("has_normal", false);
            }
            
            // active and lock unit texture 1: surface
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, m_texture_surface->getID());

            //active and lock unit texture 0: cloud
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_cloud_texture->getID());
            
                //draw all textured vertices
                glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, 0);

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            
        /************************************************* unbind VBO and IBO ********************************************************/
        glBindBuffer(GL_ARRAY_BUFFER,         0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        //===================================================================================================================================

        glUseProgram(0);
    }
    


}