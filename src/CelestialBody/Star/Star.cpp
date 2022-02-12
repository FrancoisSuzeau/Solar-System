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

    m_flare = new FlareTexture(0.33f, "../../assets/textures/lensFlareTextures/sunSpikes.png");
    assert(m_flare);
}

Star::Star()
{
    
}

Star::~Star()
{
    if(m_flare)
    {
        delete m_flare;
    }
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

    this->renderFlare(render_data);
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

/***********************************************************************************************************************************************************************/
/************************************************************************ renderFlare *******************************************************************************/
/***********************************************************************************************************************************************************************/
void Star::renderFlare(RenderData &render_data)
{
    if(m_flare != nullptr)
    {
        glm::mat4 tmp_view_mat = render_data.getViewMat();
        render_data.initSaveMat();

        render_data.lockViewMat(glm::vec3(0.0f, 0.0f, 1.7f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

        // m_flare->setPositionFlareText(glm::vec3(0.0, 0.0, -0.2));
        // m_flare->transformMat();

        //calculate sun position on the screen
        glm::vec2 sunScreenCoords = convertToScreenSpace(render_data.getSunPos(), tmp_view_mat, render_data.getProjectionMat());

        if(sunScreenCoords == glm::vec2(-100))
        {
            return;
        }

        //calculate line form sun through center screen
        glm::vec2 sunToCenter = glm::vec2(0.5f) - sunScreenCoords;

        float brightness = 1 - (glm::length(sunToCenter) / 0.6f);
        
        if(brightness > 0)
        {
            calculateFlarePos(sunToCenter, sunScreenCoords);
            m_flare->display(render_data, brightness);
        }

        render_data.saveViewMat();
    }
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** calculateFlarePos **************************************************************************/
/***********************************************************************************************************************************************************************/
void Star::calculateFlarePos(glm::vec2 sunToCenter, glm::vec2 sunCoords)
{
    if(m_flare != nullptr)
    {
        
        /*
            Just a reminder : we calculate the sun coord on the screen with origin at the left hight corner of the screen (with 0.5, 0.5 as the center)
            but the position of the flares are calculate with the OpenGL screen coord with origin in the center of the screen because of the lock on the view matrice
            so we had to substract 0.5 at each calculation of the flare position
        */

        glm::vec2 flarePos = glm::vec2(sunCoords - glm::vec2(0.5));

        flarePos.y *= -1;
        flarePos.x *= -1;

        m_flare->setPositionFlareText(glm::vec3(flarePos, -0.2));
        m_flare->transformMat();
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** convertToScreenSpace **************************************************************************/
/***********************************************************************************************************************************************************************/
glm::vec2 Star::convertToScreenSpace(glm::vec3 sunPos, glm::mat4 viewMat, glm::mat4 projMat)
{

    glm::vec4 clipSpacePos = projMat * (viewMat * glm::vec4(sunPos, 1.0f));

    if(clipSpacePos.w <= 0)
    {
        return glm::vec2(-100); // NULL
    }

    float x = (clipSpacePos.x / clipSpacePos.w + 1) / 2.0f; 
    float y = 1 - ((clipSpacePos.y / clipSpacePos.w + 1) / 2.0f);

    return glm::vec2(x, y);
}