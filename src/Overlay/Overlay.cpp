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

Overlay::Overlay(TTF_Font *police) :
m_rect(0.05, 0.1)
{
    std::string str_init[] = {  "None",
                                "None",
                                "None",
                                "Navigation",
                                "Position :",
                                "Speed :",
                                "None",
                                "None"
                                };

    for (int i = 0; i < 8; i++)
    {
        m_texts.push_back(new Text(3.0f, 0.2f, 6.0f, "../assets/font/aAtmospheric.ttf", police));
        assert(m_texts[i]);
        assert(m_texts[i]->loadTTF(str_init[i]));
    }

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

    m_ancient_radius = 0.0;
    m_ancient_speed = 0.0;

    m_colorBlack = vec3(0.05);
    m_colorGrey = vec3(0.1);
}

Overlay::~Overlay()
{
    for(std::vector<Text*>::iterator it = m_texts.begin(); it != m_texts.end(); ++it)
    {
        if(*it != nullptr)
        {
            delete *it;
        }
    }
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

    int track = render_data.getTrack();
    int vol = render_data.getVolume();
    bool pause_music = render_data.getPauseMusic();

    window_flags |= ImGuiWindowFlags_NoResize;

    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.04f, 0.04f, 0.04f, 1.0f));
    ImGui::SetNextWindowPos(ImVec2(render_data.getWidth() - 380, render_data.getHeight() - 170));
    ImGui::SetNextWindowSize(ImVec2(380, 170));
    
    ImGui::Begin("Music Information : ", NULL, window_flags);
    
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
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted("For now there only is one radio available until NASA engineers upgrade their Deep Space Network.");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }

    ImGui::PopStyleColor();
    ImGui::End();
    
    render_data.setVolume(vol);
    render_data.setTrackMusic(track);
    render_data.setPauseMusic(pause_music);
}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayMoveInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayMoveInfoOverlay(RenderData &render_data, glm::vec3 &position, float const speed)
{
    glm::mat4 save = render_data.getViewMat();
    float constance = 0.05f;

    float start_bottom_black_first = -1.265f;
    float start_bottom_black_second = -1.265f;
    float start_bottom_black_third = -1.265f;
    float start_bottom_black_fourth = -1.265f;
    float start_bottom_white = -1.265f;

    if(render_data.getShader("square") != nullptr)
    {
        for (size_t i(0); i < 10; i++)
        {
                m_rect.updatePosition(glm::vec3(start_bottom_black_first, -0.675f, 0.0f));
                m_rect.display(render_data, m_colorBlack);

            render_data.updateView(save);
            start_bottom_black_first = start_bottom_black_first + constance;
        }

        for (size_t i(0); i < 10; i++)
        {
                m_rect.updatePosition(glm::vec3(start_bottom_black_second, -0.625f, 0.0f));
                m_rect.display(render_data, m_colorBlack);

            render_data.updateView(save);
            start_bottom_black_second = start_bottom_black_second + constance;
        }

        for (size_t i(0); i < 10; i++)
        {

                m_rect.updatePosition(glm::vec3(start_bottom_black_third, -0.575f, 0.0f));
                m_rect.display(render_data, m_colorBlack);

            render_data.updateView(save);
            start_bottom_black_third = start_bottom_black_third + constance;
        }

        //fourth and last pass with white border on the top
        for (size_t i(0); i < 10; i++)
        {
                m_rect.updatePosition(glm::vec3(start_bottom_white, -0.525f, -0.01f));
                m_rect.display(render_data, m_colorGrey);

            render_data.updateView(save);
            start_bottom_white = start_bottom_white + constance;

                m_rect.updatePosition(glm::vec3(start_bottom_black_fourth, -0.530f, 0.0f));
                m_rect.display(render_data, m_colorBlack);

            render_data.updateView(save);
            start_bottom_black_fourth = start_bottom_black_fourth + constance;
        }

        m_rect.updatePosition(glm::vec3(-1.265f + 0.05f*9, -0.670f, -0.01f));
        m_rect.display(render_data, m_colorGrey);

        render_data.updateView(save);

            m_rect.updatePosition(glm::vec3(-1.265f + 0.05f*9, -0.625f, -0.01f));
            m_rect.display(render_data, m_colorGrey);

        render_data.updateView(save);

            m_rect.updatePosition(glm::vec3(-1.265f + 0.05f*9, -0.575f, -0.01f));
            m_rect.display(render_data, m_colorGrey);
    }

    render_data.updateView(save);

        if(render_data.getShader("text") != nullptr)
        {
            std::vector<glm::vec3> coordinates;
            coordinates.push_back(glm::vec3(-1.03f, -0.525f, -0.0f));
            coordinates.push_back(glm::vec3(-1.15f, -0.580f, -0.0f));
            coordinates.push_back(glm::vec3(-1.15f, -0.650f, -0.0f));
            coordinates.push_back(glm::vec3(-0.95f, -0.650f, -0.0f));

            std::vector<glm::vec3> scale_datas;
            scale_datas.push_back(glm::vec3(0.05f, 0.05f, 0.0f));
            scale_datas.push_back(glm::vec3(0.02f, 0.045f, 0.0f));
            scale_datas.push_back(glm::vec3(0.02f, 0.038f, 0.0f));
            scale_datas.push_back(glm::vec3(0.04f, 0.04f, 0.0f));

            setSpeedInformation(speed);

            for (int i = 3; i < 7; i++)
            {
                m_texts[i]->updatePosition(coordinates[i - 3]);
                m_texts[i]->updateScale(scale_datas[i - 3]);
                m_texts[i]->renderText(render_data);

                render_data.updateView(save);
            }

            render_data.updateView(save);
        }

        
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
    
    ImGui::Begin("Application Information : ", NULL, window_flags);

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
/********************************************************************** setSpeedInformation **************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::setSpeedInformation(float const speed)
{
    
    float value_perc = ((speed * 100)/200)/100;

    if(value_perc <= 0.0f)
    {
        value_perc = 0.0f;
    }

    if(m_ancient_speed != speed)
    {
        // recover the first two digits
        std::ostringstream oss_x;
        oss_x << std::setprecision(3) << value_perc;
        std::string tmp = oss_x.str() + " time light speed";

        assert(m_texts[6]->setText(tmp));
        m_ancient_speed = speed;
    }

    
}