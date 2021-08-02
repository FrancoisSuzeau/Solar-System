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
m_grey_rect(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.7),
m_titre(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_quit(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag")
{
    m_titre.loadTTF("Settings");
    m_quit.loadTTF("Quit Simulation");
    m_quit_mouse_button_pressed = false;

    screen_width = GetSystemMetrics(SM_CXSCREEN);
    screen_height = GetSystemMetrics(SM_CYSCREEN);
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


    //render titre settings

        modelview = translate(modelview, vec3(0.0, 0.345, -0.0));
        modelview = scale(modelview, vec3(0.03, 0.060, 0.0));
        m_titre.renderTextOverlay(projection, modelview);

    modelview = save;

        modelview = translate(modelview, vec3(0.0, -0.345, -0.0));
        modelview = scale(modelview, vec3(0.05, 0.060, 0.0));
        m_quit.renderTextOverlay(projection, modelview);

    modelview = save;
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************* quitSimulation ****************************************************************************/
/***********************************************************************************************************************************************************************/
bool Settings::quitSimulation(Input const &input)
{
    if((input.getMouseButton(SDL_MOUSEBUTTONDOWN)) && (!m_quit_mouse_button_pressed))
    {
        m_quit_mouse_button_pressed = true;
        std::cout << "xRel = " << input.getX() << std::endl;

        if( (input.getX() >= (screen_width/2) - 115) && (input.getX() <= (screen_width/2) + 115) ) //not portable with other screen -> have to search relative
        {
            std::cout << "yRel = " << input.getY() << std::endl;
            if((input.getY() >= (screen_height/2) + 256) && (input.getY() <= (screen_height/2) + 270))
            {
                //std::cout << "YES !" << std::endl;
                //return true;
            }
        }
    }

    if(input.getMouseButton(SDL_MOUSEBUTTONDOWN) == false)
    {
        m_quit_mouse_button_pressed = false;
    }
    

    return false;
}