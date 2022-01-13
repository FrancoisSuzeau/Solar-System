/*
AUTHOR : SUZEAU François

DATE : 21/07/2021

MODULE : Overlay

NAMEFILE : Overlay.cpp

PURPOSE : class Overlay
*/

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "Overlay.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/

Overlay::Overlay() : m_rect(0.05, 0.1)
{

    map_music_data[0].title = "Mass Effect - Vigil";
    map_music_data[0].author = "Jack Wall";
    map_music_data[0].studio = "EA Games Soundtrack";
    map_music_data[1].title = "Natural Splendor";
    map_music_data[1].author = "Gerald M. Dorai";
    map_music_data[1].studio = "Le Phonarium - Nantes";
    map_music_data[2].title = "Dying Star";
    map_music_data[2].author = "Utho Riley";
    map_music_data[2].studio = "Symphonic Orchestral Music";
    map_music_data[3].title = "Orizon Theme";
    map_music_data[3].author = "Pedro Camacho";
    map_music_data[3].studio = "Star Citizen Soundtrack";

    map_nav_data["Sun"] = {ImVec4(1.0f, 1.0f, 0.0f, 1.0f), 0.0f};
    map_nav_data["Mercury"] = {ImVec4(0.502f, 0.502f, 0.502f, 1.0f), 0.019493f};
    map_nav_data["Venus"] = {ImVec4(1.0f, 0.894f, 0.710f, 1.0f), 0.0673764f};
    map_nav_data["Earth"] = {ImVec4(0.0f, 0.749f, 1.0f, 1.0f), 0.0820391f};
    map_nav_data["Mars"] = {ImVec4(0.698f, 0.133f, 0.133f, 1.0f), 0.0195781f};
    map_nav_data["Jupiter"] = {ImVec4(0.784f, 0.678f, 0.980f, 1.0f), 0.11756f};
    map_nav_data["Saturn"] = {ImVec4(1.0f, 0.808f, 0.604f, 1.0f), 0.0534512f};
    map_nav_data["Uranus"] = {ImVec4(0.454f, 0.815f, 0.945f, 1.0f), 0.047227f};
    map_nav_data["Neptune"] = {ImVec4(0.192f, 0.549f, 0.906f, 1.0f), 0.0604449f};

    m_ancient_radius = 0.0;
    m_ancient_speed = 0.0;

    m_colorBlack = vec3(0.05);
    m_colorGrey = vec3(0.1);
}

Overlay::~Overlay()
{
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** displaySquares ********************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displaySquares(RenderData &render_data, std::vector<glm::vec3> coordinates)
{
    glm::mat4 save = render_data.getViewMat();

        m_rect.updatePosition(coordinates[0]);
        m_rect.display(render_data, m_colorGrey);

    render_data.updateView(save);

        m_rect.updatePosition(coordinates[1]);
        m_rect.display(render_data, m_colorBlack);

    render_data.updateView(save);
}

/***********************************************************************************************************************************************************************/
/******************************************************************** displayGeneralOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayGeneralOverlay(RenderData &render_data)
{   
    glm::mat4 save = render_data.getViewMat();
    float constance = 0.05f;

    /************************************************************************ horizontal bar *******************************************************************/
        float start_horizontal = 1.285f;

        if(render_data.getShader("square") != nullptr)
        {
            glUseProgram(render_data.getShader("square")->getProgramID());

                render_data.getShader("square")->setInt("load", false);

            glUseProgram(0);

            for (size_t i(0); i < 52; i++) // 25 * 2 + 2
            {
                std::vector<glm::vec3> coordinates1;
                std::vector<glm::vec3> coordinates2;

                    coordinates1.push_back(glm::vec3(start_horizontal, 0.720f, -0.01f));
                    coordinates1.push_back(glm::vec3(start_horizontal, 0.725f, 0.0f));
                    coordinates2.push_back(glm::vec3(start_horizontal, -0.720f, -0.01f));
                    coordinates2.push_back(glm::vec3(start_horizontal, -0.725f, 0.0f));

                    displaySquares(render_data, coordinates1);
                    displaySquares(render_data, coordinates2);

                start_horizontal = start_horizontal - constance;

                render_data.updateView(save);
            }

            render_data.updateView(save);

                m_rect.updatePosition(glm::vec3(-1.285f, 0.725f, 0.0f));
                m_rect.display(render_data, m_colorBlack);

            render_data.updateView(save);

                m_rect.updatePosition(glm::vec3(-1.285f, -0.725f, 0.0f));
                m_rect.display(render_data, m_colorBlack);

            render_data.updateView(save);
    //=======================================================================================================================================================

    // /*************************************************************************** vertical bar ******************************************************************/

            float start_verticale = 0.675f; //minus one square because of the top bar

            for (size_t i(0); i < 28; i++) //goes to bottom bar
            {

                std::vector<glm::vec3> coordinates1;
                std::vector<glm::vec3> coordinates2;

                    coordinates1.push_back(glm::vec3(-1.285f, start_verticale, -0.01f));
                    coordinates1.push_back(glm::vec3(-1.285f, start_verticale, 0.0f));
                    coordinates2.push_back(glm::vec3(1.285f, start_verticale, -0.01f));
                    coordinates2.push_back(glm::vec3(1.285f, start_verticale, 0.0f));

                    displaySquares(render_data, coordinates1);
                    displaySquares(render_data, coordinates2);

                start_verticale = start_verticale - constance;

                render_data.updateView(save);
            }
        }
        
    render_data.updateView(save);
}

