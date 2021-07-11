/*
AUTHOR : SUZEAU François

DATE : 15/06/2021

MODULE : CelestialBody.SimplePlanete

NAMEFILE : SimplePlanete.cpp

PURPOSE : class SimplePlanete
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)0 + (offset))
#endif
#define VERT_NUM_FLOATS 8


#include "SimplePlanete.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
SimplePlanete::SimplePlanete( std::string const texture, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos) :
Sphere(1, 50, 50, "../src/Shader/Shaders/planeteTexture.vert", "../src/Shader/Shaders/oneTexturePlanete.frag"), m_texture_surface(texture),
m_name(name), m_name_renderer(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag")
{
    m_texture_surface.loadTexture();
    m_name_renderer.loadTTF(m_name);
    m_inclinaison_angle = inclinaison_angle;
    m_real_size = real_size;
    m_initial_pos = initial_pos;
    m_current_position = m_initial_pos;
    m_rotation_angle = 0.0;
    m_inclinaison_angle = inclinaison_angle;
    m_speed_rotation = 0.1;

    if(m_name == "Mars")
    {
        m_atmosphere = new Atmosphere(9.7, m_name, "../assets/textures/atmosphere.png");

    }
    else if(m_name == "Venus")
    {
        m_atmosphere = new Atmosphere(10.4, m_name, "../assets/textures/atmosphere.png");
    }
}

SimplePlanete::SimplePlanete(): Sphere()
{

}

SimplePlanete::~SimplePlanete()
{
   
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* display *******************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos)
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
        m_shader.setTexture("texture0", 0);

        m_shader.setVec3("viewPos", camPos);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture_surface.getID());
        
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

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayName ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::displayName(glm::mat4 &projection, glm::mat4 &modelview, double ratio, float phi, float theta, float y)
{
    translateCelestialBody(modelview, m_current_position);
    m_name_renderer.renderText(projection, modelview, m_real_size, ratio, phi, theta, y);
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** updatePosition ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::updatePosition(glm::mat4 &projection, glm::mat4 &modelview)
{
    m_current_position = m_initial_pos;
    //postionning body
    translateCelestialBody(modelview, m_current_position);

    //making the planete inclinaison
    inclineCelestialBody(modelview, m_inclinaison_angle);

    //making the planete rotation
    m_rotation_angle += m_speed_rotation;
    if(m_rotation_angle >= 360)
    {
        m_rotation_angle -= 360;
    }
    rotateCelestialBody(modelview, m_rotation_angle);

    //scaling on his real size
    scaleCelestialBody(modelview, m_real_size);
}

/***********************************************************************************************************************************************************************/
/************************************************************************* updatePositionLight *************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::updatePositionLight(glm::mat4 &projection, glm::mat4 &light_src)
{
    m_current_position = m_initial_pos;
    //postionning body
    translateCelestialBody(light_src, m_current_position);

    //making the planete inclinaison
    inclineCelestialBody(light_src, m_inclinaison_angle);

    //making the planete rotation
    m_rotation_angle += m_speed_rotation;
    if(m_rotation_angle >= 360)
    {
        m_rotation_angle -= 360;
    }
    rotateCelestialBody(light_src, m_rotation_angle);

    //scaling on his real size
    scaleCelestialBody(light_src, m_real_size);
}

/***********************************************************************************************************************************************************************/
/*************************************************************************** updateAtmoInter ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::updateAtmoInter(glm::mat4 &projection, glm::mat4 &light_src)
{
    m_current_position = m_initial_pos;
    //postionning body
    translateCelestialBody(light_src, m_current_position);

    //making the planete inclinaison
    //inclineCelestialBody(light_src, m_inclinaison_angle);

    //scaling on his real size
    scaleCelestialBody(light_src, m_real_size);
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayAtmo ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, float phi, float theta, glm::vec3 &body_pos, glm::mat4 &light_src, glm::vec3 &camPos)
{
    if( (m_name == "Mars") || (m_name == "Venus") )
    {
        translateCelestialBody(modelview, m_current_position);
        m_atmosphere->display(projection, modelview, phi, theta, body_pos, light_src, camPos);
    }
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** getName ****************************************************************************/
/***********************************************************************************************************************************************************************/
std::string SimplePlanete::getName() const
{
    return m_name;
}