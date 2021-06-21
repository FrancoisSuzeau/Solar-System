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


#include "PlaneteRing.h"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
PlaneteRing::PlaneteRing(std::string const texture, std::string const ring_texture, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos) : SimplePlanete(texture, name, real_size, inclinaison_angle, initial_pos),
m_ring(4, ring_texture)
{
    
}

PlaneteRing::PlaneteRing() : SimplePlanete(), m_ring()
{

}

PlaneteRing::~PlaneteRing()
{
   
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayCrate **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlaneteRing::display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src)
{
    //Activate the shader
    glUseProgram(m_shader.getProgramID());

    glBindBuffer(GL_ARRAY_BUFFER,         m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
    glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
    glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));

        //send matrices to shader
        // glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
        // glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        // glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "light_src"), 1, GL_FALSE, value_ptr(light_src));
        m_shader.setMat4("modelview", modelview);
        m_shader.setMat4("projection", projection);
        m_shader.setMat4("light_src", light_src);
        
        // glUniform1i(glGetUniformLocation(m_shader.getProgramID(), "texture0"), 0);
        m_shader.setTexture("texture0", 0);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_surface.getID());

        glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

        glBindTexture(GL_TEXTURE_2D, 0);

        m_ring.display(projection, modelview, light_src);

    /************************************************* unbind VBO and IBO ********************************************************/
    glBindBuffer(GL_ARRAY_BUFFER,         0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    //===================================================================================================================================

    glUseProgram(0);

    
}