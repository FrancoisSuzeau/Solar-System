/*
AUTHOR : SUZEAU François

DATE : 02/08/2021

MODULE : Settings

NAMEFILE : Settings.cpp

PURPOSE : class Settings
*/

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Settings.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Settings::Settings() : m_black_rect(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.1),
m_grey_rect(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.7)
{

}

Settings::~Settings()
{

}

/***********************************************************************************************************************************************************************/
/********************************************************************* displayFrameSettings ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::displayFrameSettings(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
{
    glm::mat4 save = modelview;
    float constance = 0.05;

    float start_x_black = -0.3;
    float start_y = 0.35;

    //black fill
    for (size_t i(0); i < 15; i++)
    {
        for (size_t j(0); j < 13; j++)
        {
                modelview = translate(modelview, vec3(start_x_black, start_y, 0.0));
                m_black_rect.display(projection, modelview, hdr);
            
            modelview = save;
            start_x_black = start_x_black + constance;
        }

        start_y = start_y - constance;
        start_x_black = -0.3;
    }

    //white border top and bottom
    float start_x_white = -0.3;

    for (size_t i(0); i < 13; i++)
    {
            modelview = translate(modelview, vec3(start_x_white, 0.36, 0.0));
            m_grey_rect.display(projection, modelview, hdr);
            
        modelview = save;

            modelview = translate(modelview, vec3(start_x_white, -0.36, 0.0));
            m_grey_rect.display(projection, modelview, hdr);

        modelview = save;

        start_x_white = start_x_white + constance;
    }

    //white border left and right
    float start_y_white = 0.36;

    for (size_t i(0); i < 15; i++)
    {
            modelview = translate(modelview, vec3(-0.31, start_y_white, 0.0));
            m_grey_rect.display(projection, modelview, hdr);
            
        modelview = save;

            modelview = translate(modelview, vec3(0.31, start_y_white, 0.0));
            m_grey_rect.display(projection, modelview, hdr);
            
        modelview = save;

        start_y_white = start_y_white - constance;
    }

    //the last to white on the bottom corner left and right

        modelview = translate(modelview, vec3(-0.31, -0.36, 0.0));
        m_grey_rect.display(projection, modelview, hdr);
            
    modelview = save;

        modelview = translate(modelview, vec3(0.31, -0.36, 0.0));
        m_grey_rect.display(projection, modelview, hdr);
            
    modelview = save;
    
}