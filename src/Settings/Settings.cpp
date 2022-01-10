/*
AUTHOR : SUZEAU François

DATE : 02/08/2021

MODULE : Settings

NAMEFILE : Settings.cpp

PURPOSE : class Settings
*/

#include "Settings.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Settings::Settings()
{
    

}

Settings::~Settings()
{
    
    
}

/***********************************************************************************************************************************************************************/
/************************************************************************** manageSettings *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::manageSettings(RenderData &render_data)
{
    ImGuiWindowFlags window_flags = 0;
    bool terminate = false;
    
    window_flags |= ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowPos(ImVec2(render_data.getWidth()/2 - 200, render_data.getHeight()/2 - 250));
    ImGui::SetNextWindowSize(ImVec2(400, 500));
    
    ImGui::Begin("Settings", NULL, window_flags);

    if(ImGui::Button("Stop Simulation"))
    {
        terminate = true;
    }

    ImGui::End();

    render_data.setTerminate(terminate);
}