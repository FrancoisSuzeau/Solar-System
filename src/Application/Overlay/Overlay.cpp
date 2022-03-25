/*
AUTHOR : SUZEAU François

DATE : 21/07/2021

MODULE : Application::Overlay

NAMEFILE : Overlay.cpp

PURPOSE :   - say to rendersquare how to render a frame all around the screen
            - render Application informations
            - render music informations

*/

#include "Overlay.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/

Overlay::Overlay()
{

    map_music_data[0].title = "Mass Effect - Vigil";
    map_music_data[0].author = "Jack Wall";
    map_music_data[0].studio = "EA Games Soundtrack";
    map_music_data[1].title = "Critical Mass";
    map_music_data[1].author = " ";
    map_music_data[1].studio = "Epic Hybrid Orchestra";
    map_music_data[2].title = "Natural Splendor";
    map_music_data[2].author = "Gerald M. Dorai";
    map_music_data[2].studio = "Le Phonarium - Nantes";
    map_music_data[3].title = "Dying Star";
    map_music_data[3].author = "Utho Riley";
    map_music_data[3].studio = "Symphonic Orchestral Music";
    map_music_data[4].title = "Orizon Theme";
    map_music_data[4].author = "Pedro Camacho";
    map_music_data[4].studio = "Star Citizen Soundtrack";
    map_music_data[5].title = "Engine of Creation";
    map_music_data[5].author = "Utho Riley";
    map_music_data[5].studio = "Epic Hybrid Orchestra";
    map_music_data[6].title = "Mass Effect - Map Theme";
    map_music_data[6].author = "Jack Wall";
    map_music_data[6].studio = "EA Games Soundtrack";
    map_music_data[7].title = "Unbound";
    map_music_data[7].author = "Utho Riley";
    map_music_data[7].studio = "Epic Hybrid Orchestra";
    map_music_data[8].title = "Dreamscape";
    map_music_data[8].author = " ";
    map_music_data[8].studio = " ";
    map_music_data[9].title = "Two Moons";
    map_music_data[9].author = "Bobby Richards";
    map_music_data[9].studio = "YouTube Audio Library";
    

    // map_nav_data["Sun"] = {ImVec4(1.0f, 1.0f, 0.0f, 1.0f), 0.0f};
    // map_nav_data["Mercury"] = {ImVec4(0.502f, 0.502f, 0.502f, 1.0f), 0.019493f};
    // map_nav_data["Venus"] = {ImVec4(1.0f, 0.894f, 0.710f, 1.0f), 0.0673764f};
    // map_nav_data["Earth"] = {ImVec4(0.0f, 0.749f, 1.0f, 1.0f), 0.0820391f};
    // map_nav_data["Mars"] = {ImVec4(0.698f, 0.133f, 0.133f, 1.0f), 0.0195781f};
    // map_nav_data["Jupiter"] = {ImVec4(0.784f, 0.678f, 0.980f, 1.0f), 0.11756f};
    // map_nav_data["Saturn"] = {ImVec4(1.0f, 0.808f, 0.604f, 1.0f), 0.0534512f};
    // map_nav_data["Uranus"] = {ImVec4(0.454f, 0.815f, 0.945f, 1.0f), 0.047227f};
    // map_nav_data["Neptune"] = {ImVec4(0.192f, 0.549f, 0.906f, 1.0f), 0.0604449f};

}

Overlay::~Overlay()
{

}

