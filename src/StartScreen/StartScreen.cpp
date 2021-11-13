/*
AUTHOR : SUZEAU François

DATE : 23/06/2021

MODULE : StartScreen

NAMEFILE : StartScreen.cpp

PURPOSE : class StartScreen
*/



#include "StartScreen.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
StartScreen::StartScreen(TTF_Font *police) : 
m_text_loadScreen(3.0f, 0.2f, 6.0f, "../assets/font/venus rising rg.ttf", police)
{
    assert(m_text_loadScreen.loadTTF(" Solar System"));
    std::cout << ">> Start Screen initiated" << std::endl;
}

StartScreen::~StartScreen()
{

}

/***********************************************************************************************************************************************************************/
/***************************************************************************** DrawStartScreen *************************************************************************/
/***********************************************************************************************************************************************************************/
void StartScreen::drawStartScreen(glm::mat4 &projection, glm::mat4 &modelview, Shader *text_shader)
{
    glm::mat4 save = modelview;

    if(text_shader != nullptr)
    {
        m_text_loadScreen.renderText(projection, modelview, text_shader);
    }

	modelview = save;
}