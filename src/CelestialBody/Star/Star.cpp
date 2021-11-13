/*
AUTHOR : SUZEAU François

DATE : 16/06/2021

MODULE : CelestialBody.Star

NAMEFILE : Star.cpp

PURPOSE : class Star
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)0 + (offset))
#endif
#define VERT_NUM_FLOATS 8


#include "Star.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Star::Star(const float radius, const unsigned int longSegs, const unsigned int latSegs, std::string const texture, std::string const name, float const real_size) :
Sphere(radius, longSegs, latSegs), m_cloud_texture(texture),
m_name(name), m_light_vao(0)
{
    assert(m_cloud_texture.loadTexture());

    m_real_size = real_size;
    m_initial_pos = vec3(0.01f, 0.0f, 0.0f);
    m_current_position = m_initial_pos;
    m_speed_rotation = 0.1f;
    m_rotation_angle = 0.0f;

    m_atmosphere = new Atmosphere(1.05f, m_name);
    assert(m_atmosphere);

    /************************************************* VAO management ********************************************************/
    if(glIsVertexArray(m_light_vao) == GL_TRUE)
    {
        glDeleteVertexArrays(1, &m_light_vao);
    }
    //generate Vertex Array Object ID
    glGenVertexArrays(1, &m_light_vao);

    //lock VAO
    glBindVertexArray(m_light_vao);

        //lock VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        //access to vertices in video memory
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);

        //unlock VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    //unlock VAO
    glBindVertexArray(0);
    //===================================================================================================================

}

Star::Star()
{
    
}

Star::~Star()
{
    if(m_atmosphere != nullptr)
    {
        delete m_atmosphere;
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* display *******************************************************************************/
/***********************************************************************************************************************************************************************/
void Star::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *star_shader)
{
    if(star_shader != nullptr)
    {
        //Activate the shader
        glUseProgram(star_shader->getProgramID());

        //lock VBO and Index Buffer Object
        glBindBuffer(GL_ARRAY_BUFFER,         m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
        glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
        glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));

            star_shader->setMat4("modelview", modelview);
            star_shader->setMat4("projection", projection);
            star_shader->setMat4("model", m_model_mat);

            star_shader->setTexture("texture0", 0);

            star_shader->setVec3("viewPos", camPos);
            
            //active and lock cloudy texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_cloud_texture.getID());
            
            //draw all textured vertices
            glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

            
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

// /***********************************************************************************************************************************************************************/
// /**************************************************************************** updatePosition ***************************************************************************/
// /***********************************************************************************************************************************************************************/
// void Star::updatePosition(glm::mat4 &projection, glm::mat4 &modelview, float const rotation)
// {
//     m_model_mat = glm::mat4(1.0f);
//     //postionning body
//     translateCelestialBody(m_model_mat, m_current_position);

//     m_rotation_angle += m_speed_rotation;
//     if(m_rotation_angle >= 360)
//     {
//         m_rotation_angle -= 360;
//     }
//     rotateCelestialBody(m_model_mat, m_rotation_angle);

//     //scaling on his real size
//     scaleCelestialBody(m_model_mat, m_real_size);
// }

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayAtmo ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Star::displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, Shader *atmo_shader)
{
    if(atmo_shader != nullptr)
    {
        translateCelestialBody(modelview, m_current_position);
        if(m_atmosphere != nullptr)
        {
            //HACK : in fact we don't need this, have to change some parameter to pass them with default value
            glm::vec3 campos(0.0f);
            m_atmosphere->display(projection, modelview, campos, hdr, atmo_shader);
        }
           
    }
}