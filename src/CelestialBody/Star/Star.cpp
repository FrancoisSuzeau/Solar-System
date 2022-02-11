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
m_name(name)
{
    assert(m_cloud_texture.loadTexture());

    m_real_size = real_size;
    m_initial_pos = vec3(0.01f, 0.0f, 0.0f);
    m_current_position = m_initial_pos;
    m_speed_rotation = 0.1f;
    m_rotation_angle = 0.0f;
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
void Star::display(RenderData &render_data)
{
    if(render_data.getShader("sun") != nullptr)
    {
        //Activate the shader
        glUseProgram(render_data.getShader("sun")->getProgramID());

        //lock VBO and Index Buffer Object
        glBindBuffer(GL_ARRAY_BUFFER,         m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
        glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
        glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));

            render_data.getShader("sun")->setInt("displayText", this->displayTexture(render_data));

            render_data.getShader("sun")->setMat4("view", render_data.getViewMat());
            render_data.getShader("sun")->setMat4("projection", render_data.getProjectionMat());
            render_data.getShader("sun")->setMat4("model", m_model_mat);
            render_data.getShader("sun")->setInt("inverse_normals", true);

            render_data.setSunPos(m_current_position - render_data.getShipPos());

            render_data.getShader("sun")->setTexture("texture0", 0);

            render_data.getShader("sun")->setVec3("viewPos", render_data.getCamPos());
            render_data.getShader("sun")->setVec3("sunPos", render_data.getSunPos());
            
            //active and lock cloudy texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_cloud_texture.getID());
            
            //draw all textured vertices
            glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

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

/***********************************************************************************************************************************************************************/
/************************************************************************ displayTexture *******************************************************************************/
/***********************************************************************************************************************************************************************/
bool Star::displayTexture(RenderData &render_data)
{
    bool ret = true;
    float distance = Physique::getDistanceFromCam("Sun", render_data.getShipPos());

    if(distance >= 1900)
    {
        ret = false;
    }

    return ret;
}