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
void StartScreen::drawStartScreen(RenderData &render_data)
{
    glm::mat4 save = render_data.getViewMat();


    if(render_data.getShader("text") != nullptr)
    {
        m_text_loadScreen.updatePosition(glm::vec3(0.0f, 0.5f, 0.0f));
        m_text_loadScreen.renderText(render_data);
    }

	render_data.updateView(save);
}