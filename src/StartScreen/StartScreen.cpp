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
StartScreen::StartScreen() : 
m_text_loadScreen(3.0, 0.2, 6, "../assets/font/venus rising rg.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag")
{
    m_text_loadScreen.loadTTF(" Solar System");
    std::cout << ">> Start Screen initiated" << std::endl;
}

StartScreen::~StartScreen()
{

}

/***********************************************************************************************************************************************************************/
/***************************************************************************** DrawStartScreen *************************************************************************/
/***********************************************************************************************************************************************************************/
void StartScreen::drawStartScreen(glm::mat4 &projection, glm::mat4 &modelview)
{
    glm::mat4 save = modelview;

    m_text_loadScreen.renderTextStartScreen(projection, modelview);

	modelview = save;
}