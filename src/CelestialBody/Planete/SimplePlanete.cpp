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
SimplePlanete::SimplePlanete(init_data data, TTF_Font *police) :
Sphere(1, 70, 70),
m_name(data.name)
{
    m_texture_surface = new Texture(data.texture_path);
    assert(m_texture_surface);
    assert(m_texture_surface->loadTexture());
    
    assert(police);
    m_name_renderer = new Text(3.0f, 0.2f, 6.0f, "../assets/font/aAtmospheric.ttf", police);
    assert(m_name_renderer);
    assert(m_name_renderer->loadTTF(m_name));

    // if((m_name != "Saturn") && (m_name != "Uranus") && (m_name != "Neptune"))
    // {
    //     m_normal_surface = new Texture(data.normal_path);
    //     assert(m_normal_surface);
    //     assert(m_normal_surface->loadTexture());

    //     m_disp_surface = new Texture(data.disp_path);
    //     assert(m_disp_surface);
    //     assert(m_disp_surface->loadTexture());

    //     heighhtScale = 0.1;
       
    // }
    
    //TODO : changing it to a special method
    m_inclinaison_angle = data.inclinaison_angle;
    m_real_size = data.size;
    m_initial_pos = data.position;
    m_current_position = m_initial_pos;
    m_rotation_angle = 0.0f;
    m_inclinaison_angle = data.inclinaison_angle;
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

    // if(m_normal_surface != nullptr)
    // {
    //     delete m_normal_surface;

    // }

    // if(m_disp_surface != nullptr)
    // {
    //     delete m_disp_surface;

    // }
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* display *******************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::display(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, bool hdr, Shader *simple_plan_shader, Shader *ring_shader)
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

            simple_plan_shader->setMat4("view", view);
            simple_plan_shader->setMat4("projection", projection);
            simple_plan_shader->setMat4("model", m_model_mat);
        
            simple_plan_shader->setTexture("material.diffuse", 0);

            simple_plan_shader->setVec3("viewPos", camPos);

            simple_plan_shader->setInt("hdr", hdr);
            if(m_name == "Jupiter")
            {
                simple_plan_shader->setInt("material.shininess", 8);
            }
            else
            {
                simple_plan_shader->setInt("material.shininess", 32);
            }
            
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
            //     simple_plan_shader->setInt("has_normal", true);
            //     simple_plan_shader->setTexture("material.normalMap", 1);
            //     simple_plan_shader->setTexture("material.depthMap", 2);
            //     simple_plan_shader->setFloat("heightScale", heighhtScale);

            //     glActiveTexture(GL_TEXTURE2);
            //     glBindTexture(GL_TEXTURE_2D, m_disp_surface->getID());
                
            //     glActiveTexture(GL_TEXTURE1);
            //     glBindTexture(GL_TEXTURE_2D, m_normal_surface->getID());
            // }
            // else
            // {
            //     simple_plan_shader->setInt("has_normal", false);

            // }

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_texture_surface->getID());
            
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
/******************************************************************************* displayName2 ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::displayName(glm::mat4 &projection, glm::mat4 &view, glm::vec3 camPos, int threshold, Shader *name_render_shader)
{
    if(name_render_shader != nullptr)
    {
        /*
            CamPos is the M point in spherical coordinate, so we already have his x, y, z coordinate
            but this coordinate are relative to the world reference
            so we add the planete position to the cam position to have the coordinate reference opposite to the planete
            we only use the parametrical coordinate to find the r radius
        */
           
        float r = this->getRadiusFromCam(camPos);
        float phi = this->getPhiFromCam(camPos);
        float theta = this->getThetaFromCam(camPos, r);
        float y = camPos[1] - m_current_position[1];
        
        if(r >= threshold * m_real_size)
        {
            translateCelestialBody(view, m_current_position);
            m_name_renderer->renderMovingText(projection, view, m_real_size, r, phi, theta, y, name_render_shader);
        }
        
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayAtmo ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SimplePlanete::displayAtmo(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, bool hdr, Shader *atmo_shader)
{
    if( (m_name == "Mars") || (m_name == "Venus")) 
    {
        if(atmo_shader != nullptr)
        {
            
            if(m_atmosphere != nullptr)
            {
                m_atmosphere->updatePosAtmo(m_current_position);
                m_atmosphere->display(projection, view, camPos, hdr, atmo_shader);
            }
            
        }
        
    }
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** getters ****************************************************************************/
/***********************************************************************************************************************************************************************/
std::string SimplePlanete::getName() const
{
    return m_name;
}

float SimplePlanete::getRadiusFromCam(glm::vec3 camPos)
{
    float x = camPos[0] - m_current_position[0];
    float y = camPos[1] - m_current_position[1];
    float z = camPos[2] - m_current_position[2];

    float r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
            
    return std::sqrt(r_squarre);

}

float SimplePlanete::getPhiFromCam(glm::vec3 camPos)
{
    float x = camPos[0] - m_current_position[0];
    float y = camPos[1] - m_current_position[1];

    return atan(y/x);
}

float SimplePlanete::getThetaFromCam(glm::vec3 camPos, float r)
{
    float z = camPos[2] - m_current_position[2];

    return acos(z/r);
}