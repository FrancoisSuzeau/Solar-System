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
AtmoPlanete::AtmoPlanete(std::string const texture, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos) : SimplePlanete(texture, name, real_size, inclinaison_angle, initial_pos)
{

    Shader s("../src/Shader/Shaders/planeteTexture.vert", "../src/Shader/Shaders/MultiPlaneteTexture.frag");
    m_shader = s;

    
    
    /************************************************* add atmosphere texture ********************************************************/
    std::string tmp;
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
    Texture t(tmp);
    m_cloud_texture = t; //no need to load texture because of the overloaded = operator constructor
    //===================================================================================================================================
    
}

AtmoPlanete::AtmoPlanete() : SimplePlanete(), m_cloud_texture(), m_oppacity(0)
{

}

AtmoPlanete::~AtmoPlanete()
{
    if( (m_name == "Mars") || (m_name == "Venus") || (m_name == "Uranus") || (m_name == "Neptune") )
    {
        delete m_atmosphere;
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* display *******************************************************************************/
/***********************************************************************************************************************************************************************/
void AtmoPlanete::display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *atmo_plan_shader)
{
    
    //Activate the shader
    glUseProgram(m_shader.getProgramID());

    //lock VBO and Index Buffer Object
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
        
        //texture variable to shader
        // glUniform1i(glGetUniformLocation(m_shader.getProgramID(), "texture0"), 0);
        // glUniform1i(glGetUniformLocation(m_shader.getProgramID(), "texture1"), 1);
        m_shader.setTexture("texture0", 0);
        m_shader.setTexture("texture1", 1);

        //glUniform1f(glGetUniformLocation(m_shader.getProgramID(), "oppacity"), m_oppacity);
        m_shader.setFloat("oppacity", m_oppacity);

        //send camera position
        m_shader.setVec3("viewPos", camPos);

        m_shader.setInt("hdr", hdr);
        
        
        //active and lock unit texture 1: surface
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture_surface.getID());

        //active and lock unit texture 0: cloud
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

    // /************************************************* display atmosphere ********************************************************/
    // glm::mat4 save = modelview;
    // glm::mat4 save_light = light_src;

    // /*
    //     CamPos is the M point in spherical coordinate, so we already have his x, y, z coordinate
    //     but this coordinate are relative to the world reference
    //     so we add the planete position to the cam position to have the coordinate reference opposite to the planete
    //     we only use the parametrical coordinate to find the r radius
    // */

    // double x = camPos[0] - m_current_position[0]; //doesn't know why I have to use the reverse value
    // double y = camPos[1] - m_current_position[1];
    // double z = camPos[2] - m_current_position[2];
    // double r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
        
    // double r = std::sqrt(r_squarre);

    // float phi = atan(y/x);
    // float theta = acos(z/r);

    // m_atmosphere->display(projection, modelview, phi, theta, y, light_src, camPos);

    // modelview = save;
    // light_src = save;
    // //===================================================================================================================================


}

// /***********************************************************************************************************************************************************************/
// /******************************************************************************* displayAtmo ***************************************************************************/
// /***********************************************************************************************************************************************************************/
// void AtmoPlanete::displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, float phi, float theta, float y, glm::mat4 &light_src, glm::vec3 &camPos)
// {
//     std::cout << "atmo in atmo planete for " << m_name << std::endl;
//     m_atmosphere.display(projection, modelview, 0, 0, 0, 0, light_src, camPos);
// }