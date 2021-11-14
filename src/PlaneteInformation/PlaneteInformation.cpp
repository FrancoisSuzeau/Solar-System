/*
AUTHOR : SUZEAU François

DATE : 06/08/2021

MODULE : PlaneteInformation

NAMEFILE : PlaneteInformation.cpp

PURPOSE : class PlaneteInformation
*/

#include "PlaneteInformation.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
PlaneteInformation::PlaneteInformation(std::string const name_plan, TTF_Font *police) : m_name_plan(name_plan),
m_text_name(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police)
{
    screen_h = GetSystemMetrics(SM_CXSCREEN);
    screen_w = GetSystemMetrics(SM_CYSCREEN);

    assert(m_text_name.loadTTF(m_name_plan));
    m_name_plan = "None";

    m_rect = new Square(0.05, 0.7);
    assert(m_rect);

    colorGrey = vec3(0.7);
    colorBlack = vec3(0.1);
}

PlaneteInformation::PlaneteInformation()
{

}

PlaneteInformation::~PlaneteInformation()
{
    if(m_rect != nullptr)
    {
        delete m_rect;
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* renderInfo **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlaneteInformation::renderInfo(glm::mat4 &projection, glm::mat4 &view, bool hdr, std::vector<Shader *> shaders)
{
    glm::mat4 save = view;
    float constance = 0.05;

    float start_x_black = -0.8;
    float start_y = 0.5;

    if((shaders[1] != nullptr) && (m_rect != nullptr))
    {
        //black fill
        for (size_t i(0); i < 11; i++)
        {
            for (size_t j(0); j < 9; j++)
            {
                    view = translate(view, vec3(start_x_black, start_y, 0.0));
                    m_rect->display(projection, view, colorBlack, hdr, shaders[1]);
                
                view = save;
                start_x_black = start_x_black + constance;
            }

            start_y = start_y - constance;
            start_x_black = -0.8;
        }

        //white border top and bottom
        float start_x_white = -0.8;

        for (size_t i(0); i < 9; i++)
        {
                view = translate(view, vec3(start_x_white, 0.51, 0.0));
                m_rect->display(projection, view, colorGrey, hdr, shaders[1]);
                
            view = save;

                view = translate(view, vec3(start_x_white, -0.01, 0.0));
                m_rect->display(projection, view, colorGrey, hdr, shaders[1]);

            view = save;

            start_x_white = start_x_white + constance;
        }

        //white border left and right
        float start_y_white = 0.51;

        for (size_t i(0); i < 11; i++)
        {
                view = translate(view, vec3(-0.81, start_y_white, 0.0));
                m_rect->display(projection, view, colorGrey, hdr, shaders[1]);
                
            view = save;

                view = translate(view, vec3(-0.39, start_y_white, 0.0));
                m_rect->display(projection, view, colorGrey, hdr, shaders[1]);
                
            view = save;

            start_y_white = start_y_white - constance;
        }

        //the last to white on the bottom corner left and right

            view = translate(view, vec3(-0.81, -0.01, 0.0));
            m_rect->display(projection, view, colorGrey, hdr, shaders[1]);
                
        view = save;

            view = translate(view, vec3(-0.39, -0.01, 0.0));
            m_rect->display(projection, view, colorGrey, hdr, shaders[1]);
    }

    

    view = save;

    if(shaders[0] != nullptr)
    {
            //Diplay text information
            view = translate(view, vec3(-0.585, 0.49, -0.0));
            view = scale(view, vec3(0.03, 0.05, 0.0));
            m_text_name.renderText(projection, view, shaders[0]);

        view = save;
    }

    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* setPlanPos **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlaneteInformation::setPosPlan(glm::vec3 const &planPos)
{
    m_plan_pos = planPos;
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** changeNamePlan **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlaneteInformation::changeNamePlan(std::string const name)
{
    assert(m_text_name.setText(name));
    m_name_plan = name;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** getInfoName **************************************************************************/
/***********************************************************************************************************************************************************************/
std::string PlaneteInformation::getInfoName() const
{
    return m_name_plan;
}