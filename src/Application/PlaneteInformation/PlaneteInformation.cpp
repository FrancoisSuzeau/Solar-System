/*
AUTHOR : SUZEAU François

DATE : 06/08/2021

MODULE : PlaneteInformation

NAMEFILE : PlaneteInformation.cpp

PURPOSE : class PlaneteInformation
*/

#include "PlaneteInformation.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
PlaneteInformation::PlaneteInformation()
{
    map_color["Sun"] = {ImVec4(1.0f, 1.0f, 0.0f, 1.0f)};
    map_color["Mercury"] = {ImVec4(0.502f, 0.502f, 0.502f, 1.0f)};
    map_color["Venus"] = {ImVec4(1.0f, 0.894f, 0.710f, 1.0f)};
    map_color["Earth"] = {ImVec4(0.0f, 0.749f, 1.0f, 1.0f)};
    map_color["Mars"] = {ImVec4(0.698f, 0.133f, 0.133f, 1.0f)};
    map_color["Jupiter"] = {ImVec4(0.784f, 0.678f, 0.980f, 1.0f)};
    map_color["Saturn"] = {ImVec4(1.0f, 0.808f, 0.604f, 1.0f)};
    map_color["Uranus"] = {ImVec4(0.454f, 0.815f, 0.945f, 1.0f)};
    map_color["Neptune"] = {ImVec4(0.192f, 0.549f, 0.906f, 1.0f)};
}

PlaneteInformation::~PlaneteInformation()
{

}

/***********************************************************************************************************************************************************************/
/********************************************************************************* renderInfo **************************************************************************/
/***********************************************************************************************************************************************************************/
void PlaneteInformation::renderInfo(RenderData &render_data, std::string name_body)
{
    ImGuiWindowFlags window_flags = 0;

    window_flags |= ImGuiWindowFlags_NoResize;
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.04f, 0.04f, 0.04f, 1.0f));
    ImGui::SetNextWindowPos(ImVec2(render_data.getWidth()/2 + 200, render_data.getHeight()/2 - 300));
    ImGui::SetNextWindowSize(ImVec2(300, 330));
    
    ImGui::Begin("Informations", NULL, window_flags);
    std::string tmp = "                 " + name_body;

    ImGui::TextColored(map_color[name_body], tmp.c_str());

    ImGui::PopStyleColor();
    ImGui::End();
}