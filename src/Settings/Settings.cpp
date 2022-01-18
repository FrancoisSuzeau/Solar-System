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
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 frame_padding_save = style.FramePadding;
    
    window_flags |= ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowPos(ImVec2(render_data.getWidth()/2 - 200, render_data.getHeight()/2 - 175));
    ImGui::SetNextWindowSize(ImVec2(400, 350));
    
    
    ImGui::Begin("Settings", NULL, window_flags);

    
    if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
    {
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("Navigation Options"))
        {
            style.FramePadding = frame_padding_save;
            this->manageNavigation(render_data);
            ImGui::EndTabItem();
        }
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("HUD"))
        {
            style.FramePadding = frame_padding_save;
            this->manageHUD(render_data);
            ImGui::EndTabItem();
        }
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("Performance"))
        {
            style.FramePadding = frame_padding_save;
            this->managePerformance(render_data);
            ImGui::EndTabItem();
        }
        
        style.FramePadding = frame_padding_save;
        ImGui::EndTabBar();
    }
    style.FramePadding = frame_padding_save;

    ImGui::Separator();

    if(ImGui::Button("Save Configuration", ImVec2(385.0f, 30.0f)))
    {
        Saving::writeConfig(render_data);
    }

    if(ImGui::Button("Stop Simulation", ImVec2(385.0f, 30.0f)))
    {
        render_data.setTerminate(true);
    }

    ImGui::End();
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* manageHUD *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::manageHUD(RenderData &render_data)
{
    ImGui::Text("General");
    bool over_rend = render_data.getOverlayRender();
    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::Checkbox("Display Overlay", &over_rend);
    render_data.setRenderOverlay(over_rend);

    bool name_rend = render_data.getRenderName();
    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::Checkbox("Display Name", &name_rend);
    render_data.setRenderName(name_rend);

    bool info_rend = render_data.getRenderInfo();
    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::Checkbox("Display Planete Information", &info_rend);
    ImGui::SameLine();
    RenderData::HelpMarker("It is possible to activate this functionality with the 'SPACE' key.");
    render_data.setRenderInfo(info_rend);
    ImGui::Separator();

    RenderData::HelpMarker("More in coming like the possibility to manage the style of the different windows.");

}

/***********************************************************************************************************************************************************************/
/*********************************************************************** managePerformance *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::managePerformance(RenderData &render_data)
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
    ImGui::Separator();

    ImGui::Text("Textures");
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
    ImGui::Separator();

    ImGui::Text("Asteroid Quantity");
    ImGui::SameLine();
    RenderData::HelpMarker("Astroid count influence the performance so you can now chose the amount.");
    ImGui::Bullet();
    int asteroid_count = render_data.getAsteroidCount();
    ImGui::SliderInt("Count", &asteroid_count, 2000, 10000);
    render_data.setAsteroidCount(asteroid_count);
    ImGui::Separator();

    static int selected = -1;
    int fps[] = {25, 60, 120, 144, 240};
    const char* names[] = { "25", "60", "120", "144", "240" };
    if (ImGui::Button("Select.."))
        ImGui::OpenPopup("my_select_popup");
    ImGui::SameLine();
    ImGui::Text("FPS Count : ");
    ImGui::SameLine();
    ImGui::TextUnformatted(selected == -1 ? "default" : names[selected]);
    if (ImGui::BeginPopup("my_select_popup"))
    {
        if(ImGui::Selectable("default"))
            selected = -1;
        ImGui::Separator();
        for (int i = 0; i < IM_ARRAYSIZE(names); i++)
            if (ImGui::Selectable(names[i]))
                selected = i;
        ImGui::EndPopup();
    }

    if((selected >= 0) && (selected < 5))
    {
        render_data.setFPS(fps[selected]);
    }
    else
    {
        render_data.setFPS(50);
    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** manageNavigation ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::manageNavigation(RenderData &render_data)
{
    RenderData::HelpMarker("More in coming like the possibility to jump directly near to a body.");
}