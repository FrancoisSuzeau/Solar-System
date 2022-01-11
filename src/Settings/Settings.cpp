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
    bool terminate = render_data.getTerminate();
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 frame_padding_save = style.FramePadding;
    
    window_flags |= ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowPos(ImVec2(render_data.getWidth()/2 - 200, render_data.getHeight()/2 - 150));
    ImGui::SetNextWindowSize(ImVec2(400, 300));
    
    
    ImGui::Begin("Settings", NULL, window_flags);

    
    if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
    {
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("Navigation Options"))
        {
            style.FramePadding = frame_padding_save;
            ImGui::EndTabItem();
        }
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("HUD"))
        {
            style.FramePadding = frame_padding_save;
            ImGui::EndTabItem();
        }
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("Performance"))
        {
            style.FramePadding = frame_padding_save;
            this->managePerformance(render_data, style);
            ImGui::EndTabItem();
        }
        
        style.FramePadding = frame_padding_save;
        ImGui::EndTabBar();
    }
    style.FramePadding = frame_padding_save;
    


    ImGui::Separator();

    if(ImGui::Button("Stop Simulation", ImVec2(385.0f, 0.0f)))
    {
        terminate = true;
    }

    ImGui::End();

    render_data.setTerminate(terminate);
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** managePerformance *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::managePerformance(RenderData &render_data, ImGuiStyle& style)
{
    ImGui::Text("Rendering");

    ImGui::BulletText("Set HDR");
    ImGui::SameLine();
    if(ImGui::Button("Enabled"))
    {
        render_data.updateHDR(true);
        if(render_data.getExposure() <= 0.5f)
        {
            render_data.updateExposure(0.8f);
        }
    }
    ImGui::SameLine();
    if(ImGui::Button("Disabled"))
    {
        render_data.updateHDR(false);
        render_data.updateExposure(0.5f);
    }

    ImGui::BulletText("Set Exposure");
    ImGui::SameLine();
    float exposure = render_data.getExposure();
    ImGui::SliderFloat(" ", &exposure, 0.5f, 0.8f);
    if(exposure == 0.5f)
    {
        render_data.updateHDR(false);
    }
    if(exposure == 0.8f)
    {
        render_data.updateHDR(true);
    }
    render_data.updateExposure(exposure);

    bool bloom = render_data.getBloom();
    int bloom_str = render_data.getBloomStr();
    if (ImGui::Button("Set Bloom"))
        ImGui::OpenPopup("my_bloom_popup");
    if (ImGui::BeginPopup("my_bloom_popup"))
    {
        
        ImGui::Text("Set Bloom");
        ImGui::Checkbox("Enabled/Disabled", &bloom);
        render_data.updateBloom(bloom);

        ImGui::BulletText("Set Bloom Strength");
        ImGui::SameLine();
        ImGui::SliderInt(" ", &bloom_str, 2, 10);
        render_data.setBloomStr(bloom_str);

        if (ImGui::Button("Close"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }

    bool normal_render = render_data.getShadowGround();
    ImGui::BulletText("Show Ground Shadow");
    ImGui::SameLine();
    ImGui::Checkbox("Activated/Disabled", &normal_render);
    render_data.setRenderShadowGround(normal_render);

    bool parallax_render = render_data.getDispMapRender();
    ImGui::BulletText("Set Parallax");
    ImGui::SameLine();
    ImGui::Checkbox("Activate/Deactivate", &parallax_render);
    render_data.setDispMapRender(parallax_render);

    ImGui::Text("Asteroid Quantity");
    ImGui::Bullet();
    int asteroid_count = render_data.getAsteroidCount();
    ImGui::SliderInt("Count", &asteroid_count, 2500, 10000);
    render_data.setAsteroidCount(asteroid_count);
    
}