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


#include "Star.h"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Star::Star(const float radius, const unsigned int longSegs, const unsigned int latSegs, std::string const texture, std::string const name, float const real_size) :
Sphere(radius, longSegs, latSegs, "../src/Shader/Shaders/sunShader.vert", "../src/Shader/Shaders/sunShader.frag"), m_cloud_texture(texture),
 m_name(name), m_name_renderer(3.0, 0.2, 6, "../assets/font/font.TTF", "../src/Shader/Shaders/texture.vert", "../src/Shader/Shaders/texture.frag"), m_light_vao(0)
{
    m_cloud_texture.loadTexture();
    m_name_renderer.loadTTF(m_name);

    m_real_size = real_size;
    m_initial_pos = vec3(0.1, 0.0, 0.0);
    m_current_position = m_initial_pos;

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
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* display *******************************************************************************/
/***********************************************************************************************************************************************************************/
void Star::display(glm::mat4 &projection, glm::mat4 &modelview)
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

        // glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
        // glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        m_shader.setMat4("modelview", modelview);
        m_shader.setMat4("projection", projection);
        
        //texture variable to shader
        //glUniform1i(glGetUniformLocation(m_shader.getProgramID(), "texture0"), 0);
        m_shader.setTexture("texture0", 0);
        
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

/***********************************************************************************************************************************************************************/
/******************************************************************************* display *******************************************************************************/
/***********************************************************************************************************************************************************************/
void Star::displayName(glm::mat4 &projection, glm::mat4 &modelview)
{
    m_name_renderer.renderText(projection, modelview, m_real_size);
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** updatePosition ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Star::updatePosition(glm::mat4 &projection, glm::mat4 &modelview, float const rotation)
{
    //postionning body
    translateCelestialBody(modelview, m_current_position);

    //displaying name of the planete
    //displayName(projection, modelview);

    //making the planete rotation
    rotateCelestialBody(modelview, rotation);

    //scaling on his real size
    scaleCelestialBody(modelview, m_real_size);
}