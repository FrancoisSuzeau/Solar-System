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

Overlay::Overlay(TTF_Font *police) : m_black_rect(0.05, 0.05),
m_grey_rect(0.05, 0.1),
m_track_music(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_Author_music(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_studio_music(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_move_info(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_position(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_speed_info(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_speed(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_time_info(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police)
{
    m_track_music.loadTTF("None");
    m_Author_music.loadTTF("None");
    m_studio_music.loadTTF("None");

    m_move_info.loadTTF("Navigation");
    m_position.loadTTF("Position :");
    m_speed_info.loadTTF("Speed :");
    m_speed.loadTTF("None");


    m_time_info.loadTTF("None");
    setTimeInformation();

    m_ancient_track = "None";
    m_ancient_radius = 0.0;
    m_ancient_speed = 0.0;
    m_ancient_time = "None";
    m_sec = 0;

    m_colorBlack = vec3(0.05);
    m_colorGrey = vec3(0.1);
}

Overlay::~Overlay()
{
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** displaySquares ********************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displaySquares(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, std::vector<glm::vec3> coordinates, Shader *square_shader)
{
    glm::mat4 save = modelview;

        modelview = translate(modelview, coordinates[0]); //from bottom right to bottom left
        m_grey_rect.display(projection, modelview, m_colorGrey, hdr, square_shader);

    modelview = save;

        modelview = translate(modelview, coordinates[1]); //from top right to top left
        m_black_rect.display(projection, modelview, m_colorBlack, hdr, square_shader);

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/******************************************************************** displayGeneralOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayGeneralOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, Shader *square_shader)
{   
    glm::mat4 save = modelview;
    float constance = 0.05f;

    /************************************************************************ horizontal bar *******************************************************************/
        float start_horizontal = 1.285f;

        if(square_shader != nullptr)
        {
            for (size_t i(0); i < 52; i++) // 25 * 2 + 2
            {
                std::vector<glm::vec3> coordinates1;
                std::vector<glm::vec3> coordinates2;

                    coordinates1.push_back(glm::vec3(start_horizontal, 0.720f, -0.01f));
                    coordinates1.push_back(glm::vec3(start_horizontal, 0.725f, 0.0f));
                    coordinates2.push_back(glm::vec3(start_horizontal, -0.720f, -0.01f));
                    coordinates2.push_back(glm::vec3(start_horizontal, -0.725f, 0.0f));

                    displaySquares(projection, modelview, hdr, coordinates1, square_shader);
                    displaySquares(projection, modelview, hdr, coordinates2, square_shader);

                start_horizontal = start_horizontal - constance;
       
            }

            modelview = save;

                modelview = translate(modelview, vec3(-1.285f, 0.725f, 0.0f)); //top left
                m_black_rect.display(projection, modelview, m_colorBlack, hdr, square_shader);

            modelview = save;

                modelview = translate(modelview, vec3(-1.285f, -0.725f, 0.0f)); //bottom left
                m_black_rect.display(projection, modelview, m_colorBlack, hdr, square_shader);

            modelview = save;
    //=======================================================================================================================================================

    /*************************************************************************** vertical bar ******************************************************************/

            float start_verticale = 0.675f; //minus one square because of the top bar

            for (size_t i(0); i < 28; i++) //goes to bottom bar
            {

                std::vector<glm::vec3> coordinates;

                    coordinates.push_back(glm::vec3(-1.285f, start_verticale, 0.0f));
                    coordinates.push_back(glm::vec3(-1.285f, start_verticale, -0.01f));
                    coordinates.push_back(glm::vec3(1.285f, start_verticale, 0.0f));
                    coordinates.push_back(glm::vec3(1.285f, start_verticale, -0.01f));

                    displaySquares(projection, modelview, hdr, coordinates, square_shader);

                start_verticale = start_verticale - constance;

            }
        }
          
        modelview = save;

    // //=======================================================================================================================================================
}

/***********************************************************************************************************************************************************************/
/********************************************************************** displayMusicOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayMusicOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, std::string const track, Shader *text_shader, Shader *square_shader)
{
    glm::mat4 save = modelview;
    float constance = 0.05f;

    float start = 1.265f;

    if(square_shader != nullptr)
    {
        for (size_t i(0); i < 10; i++)
        {
            /*In the first pass, we do not render the grey square because they will be cover by black square*/

                modelview = translate(modelview, vec3(start, -0.675f, 0.0f)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, m_colorBlack, hdr, square_shader);

            modelview = save;

                std::vector<glm::vec3> coordinates;

                    coordinates.push_back(glm::vec3(start, -0.620f, -0.01f));
                    coordinates.push_back(glm::vec3(start, -0.625f, 0.0f));
            
                    displaySquares(projection, modelview, hdr, coordinates, square_shader);

            start = start - constance;

            modelview = save;
        }

        modelview = save;

            /*We only draw the last one to make the border*/

            modelview = translate(modelview, vec3(1.265f - 0.05f*9, -0.670f, -0.01f)); //from bottom right to bottom left
            m_grey_rect.display(projection, modelview, m_colorGrey, hdr, square_shader);
    }

    modelview = save;

        if(track != m_ancient_track)
        {
            //std::string tmp = "Music :\n" + track;
            m_track_music.setText(track);
            m_ancient_track = track;
            setMusicInformation(track);
        }

        if(text_shader != nullptr)
        {
            modelview = translate(modelview, vec3(0.91f, -0.61f, -0.0f));
                modelview = scale(modelview, vec3(0.04f, 0.035f, 0.0f));
                m_track_music.renderText(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(0.85f, -0.64f, -0.0f));
                modelview = scale(modelview, vec3(0.02f, 0.035f, 0.0f));
                m_Author_music.renderText(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(0.91f, -0.67f, -0.0f));
                modelview = scale(modelview, vec3(0.04f, 0.035f, 0.0f));
                m_studio_music.renderText(projection, modelview, text_shader);

            modelview = save;

        }
        

}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayMoveInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayMoveInfoOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, glm::vec3 &position, float const speed, Shader *text_shader, Shader *square_shader)
{
    glm::mat4 save = modelview;
    float constance = 0.05f;

    float start_bottom_black_first = -1.265f;
    float start_bottom_black_second = -1.265f;
    float start_bottom_black_third = -1.265f;
    float start_bottom_black_fourth = -1.265f;
    float start_bottom_white = -1.265f;

    if(square_shader != nullptr)
    {
        for (size_t i(0); i < 10; i++)
        {
            /*In the first pass, we do not render the grey square because they will be cover by black square*/

                modelview = translate(modelview, vec3(start_bottom_black_first, -0.675f, 0.0f)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, m_colorBlack, hdr, square_shader);

            modelview = save;
            start_bottom_black_first = start_bottom_black_first + constance;
        }

        for (size_t i(0); i < 10; i++)
        {
            /*In the second pass, we do not render the grey square because they also will be cover by black square*/

                modelview = translate(modelview, vec3(start_bottom_black_second, -0.625f, 0.0f)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, m_colorBlack, hdr, square_shader);

            modelview = save;
            start_bottom_black_second = start_bottom_black_second + constance;
        }

        for (size_t i(0); i < 10; i++)
        {
            /*In the third pass, we do not render the grey square because they also will be cover by black square*/

                modelview = translate(modelview, vec3(start_bottom_black_third, -0.575f, 0.0f)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, m_colorBlack, hdr, square_shader);

            modelview = save;
            start_bottom_black_third = start_bottom_black_third + constance;
        }

        //fourth and last pass with white border on the top
        for (size_t i(0); i < 10; i++)
        {
                modelview = translate(modelview, vec3(start_bottom_white, -0.525f, -0.01f)); //from bottom right to bottom left
                m_grey_rect.display(projection, modelview, m_colorGrey, hdr, square_shader);

            modelview = save;
            start_bottom_white = start_bottom_white + constance;

                modelview = translate(modelview, vec3(start_bottom_black_fourth, -0.530f, 0.0f)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, m_colorBlack, hdr, square_shader);

            modelview = save;
            start_bottom_black_fourth = start_bottom_black_fourth + constance;
        }

        /*We only draw the lasts ones to make the border*/

        modelview = translate(modelview, vec3(-1.265f + 0.05f*9, -0.670f, -0.01f)); 
        m_grey_rect.display(projection, modelview, m_colorGrey, hdr, square_shader);

        modelview = save;

            modelview = translate(modelview, vec3(-1.265f + 0.05f*9, -0.625f, -0.01f)); 
            m_grey_rect.display(projection, modelview, m_colorGrey, hdr, square_shader);

        modelview = save;

            modelview = translate(modelview, vec3(-1.265f + 0.05f*9, -0.575f, -0.01f));
            m_grey_rect.display(projection, modelview, m_colorGrey, hdr, square_shader);
    }

    modelview = save;

        if(text_shader != nullptr)
        {
                modelview = translate(modelview, vec3(-1.03f, -0.515f, -0.0f));
                modelview = scale(modelview, vec3(0.05f, 0.05f, 0.0f));
                m_move_info.renderText(projection, modelview, text_shader);

            modelview = save;


                modelview = translate(modelview, vec3(-1.15f, -0.564f, -0.0f));
                modelview = scale(modelview, vec3(0.02f, 0.045f, 0.0f));
                m_position.renderText(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(-1.15f, -0.650f, -0.0f));
                modelview = scale(modelview, vec3(0.02f, 0.038f, 0.0f));
                m_speed_info.renderText(projection, modelview, text_shader);

            modelview = save;

            setSpeedInformation(speed);

                modelview = translate(modelview, vec3(-0.95f, -0.650f, -0.0f));
                modelview = scale(modelview, vec3(0.04f, 0.04f, 0.0f));
                m_speed.renderText(projection, modelview, text_shader);

            modelview = save;
        }

        
}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayTimeInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayTimeInfoOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, Shader *text_shader, Shader *square_shader)
{
    glm::mat4 save = modelview;
    float constance = 0.05f;

    float start_top_black_to_left = 0.0f;
    float start_top_white_to_left = 0.0f;

    float start_top_black_to_right = 0.05f;
    float start_top_white_to_right = 0.05f;

    if(square_shader != nullptr)
    {
        
        for (size_t i(0); i < 5; i++)
        {
                modelview = translate(modelview, vec3(start_top_white_to_left, 0.670f, -0.01f)); 
                m_grey_rect.display(projection, modelview, m_colorGrey, hdr, square_shader);

            modelview = save;
            start_top_white_to_left = start_top_white_to_left - constance;

                modelview = translate(modelview, vec3(start_top_black_to_left, 0.675f, 0.0f)); 
                m_black_rect.display(projection, modelview, m_colorBlack, hdr, square_shader);

            modelview = save;
            start_top_black_to_left = start_top_black_to_left - constance;
        }

        for (size_t i(0); i < 4; i++)
        {

                modelview = translate(modelview, vec3(start_top_white_to_right, 0.670f, -0.01f)); 
                m_grey_rect.display(projection, modelview, m_colorGrey, hdr, square_shader);

            modelview = save;
            start_top_white_to_right = start_top_white_to_right + constance;

                modelview = translate(modelview, vec3(start_top_black_to_right, 0.675f, 0.0f)); 
                m_black_rect.display(projection, modelview, m_colorBlack, hdr, square_shader);

            modelview = save;
            start_top_black_to_right = start_top_black_to_right + constance;
        }


            /*We only draw the lasts whites squares to make the border ont left and the right*/

            modelview = translate(modelview, vec3(0.0f - 0.043f*5, 0.670f, -0.01f)); 
            m_grey_rect.display(projection, modelview, m_colorGrey, hdr, square_shader);
        
        modelview = save;

            modelview = translate(modelview, vec3(0.0f + 0.043f * 5, 0.670f, -0.01f)); 
            m_grey_rect.display(projection, modelview, m_colorGrey, hdr, square_shader);

    }

    
    modelview = save;

        if(text_shader != nullptr)
        {
            setTimeInformation();

                modelview = translate(modelview, vec3(0.0f, 0.658f, -0.0f));
                modelview = scale(modelview, vec3(0.039f, 0.050f, 0.0f));
                m_time_info.renderText(projection, modelview, text_shader);

            modelview = save;
        }
        
}

/***********************************************************************************************************************************************************************/
/********************************************************************** setMusicInformation ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::setMusicInformation(std::string const track)
{
    if(track == "Mass Effect - Vigil")
    {
        m_Author_music.setText("Jack Wall");
        m_studio_music.setText("EA Games Soundtrack");
    }

    if(track == "Natural Splendor") 
    {
        m_Author_music.setText("Gerald M. Dorai");
        m_studio_music.setText("Le Phonarium - Nantes");
    }

    if(track == "Dying Star") 
    {
        m_Author_music.setText("Utho Riley");
        m_studio_music.setText("Symphonic Orchestral Music");
    }

    if(track == "Orizon Theme") 
    {
        m_Author_music.setText("Pedro Camacho");
        m_studio_music.setText("Star Citizen Soundtrack");
    }
    
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

        m_speed.setText(tmp);
        m_ancient_speed = speed;
    }

    
}

/***********************************************************************************************************************************************************************/
/********************************************************************** setTimeInformation ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::setTimeInformation()
{
    time_t local_time = time(0);
    std::string time = ctime(&local_time);
    tm *ltm = localtime(&local_time);

    if(time != m_ancient_time)
    {
        
        if(ltm->tm_sec >= m_sec + 8) //reduce updating refresh
        {
            m_time_info.setText(time);
            m_ancient_time = time;
            m_sec = ltm->tm_sec;
        }
        
    }

    if(ltm->tm_sec == 59)
    {
        m_sec = 0;
    }
}