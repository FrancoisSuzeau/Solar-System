/*
AUTHOR : SUZEAU François

DATE : 02/08/2021

MODULE : Settings

NAMEFILE : Settings.cpp

PURPOSE : class Settings
*/
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Settings.hpp"

using namespace glm;

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
        assert(this->loadTextureFromFile(it[0]));
    }

    index = 0;

}

Settings::~Settings()
{
    for(std::vector<imguiTexture_datas>::iterator it = textures_data.begin(); it != textures_data.end(); it++)
    {
        glDeleteTextures(1, &it[0].text_id);
        if(glIsTexture(it[0].text_id) == GL_FALSE)
        {
            std::cout << ">> TEXTURE :: delete " << it[0].filepath << " : SUCESS" << std::endl;
        }
    }
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
            // this->manageNavigation(render_data);
            ImGui::EndTabItem();
        }
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("HUD"))
        {
            style.FramePadding = frame_padding_save;
            // this->manageHUD(render_data);
            ImGui::EndTabItem();
        }
        style.FramePadding = ImVec2(25, 3);
        if (ImGui::BeginTabItem("Performance"))
        {
            style.FramePadding = frame_padding_save;
            // this->managePerformance(render_data);
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
// void Settings::manageHUD(RenderData &render_data)
// {
//     ImGui::Text("General");
//     bool over_rend = render_data.getOverlayRender();
//     ImGui::Bullet();
//     ImGui::SameLine();
//     ImGui::Checkbox("Display Overlay", &over_rend);
//     render_data.setRenderOverlay(over_rend);

//     bool name_rend = render_data.getRenderName();
//     ImGui::Bullet();
//     ImGui::SameLine();
//     ImGui::Checkbox("Display Name", &name_rend);
//     render_data.setRenderName(name_rend);

//     bool info_rend = render_data.getRenderInfo();
//     ImGui::Bullet();
//     ImGui::SameLine();
//     ImGui::Checkbox("Display Planete Information", &info_rend);
//     ImGui::SameLine();
//     RenderData::HelpMarker("It is possible to activate this functionality with the 'SPACE' key.");
//     render_data.setRenderInfo(info_rend);
//     ImGui::Separator();

//     RenderData::HelpMarker("More in coming like the possibility to manage the style of the different windows.");

// }

/***********************************************************************************************************************************************************************/
/*********************************************************************** managePerformance *****************************************************************************/
/***********************************************************************************************************************************************************************/
// void Settings::managePerformance(RenderData &render_data)
// {
//     ImGui::Text("Rendering");

//     ImGui::BulletText("Set HDR");
//     ImGui::SameLine();
//     if(ImGui::Button("Enabled"))
//     {
//         render_data.updateHDR(true);
//         if(render_data.getExposure() <= 0.5f)
//         {
//             render_data.updateExposure(0.8f);
//         }
//     }
//     ImGui::SameLine();
//     if(ImGui::Button("Disabled"))
//     {
//         render_data.updateHDR(false);
//         render_data.updateExposure(0.5f);
//     }

//     ImGui::BulletText("Set Exposure");
//     ImGui::SameLine();
//     float exposure = render_data.getExposure();
//     ImGui::SliderFloat(" ", &exposure, 0.5f, 0.8f);
//     if(exposure == 0.5f)
//     {
//         render_data.updateHDR(false);
//     }
//     if(exposure == 0.8f)
//     {
//         render_data.updateHDR(true);
//     }
//     render_data.updateExposure(exposure);

//     bool bloom = render_data.getBloom();
//     int bloom_str = render_data.getBloomStr();
//     if (ImGui::Button("Set Bloom"))
//         ImGui::OpenPopup("my_bloom_popup");
//     if (ImGui::BeginPopup("my_bloom_popup"))
//     {
        
//         ImGui::Text("Set Bloom");
//         ImGui::Checkbox("Enabled/Disabled", &bloom);
//         render_data.updateBloom(bloom);

//         ImGui::BulletText("Set Bloom Strength");
//         ImGui::SameLine();
//         ImGui::SliderInt(" ", &bloom_str, 2, 10);
//         render_data.setBloomStr(bloom_str);

//         if (ImGui::Button("Close"))
//             ImGui::CloseCurrentPopup();
//         ImGui::EndPopup();
//     }
//     ImGui::Separator();

//     ImGui::Text("Textures");
//     bool normal_render = render_data.getShadowGround();
//     ImGui::BulletText("Show Ground Shadow");
//     ImGui::SameLine();
//     ImGui::Checkbox("Activated/Disabled", &normal_render);
//     render_data.setRenderShadowGround(normal_render);

//     bool parallax_render = render_data.getDispMapRender();
//     ImGui::BulletText("Set Parallax");
//     ImGui::SameLine();
//     ImGui::Checkbox("Activate/Deactivate", &parallax_render);
//     render_data.setDispMapRender(parallax_render);
//     ImGui::Separator();

//     ImGui::Text("Asteroid Quantity");
//     ImGui::SameLine();
//     RenderData::HelpMarker("Astroid count influence the performance so you can now chose the amount.");
//     ImGui::Bullet();
//     int asteroid_count = render_data.getAsteroidCount();
//     ImGui::SliderInt("Count", &asteroid_count, 2000, 10000);
//     render_data.setAsteroidCount(asteroid_count);
//     ImGui::Separator();

//     static int selected = -1;
//     int fps[] = {25, 60, 120, 144, 240};
//     const char* names[] = { "25", "60", "120", "144", "240" };
//     if (ImGui::Button("Select.."))
//         ImGui::OpenPopup("my_select_popup");
//     ImGui::SameLine();
//     ImGui::Text("FPS Count : ");
//     ImGui::SameLine();
//     ImGui::TextUnformatted(selected == -1 ? "default" : names[selected]);
//     if (ImGui::BeginPopup("my_select_popup"))
//     {
//         if(ImGui::Selectable("default"))
//             selected = -1;
//         ImGui::Separator();
//         for (int i = 0; i < IM_ARRAYSIZE(names); i++)
//             if (ImGui::Selectable(names[i]))
//                 selected = i;
//         ImGui::EndPopup();
//     }

//     if((selected >= 0) && (selected < 5))
//     {
//         render_data.setFPS(fps[selected]);
//     }
//     else
//     {
//         render_data.setFPS(50);
//     }
    
// }

/***********************************************************************************************************************************************************************/
/*********************************************************************** manageNavigation ******************************************************************************/
/***********************************************************************************************************************************************************************/
// void Settings::manageNavigation(RenderData &render_data)
// {
//     float spacing = ImGui::GetStyle().ItemInnerSpacing.x;

//     float distance = render_data.getDist();

//     ImGui::BulletText("Choose your vessel : ");
//     ImGui::SameLine();
//     RenderData::HelpMarker("Choose between " + std::to_string(textures_data.size()) + " skins available.");
//     ImGui::PushButtonRepeat(true);
//     if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { index--; }
//     this->verifIndex();
//     ImGui::SameLine(0.0f, spacing);
//     // ImGui::Text("%d", index);
//     if(ImGui::ImageButton((void*)(intptr_t)textures_data[index].text_id, ImVec2(textures_data[index].img_width *0.5f, textures_data[index].img_height * 0.5f), ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f)))
//     {
//         if(index != render_data.getIndexShip())
//         {
//             render_data.setIndexShip(index);
//             render_data.setChangeModel(true);
//         }
//     }
//     ImGui::SameLine(0.0f, spacing);
//     if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { index++; }
//     this->verifIndex();
//     ImGui::PopButtonRepeat();
//     ImGui::Text(textures_data[index].name_disp.c_str());

//     ImGui::Separator();

//     ImGui::BulletText("Distance from ship");
//     if(ImGui::SliderFloat(" ", &distance, min_distance[index], 10.0f))
//     {
//         render_data.setDist(distance);
//     }
    
//     RenderData::HelpMarker("More in coming like the possibility to jump directly near to a body.");
// }

/***********************************************************************************************************************************************************************/
/******************************************************************** loadTextureFromFile ******************************************************************************/
/***********************************************************************************************************************************************************************/
bool Settings::loadTextureFromFile(imguiTexture_datas &data)
{
    unsigned char* image_data = stbi_load(data.filepath.c_str(), &data.img_width, &data.img_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    glGenTextures(1, &data.text_id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, data.text_id);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.img_width, data.img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
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