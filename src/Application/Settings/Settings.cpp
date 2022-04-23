/*
AUTHOR : SUZEAU François

DATE : 02/08/2021

MODULE : Settings

NAMEFILE : Settings.cpp

PURPOSE : class Settings

*/

#include "Settings.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Settings::Settings()
{
    textures_data.push_back({0, 0, 0, "../../assets/textures/imguiSpaceship.png", "  Star Hunter - Class Eviscerator"});
    textures_data.push_back({0, 0, 0, "../../assets/textures/imguiDonut.png", "  Donut X37 - Class Yummi Yummi !"});
    textures_data.push_back({0, 0, 0, "../../assets/textures/imguiSpaceshuttle.png", "Spaceshuttle Atlantis Fuel Tank Booster"});

    min_distance.push_back(2.0f);
    min_distance.push_back(1.180f);
    min_distance.push_back(1.6f);

    for(std::vector<imguiTexture_datas>::iterator it = textures_data.begin(); it != textures_data.end(); it++)
    {
        assert(Loader::loadWithStbi(it[0].filepath, it[0].text_id, it[0].img_width, it[0].img_height));
    }

    index = 0;

}

Settings::~Settings()
{
    
}

/***********************************************************************************************************************************************************************/
/************************************************************************** clean *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::clean()
{
    for(std::vector<imguiTexture_datas>::iterator it = textures_data.begin(); it != textures_data.end(); it++)
    {
        if(glIsTexture(it[0].text_id) == GL_TRUE)
        {
            glDeleteTextures(1, &it[0].text_id);
            it[0].text_id = 0;
        }
    }

    std::cout << ">> SETTINGS TEXTURES : DESTROY COMPLETE " << std::endl;
}

/***********************************************************************************************************************************************************************/
/************************************************************************** manageSettings *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::manageSettings(DataManager &data_manager)
{
    ImGuiWindowFlags window_flags = 0;
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 frame_padding_save = style.FramePadding;
    
    window_flags |= ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowPos(ImVec2(data_manager.getWidth()/2 - 200, data_manager.getHeight()/2 - 200));
    ImGui::SetNextWindowSize(ImVec2(400, 400));
    
    
    ImGui::Begin("Settings", NULL, window_flags);

    
    if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
    {
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("Navigation Options"))
        {
            style.FramePadding = frame_padding_save;
            this->manageNavigation(data_manager);
            ImGui::EndTabItem();
        }
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("HUD"))
        {
            style.FramePadding = frame_padding_save;
            this->manageHUD(data_manager);
            ImGui::EndTabItem();
        }
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("Performance"))
        {
            style.FramePadding = frame_padding_save;
            this->managePerformance(data_manager);
            ImGui::EndTabItem();
        }
        
        style.FramePadding = frame_padding_save;
        ImGui::EndTabBar();
    }
    style.FramePadding = frame_padding_save;

    ImGui::Separator();

    // if(ImGui::Button("Save Configuration", ImVec2(385.0f, 30.0f)))
    // {
    //     Saving::writeConfig(render_data);
    // }

    if(ImGui::Button("Stop Simulation", ImVec2(385.0f, 30.0f)))
    {
        data_manager.setTerminate(true);
    }

    ImGui::End();
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* manageHUD *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::manageHUD(DataManager &data_manager)
{
    ImGui::Text("General");
    bool over_rend = data_manager.getRenderOverlay();
    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::Checkbox("Display Overlay", &over_rend);
    data_manager.setRenderOverlay(over_rend);

    bool name_rend = data_manager.getRenderName();
    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::Checkbox("Display Name", &name_rend);
    data_manager.setRenderName(name_rend);

    bool info_rend = data_manager.getRenderInfo();
    ImGui::Bullet();
    ImGui::SameLine();
    ImGui::Checkbox("Display Planete Information", &info_rend);
    ImGui::SameLine();
    // RenderData::HelpMarker("It is possible to activate this functionality with the 'SPACE' key.");
    data_manager.setRenderInfo(info_rend);
    ImGui::Separator();

//     RenderData::HelpMarker("More in coming like the possibility to manage the style of the different windows.");

}

/***********************************************************************************************************************************************************************/
/*********************************************************************** managePerformance *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::managePerformance(DataManager &data_manager)
{
    ImGui::Text("Rendering");

    ImGui::BulletText("Highlight Sun");
    ImGui::SameLine();
    if(ImGui::Button("Enabled"))
    {
        data_manager.setHilightSun(true);
    }
    ImGui::SameLine();
    if(ImGui::Button("Disabled"))
    {
        data_manager.setHilightSun(false);
    }

    bool bloom = data_manager.getBloom();
    int bloom_str = data_manager.getBloomStrength();
    if (ImGui::Button("Set Bloom"))
        ImGui::OpenPopup("my_bloom_popup");
    if (ImGui::BeginPopup("my_bloom_popup"))
    {
        ImGui::Text("Set Bloom");
        ImGui::Checkbox("Enabled/Disabled", &bloom);
        data_manager.setBloom(bloom);

        ImGui::BulletText("Set Bloom Strength");
        ImGui::SameLine();
        ImGui::SliderInt(" ", &bloom_str, 2, 10);
        data_manager.setBloomStrength(bloom_str);

        if (ImGui::Button("Close"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }

    bool render_shadow = data_manager.getRenderShadow();
    ImGui::Checkbox("Render shadow", &render_shadow);
    data_manager.setRenderShadow(render_shadow);

    ImGui::Separator();

    ImGui::Text("Textures");
    bool normal_render = data_manager.getRenderNormal();
    ImGui::BulletText("Show Ground Shadow");
    ImGui::SameLine();
    ImGui::Checkbox("Activated/Disabled", &normal_render);
    data_manager.setRenderNormal(normal_render);

    ImGui::Text("Asteroid Quantity");
    ImGui::SameLine();
    // RenderData::HelpMarker("Astroid count influence the performance so you can now chose the amount.");
    ImGui::Bullet();
    int asteroid_count = data_manager.getAsteroidCount();
    ImGui::SliderInt("Count", &asteroid_count, 2000, 10000);
    data_manager.setAsteroidCount(asteroid_count);
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
        data_manager.setFps(fps[selected]);
    }
    else
    {
        data_manager.setFps(60);
    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** manageNavigation ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::manageNavigation(DataManager &data_manager)
{
    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;

    float distance = data_manager.getDistancteFromShip();

    ImGui::BulletText("Choose your vessel : ");
    // ImGui::SameLine();
//     RenderData::HelpMarker("Choose between " + std::to_string(textures_data.size()) + " skins available.");
    ImGui::PushButtonRepeat(true);
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { index--; }
    this->verifIndex();
    ImGui::SameLine(0.0f, spacing);
    // ImGui::Text("%d", index);
    if(ImGui::ImageButton((void*)(intptr_t)textures_data[index].text_id, ImVec2(textures_data[index].img_width *0.5f, textures_data[index].img_height * 0.5f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f)))
    {
        if(index != data_manager.getIndexShip())
        {
            data_manager.setIndexShip(index);
            data_manager.setChangeSkin(true);
        }
    }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { index++; }
    this->verifIndex();
    ImGui::PopButtonRepeat();
    ImGui::Text(textures_data[index].name_disp.c_str());

    ImGui::Separator();

    ImGui::BulletText("Distance from ship");
    if(ImGui::SliderFloat(" ", &distance, min_distance[index], 10.0f))
    {
        data_manager.setDistanceFromShip(distance);
    }
    
//     RenderData::HelpMarker("More in coming like the possibility to jump directly near to a body.");
}

void Settings::verifIndex()
{
    if(index < 0)
    {
        index = textures_data.size() - 1;
    }

    if(index >= (int) textures_data.size())
    {
        index = 0;
    }
}