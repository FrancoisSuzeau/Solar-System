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
        m_ring = new Ring(4, "../assets/textures/CelestialBody/SaturnRing.png");
        assert(m_ring);
    }
    else if(data.name == "Uranus")
    {
        m_ring = new Ring(4, "../assets/textures/CelestialBody/UranusRing.png");
        assert(m_ring);
    }
    else if(data.name == "Neptune")
    {
        m_ring = new Ring(4, "../assets/textures/CelestialBody/NeptuneRing.png");
        assert(m_ring);
    }
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
void PlaneteRing::display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *plan_ring_shader, Shader *ring_shader)
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

            plan_ring_shader->setMat4("modelview", modelview);
            plan_ring_shader->setMat4("projection", projection);
            plan_ring_shader->setMat4("light_src", light_src);
            
            plan_ring_shader->setTexture("texture0", 0);

            plan_ring_shader->setVec3("viewPos", camPos);
            
            plan_ring_shader->setInt("hdr", hdr);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_texture_surface->getID());

            glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

            glBindTexture(GL_TEXTURE_2D, 0);

            if((m_ring != nullptr) && (ring_shader != nullptr))
            {
                m_ring->display(projection, modelview, light_src, camPos, hdr, ring_shader);
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