/***********************************************************************************************************************************************************************/
/*********************************************************************** clean ********************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::clean()
{
    if(m_square_ptr != nullptr)
    {
        delete m_square_ptr;
        m_square_ptr = nullptr;
    }

    if(m_square_renderer != nullptr)
    {
        m_square_renderer->clean();
        delete m_square_renderer;
        m_square_renderer = nullptr;
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** displaySquares ********************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displaySquares(DataManager &data_manager, std::vector<glm::vec3> coordinates)
{   
    m_square_ptr->updateSize(glm::vec3(0.5));

    m_square_ptr->updateColor(0.2f); //less grey black
    m_square_ptr->updatePosition(coordinates[0]);
    m_square_ptr->transform(glm::vec3(0.f), nullptr);
    if((m_square_ptr != nullptr) && (m_square_renderer != nullptr))
    {
        m_square_ptr->sendToShader(data_manager);
        m_square_renderer->render(data_manager, m_square_ptr);
    }

    m_square_ptr->updateColor(0.05f); //grey black
    m_square_ptr->updatePosition(coordinates[1]);
    m_square_ptr->transform(glm::vec3(0.f), nullptr);
    if((m_square_ptr != nullptr) && (m_square_renderer != nullptr))
    {
        m_square_ptr->sendToShader(data_manager);
        m_square_renderer->render(data_manager, m_square_ptr);
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************** renderHorizontal ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::renderHorizontal(DataManager &data_manager, float side)
{
    for (float i(-1.5f); i < 2.f; i = i + 0.5f)
    {
        std::vector<glm::vec3> coordinates;
        coordinates.push_back(glm::vec3(i, side, 0.f));
        float tmp = (side > 0.f) ? 1.42f : -1.42f;
        coordinates.push_back(glm::vec3(i, tmp, 0.1f));
        this->displaySquares(data_manager, coordinates);
    }
}


/***********************************************************************************************************************************************************************/
/******************************************************************** renderVertical ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::renderVertical(DataManager &data_manager, float side)
{
    for (float i(-1.f); i < 2.f; i++)
    {
        std::vector<glm::vec3> coordinates;
        coordinates.push_back(glm::vec3(side, i, 0.f));
        float tmp = (side > 0.f) ? 2.16f : -2.16f;
        coordinates.push_back(glm::vec3(tmp, i, 0.1f));
        this->displaySquares(data_manager, coordinates);
    }
}

/***********************************************************************************************************************************************************************/
/******************************************************************** renderEdges **************************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::renderEdges(DataManager &data_manager)
{   
    //up
    this->renderHorizontal(data_manager, 1.4f);
    //bottom
    this->renderHorizontal(data_manager, -1.4f);
    //left
    this->renderVertical(data_manager, -2.11f);
    //right
    this->renderVertical(data_manager, 2.11f);
}

/***********************************************************************************************************************************************************************/
/********************************************************************** renderMusicInfo ********************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::renderMusicInfo(DataManager &data_manager)
{
    ImGuiWindowFlags window_flags = 0;
    ImGuiStyle& style = ImGui::GetStyle();

    int track = data_manager.getTrack();
    int vol = data_manager.getVolume();
    bool pause_music = data_manager.getPause();

    window_flags |= ImGuiWindowFlags_NoResize;

    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.04f, 0.04f, 0.04f, 1.0f));
    ImGui::SetNextWindowPos(ImVec2(data_manager.getWidth() - 380, data_manager.getHeight() - 170));
    ImGui::SetNextWindowSize(ImVec2(380, 170));

    float save_frame = style.FrameRounding;
    float save_grab = style.GrabRounding;
    style.FrameRounding = 15;
    style.GrabRounding = 15;
    
    ImGui::Begin("Music Information", NULL, window_flags);
    
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Title :");
    ImGui::SameLine();
        
    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
    ImGui::PushButtonRepeat(true);
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { track--; }
    ImGui::SameLine(0.0f, spacing);
    ImGui::Text(map_music_data[track].title.c_str());
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { track++; }
    ImGui::PopButtonRepeat();

    std::string tmp = "Author :    " + map_music_data[track].author;
    ImGui::Text(tmp.c_str());

    tmp = "Studio :    " + map_music_data[track].studio;
    ImGui::Text(tmp.c_str());
    
    ImGui::SliderInt("Volume", &vol, 0, 128);
    

    ImGui::Checkbox("Mute music", &pause_music);

    const char* items[] = { "Epic Orchestra", "-Error Canal Transmission-", "-Error Canal Transmission-", "-Error Canal Transmission-"};
    static int item_current = 0;
    ImGui::Combo("Radio", &item_current, items, IM_ARRAYSIZE(items));

    ImGui::SameLine();
    std::string t_mp = "For now there only is one radio available until NASA engineers upgrade their Deep Space Network.";
    // RenderData::HelpMarker(t_mp);

    style.FrameRounding = save_frame;
    style.GrabRounding = save_grab;

    ImGui::PopStyleColor();
    ImGui::End();
    
    data_manager.setVolume(vol);
    data_manager.setTrack(track);
    data_manager.setPause(pause_music);
}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayMoveInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
// void Overlay::displayNavigation(RenderData &render_data)
// {
//     ImGuiWindowFlags window_flags = 0;
//     ImGuiStyle& style = ImGui::GetStyle();

//     window_flags |= ImGuiWindowFlags_NoResize;
//     ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.04f, 0.04f, 0.04f, 1.0f));
//     ImGui::SetNextWindowPos(ImVec2(0, render_data.getHeight() - 250));
//     ImGui::SetNextWindowSize(ImVec2(380, 250));

//     float save_frame = style.FrameRounding;
//     float save_grab = style.GrabRounding;
//     style.FrameRounding = 15;
//     style.GrabRounding = 15;
    
//     ImGui::Begin("Navigation", NULL, window_flags);

//     float progress = render_data.getShipSpeed() / 200;

    
//     ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
//     ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
//     ImGui::Text("Speed");

//     float phase = Physique::getSolarConst(render_data.getShipPos());
//     std::string unit[5] = {"W.m^-2", "KW.m^-2", "MW.m^-2", "GW.m^-2", "TW.m^-2"};
//     int exponent = (int) log10(phase);
//     int index = exponent;
//     exponent = -exponent;
//     phase *= pow(10, exponent - 1);
//     static float values[90] = {};
//     static int values_offset = 0;
//     static double refresh_time = 0.0;
//     if (refresh_time == 0.0)
//         refresh_time = ImGui::GetTime();
//     while (refresh_time < ImGui::GetTime())
//     {
//         values[values_offset] = phase;
//         values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
//         refresh_time += 1.0f / 40.0f;
//     }
//     ImGui::BulletText("Solar Radiation");
//     ImGui::SameLine();
//     std::string tmp = "Keep in mind that the value is display between 0 and 1 so you have to multiply by 10 000.\n(Example : for Earth\n-value display : 0.1362 W.m^-2\n-reality : 1 362 W.m^-2)";
//     RenderData::HelpMarker(tmp);
//     if(index - 9 < 5)
//     {
//         ImGui::PlotLines(unit[index - 9].c_str(), values, IM_ARRAYSIZE(values), values_offset, NULL, 0.0f, 1.0f, ImVec2(0, 40.0f));
//     }
//     else
//     {
//         float tmp[2] = {1.0, 1.0};
//         ImGui::PlotLines("You're dead", tmp, IM_ARRAYSIZE(tmp), 0, NULL, 0.0f, 1.0f, ImVec2(0, 40.0f));
//     }
//     //TODO : make this with real scale
    
//     float arr1[] = {0.0};
//     float arr2[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};    
//     if(render_data.getInfVal()[0] <= map_nav_data[render_data.getInfName()].min_grav_inf)
//     {
//         std::vector<float> dist_sun = {Physique::getDistanceFromCam("Sun", render_data.getShipPos())};
//         float grav_inf = Physique::getGravInfluence("Sun", dist_sun)[0];
//         arr1[0] = grav_inf;
//         tmp = "Sun";
//     }
//     else
//     {
//         tmp = render_data.getInfName();
//         std::vector<double> tmp_vect = render_data.getInfVal();
//         arr1[0] = tmp_vect[0];
//         for(int i = 1; i < (int)tmp_vect.size(); i++)
//         {
//             arr2[i-1] = tmp_vect[i];
//         }
//     }
//     ImGui::BulletText("Gravitational Influence");
//     ImGui::SameLine();
//     ImGui::TextColored(map_nav_data[tmp].color_text, tmp.c_str());
//     ImGui::SameLine();
//     tmp = "Display the name of the body or the host name of the planetary system.";
//     RenderData::HelpMarker(tmp);
//     ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.862f, 0.078f, 0.235f, 1.0f));
//     ImGui::PlotHistogram("          ", arr1, IM_ARRAYSIZE(arr1), 0, " ", 0.0f, 1.0f, ImVec2(30, 80.0f));
//     ImGui::SameLine();
//     ImGui::PlotHistogram(" ", arr2, IM_ARRAYSIZE(arr2), 0, " ", 0.0f, 1.0f, ImVec2(200, 80.0f));
//     ImGui::Text("Host");
//     ImGui::SameLine();
//     ImGui::Text("           Natural companion");
//     ImGui::SameLine();
//     tmp = "Those are for the natural moons of the host.";
//     RenderData::HelpMarker(tmp);

//     style.FrameRounding = save_frame;
//     style.GrabRounding = save_grab;
    
//     ImGui::PopStyleColor();
//     ImGui::PopStyleColor();
//     ImGui::End();
// }

/***********************************************************************************************************************************************************************/
/******************************************************************* renderAppInfo ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::renderAppInfo()
{
    time_t local_time = time(0);
    std::string time = ctime(&local_time);

    ImGuiWindowFlags window_flags = 0;
    ImGuiIO& io = ImGui::GetIO();

    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.04f, 0.04f, 0.04f, 1.0f));
    ImGui::SetNextWindowPos(ImVec2(0.0, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(380, 150));
    
    ImGui::Begin("Application Information", NULL, window_flags);

    ImGui::Text("Application Information : ");

    std::string tmp = "Time : " + time;
    ImGui::Bullet();
    ImGui::Text(tmp.c_str());

    ImGui::Bullet();
    ImGui::Text("Application average : %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    if (ImGui::TreeNode("Mouse State"))
    {
        if (ImGui::IsMousePosValid())
            ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
        else
            ImGui::Text("Mouse pos: <INVALID>");
        ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);

        int count = IM_ARRAYSIZE(io.MouseDown);
        ImGui::Text("Mouse down:");         for (int i = 0; i < count; i++) if (ImGui::IsMouseDown(i))      { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
        ImGui::TreePop();
    }

    ImGui::PopStyleColor();
    ImGui::End();
}



/***********************************************************************************************************************************************************************/
/******************************************************************* initOverlayAssets ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::initOverlayAssets(Renderer *square_rend, Square *square)
{
    m_square_renderer = square_rend;
    m_square_ptr = square;
}