/***********************************************************************************************************************************************************************/
/********************************************************************** displayMusicOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayMusicInfo(RenderData &render_data)
{
    ImGuiWindowFlags window_flags = 0;
    ImGuiStyle& style = ImGui::GetStyle();

    int track = render_data.getTrack();
    int vol = render_data.getVolume();
    bool pause_music = render_data.getPauseMusic();

    window_flags |= ImGuiWindowFlags_NoResize;

    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.04f, 0.04f, 0.04f, 1.0f));
    ImGui::SetNextWindowPos(ImVec2(render_data.getWidth() - 380, render_data.getHeight() - 170));
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
    RenderData::HelpMarker(t_mp);

    style.FrameRounding = save_frame;
    style.GrabRounding = save_grab;

    ImGui::PopStyleColor();
    ImGui::End();
    
    render_data.setVolume(vol);
    render_data.setTrackMusic(track);
    render_data.setPauseMusic(pause_music);
}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayMoveInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayNavigation(RenderData &render_data)
{
    ImGuiWindowFlags window_flags = 0;
    ImGuiStyle& style = ImGui::GetStyle();

    window_flags |= ImGuiWindowFlags_NoResize;
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.04f, 0.04f, 0.04f, 1.0f));
    ImGui::SetNextWindowPos(ImVec2(0, render_data.getHeight() - 250));
    ImGui::SetNextWindowSize(ImVec2(380, 250));

    float save_frame = style.FrameRounding;
    float save_grab = style.GrabRounding;
    style.FrameRounding = 15;
    style.GrabRounding = 15;
    
    ImGui::Begin("Navigation", NULL, window_flags);

    float progress = render_data.getShipSpeed() / 200;

    
    ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
    ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
    ImGui::Text("Speed");

    float phase = Physique::getSolarConst(render_data.getShipPos());
    std::string unit[5] = {"W.m^-2", "KW.m^-2", "MW.m^-2", "GW.m^-2", "TW.m^-2"};
    int exponent = (int) log10(phase);
    int index = exponent;
    exponent = -exponent;
    phase *= pow(10, exponent - 1);
    static float values[90] = {};
    static int values_offset = 0;
    static double refresh_time = 0.0;
    if (refresh_time == 0.0)
        refresh_time = ImGui::GetTime();
    while (refresh_time < ImGui::GetTime())
    {
        values[values_offset] = phase;
        values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
        refresh_time += 1.0f / 40.0f;
    }
    ImGui::BulletText("Solar Radiation");
    ImGui::SameLine();
    std::string tmp = "Keep in mind that the value is display between 0 and 1 so you have to multiply by 10 000.\n(Example : for Earth\n-value display : 0.1362 W.m^-2\n-reality : 1 362 W.m^-2)";
    RenderData::HelpMarker(tmp);
    if(index - 9 < 5)
    {
        ImGui::PlotLines(unit[index - 9].c_str(), values, IM_ARRAYSIZE(values), values_offset, NULL, 0.0f, 1.0f, ImVec2(0, 40.0f));
    }
    else
    {
        float tmp[2] = {1.0, 1.0};
        ImGui::PlotLines("You're dead", tmp, IM_ARRAYSIZE(tmp), 0, NULL, 0.0f, 1.0f, ImVec2(0, 40.0f));
    }
    //TODO : make this with real scale
    
    float arr1[] = {0.0};
    float arr2[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};    
    if(render_data.getInfVal()[0] <= map_nav_data[render_data.getInfName()].min_grav_inf)
    {
        std::vector<float> dist_sun = {Physique::getDistanceFromCam("Sun", render_data.getShipPos())};
        float grav_inf = Physique::getGravInfluence("Sun", dist_sun)[0];
        arr1[0] = grav_inf;
        tmp = "Sun";
    }
    else
    {
        tmp = render_data.getInfName();
        std::vector<double> tmp_vect = render_data.getInfVal();
        arr1[0] = tmp_vect[0];
        for(int i = 1; i < (int)tmp_vect.size(); i++)
        {
            arr2[i-1] = tmp_vect[i];
        }
    }
    ImGui::BulletText("Gravitational Influence");
    ImGui::SameLine();
    ImGui::TextColored(map_nav_data[tmp].color_text, tmp.c_str());
    ImGui::SameLine();
    tmp = "Display the name of the body or the host name of the planetary disney.";
    RenderData::HelpMarker(tmp);
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.862f, 0.078f, 0.235f, 1.0f));
    ImGui::PlotHistogram("          ", arr1, IM_ARRAYSIZE(arr1), 0, " ", 0.0f, 1.0f, ImVec2(30, 80.0f));
    ImGui::SameLine();
    ImGui::PlotHistogram(" ", arr2, IM_ARRAYSIZE(arr2), 0, " ", 0.0f, 1.0f, ImVec2(200, 80.0f));
    ImGui::Text("Host");
    ImGui::SameLine();
    ImGui::Text("           Natural companion");
    ImGui::SameLine();
    tmp = "Those are for the natural moons of the host.";
    RenderData::HelpMarker(tmp);

    style.FrameRounding = save_frame;
    style.GrabRounding = save_grab;
    
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::End();
}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayTimeInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayAppInfo(RenderData &render_data)
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