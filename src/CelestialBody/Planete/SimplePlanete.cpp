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
SimplePlanete::SimplePlanete( std::string const texture, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos, TTF_Font *police) :
Sphere(1, 70, 70),
m_name(name)
{
    m_texture_surface = new Texture(texture);
    assert(m_texture_surface);
    assert(m_texture_surface->loadTexture());
    
    assert(police);
    m_name_renderer = new Text(3.0f, 0.2f, 6.0f, "../assets/font/aAtmospheric.ttf", police);
    assert(m_name_renderer);
    assert(m_name_renderer->loadTTF(m_name));

    //TODO : changing it to a special method
    m_inclinaison_angle = inclinaison_angle;
    m_real_size = real_size;
    m_initial_pos = initial_pos;
    m_current_position = m_initial_pos;
    m_rotation_angle = 0.0f;
    m_inclinaison_angle = inclinaison_angle;
    m_speed_rotation = 0.1f;

    if(m_name == "Mars")
    {
        m_atmosphere = new Atmosphere(1.05f, m_name);
        if(m_atmosphere == nullptr)
        {
            exit(EXIT_FAILURE);
        }
    }
    else if(m_name == "Venus")
    {
        m_atmosphere = new Atmosphere(1.05f, m_name);
        if(m_atmosphere == nullptr)
        {
            exit(EXIT_FAILURE);
        }
    }
}

SimplePlanete::SimplePlanete(): Sphere()
{

}

SimplePlanete::~SimplePlanete()
{
    if(m_texture_surface != nullptr)
    {
        delete m_texture_surface;
    }

    if(m_name_renderer != nullptr)
    {
        delete m_name_renderer;
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* display *******************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *simple_plan_shader, Shader *ring_shader)
{
    if(simple_plan_shader != nullptr)
    {
        //Activate the shader
        glUseProgram(simple_plan_shader->getProgramID());

        //lock VBO and Index Buffer Object
        glBindBuffer(GL_ARRAY_BUFFER,         m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
        glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
        glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));

            simple_plan_shader->setMat4("modelview", modelview);
            simple_plan_shader->setMat4("projection", projection);
            simple_plan_shader->setMat4("light_src", light_src);
        
            simple_plan_shader->setTexture("texture0", 0);

            simple_plan_shader->setVec3("viewPos", camPos);

            simple_plan_shader->setInt("hdr", hdr);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_texture_surface->getID());
            
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

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayName ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::displayName(glm::mat4 &projection, glm::mat4 &modelview, double ratio, float phi, float theta, float y, Shader *name_render_shader)
{
    if(name_render_shader != nullptr)
    {
        translateCelestialBody(modelview, m_current_position);
        m_name_renderer->renderMovingText(projection, modelview, m_real_size, ratio, phi, theta, y, name_render_shader);
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayName2 ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::displayName2(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 camPos, Shader *name_render_shader)
{
    if(name_render_shader != nullptr)
    {
        /*
            CamPos is the M point in spherical coordinate, so we already have his x, y, z coordinate
            but this coordinate are relative to the world reference
            so we add the planete position to the cam position to have the coordinate reference opposite to the planete
            we only use the parametrical coordinate to find the r radius
        */
       
        float x = camPos[0] - m_current_position[0];
        float y = camPos[1] - m_current_position[1];
        float z = camPos[2] - m_current_position[2];
           
        float r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
           
        float r = std::sqrt(r_squarre);
        float phi = atan(y/x);
        float theta = acos(z/r);
        
        if(r >= 400 * m_real_size)
        {
            translateCelestialBody(modelview, m_current_position);
            m_name_renderer->renderMovingText(projection, modelview, m_real_size, r, phi, theta, y, name_render_shader);
        }
        
    }
    
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
/******************************************************************************* displayAtmo ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *atmo_shader)
{
    if( (m_name == "Mars") || (m_name == "Venus")) 
    {
        if(atmo_shader != nullptr)
        {
            
            if(m_atmosphere != nullptr)
            {
                m_atmosphere->display(projection, modelview,  light_src, camPos, hdr, atmo_shader);
            }
            
        }
        
    }
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** getName ****************************************************************************/
/***********************************************************************************************************************************************************************/
std::string SimplePlanete::getName() const
{
    return m_name;
}