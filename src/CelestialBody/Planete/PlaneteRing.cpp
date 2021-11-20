/*
AUTHOR : SUZEAU François

DATE : 07/06/2021

MODULE : CelestialBody.Planete

NAMEFILE : PlaneteRing.cpp

PURPOSE : class PlaneteRing
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)0 + (offset))
#endif
#define VERT_NUM_FLOATS 8


#include "PlaneteRing.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
PlaneteRing::PlaneteRing(init_data data, TTF_Font *police) : SimplePlanete(data, police)
{
    if(data.name == "Saturn")
    {
        m_ring = new Ring(4, "../assets/textures/CelestialBody/SaturnRing.png", data);
        assert(m_ring);
    }
    else if(data.name == "Uranus")
    {
        m_ring = new Ring(4, "../assets/textures/CelestialBody/UranusRing.png", data);
        assert(m_ring);
    }
    else if(data.name == "Neptune")
    {
        m_ring = new Ring(4, "../assets/textures/CelestialBody/NeptuneRing.png", data);
        assert(m_ring);
    }

    // m_normal_surface = new Texture(data.normal_path);
    // assert(m_normal_surface);
    // assert(m_normal_surface->loadTexture());

    // m_disp_surface = new Texture(data.disp_path);
    // assert(m_disp_surface);
    // assert(m_disp_surface->loadTexture());

    heighhtScale = 0.1;
}

PlaneteRing::PlaneteRing() : SimplePlanete(), m_ring()
{
    
}

PlaneteRing::~PlaneteRing()
{
    if(m_ring != nullptr)
    {
        delete m_ring;
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** display ***************************************************************************/
/***********************************************************************************************************************************************************************/
void PlaneteRing::display(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, bool hdr, Shader *plan_ring_shader, Shader *ring_shader)
{
    if(plan_ring_shader != nullptr)
    {
        //Activate the shader
        glUseProgram(plan_ring_shader->getProgramID());

        glBindBuffer(GL_ARRAY_BUFFER,         m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
        glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
        glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));

            plan_ring_shader->setMat4("view", view);
            plan_ring_shader->setMat4("projection", projection);
            plan_ring_shader->setMat4("model", m_model_mat);
            
            plan_ring_shader->setTexture("material.diffuse", 0);

            plan_ring_shader->setVec3("viewPos", camPos);
            
            plan_ring_shader->setInt("hdr", hdr);
            plan_ring_shader->setInt("material.shininess", 16);


            // if(m_normal_surface != nullptr)
            // {
            //     if( heighhtScale > 0.0)
            //     {
            //         heighhtScale -= 0.0005f;
            //     }
            //     else
            //     {
            //         heighhtScale = 0.0f;
            //     }
            //     plan_ring_shader->setInt("has_normal", true);
            //     plan_ring_shader->setTexture("material.normalMap", 1);
            //     plan_ring_shader->setTexture("material.depthMap", 2);
            //     plan_ring_shader->setFloat("heightScale", heighhtScale);

            //     glActiveTexture(GL_TEXTURE2);
            //     glBindTexture(GL_TEXTURE_2D, m_disp_surface->getID());
                
            //     glActiveTexture(GL_TEXTURE1);
            //     glBindTexture(GL_TEXTURE_2D, m_normal_surface->getID());

            // }
            // else
            // {
            //     plan_ring_shader->setInt("has_normal", false);

            // }
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_texture_surface->getID());

            glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);

            if((m_ring != nullptr) && (ring_shader != nullptr))
            {
                m_ring->setPosition(m_current_position);
                m_ring->updatePosition();
                m_ring->display(projection, view, camPos, hdr, ring_shader);
            }

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