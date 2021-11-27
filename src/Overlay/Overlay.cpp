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
void Overlay::displayMusicOverlay(RenderData &render_data, std::string const track)
{
    glm::mat4 save = render_data.getViewMat();
    float constance = 0.05f;

    float start = 1.265f;

    if(render_data.getShader("square") != nullptr)
    {
        for (size_t i(0); i < 9; i++)
        {
            /*In the first pass, we do not render the grey square because they will be cover by black square*/

                m_rect.updatePosition(glm::vec3(start, -0.675f, 0.0f));
                m_rect.display(render_data, m_colorBlack);

            render_data.updateView(save);
            
                std::vector<glm::vec3> coordinates;

                    coordinates.push_back(glm::vec3(start, -0.620f, -0.01f));
                    coordinates.push_back(glm::vec3(start, -0.625f, 0.0f));
            
                    displaySquares(render_data, coordinates);

            start = start - constance;

            render_data.updateView(save);
        }

        render_data.updateView(save);

            m_rect.updatePosition(glm::vec3(1.265f - 0.05f*8, -0.670f, -0.01f));
            m_rect.display(render_data, m_colorGrey);
    }

    render_data.updateView(save);

        if(track != m_ancient_track)
        {
            assert(m_texts[0]->setText(track));
            m_ancient_track = track;
            setMusicInformation(track);
        }

        if(render_data.getShader("text") != nullptr)
        {
            glm::vec3 coordinate(0.99f, -0.61f, -0.0f);
            glm::vec3 scale_data(0.04f, 0.035f, 0.0f);

            for (int i = 0; i < 3; i++)
            {
                m_texts[i]->updatePosition(coordinate);
                m_texts[i]->updateScale(scale_data);
                m_texts[i]->renderText(render_data);

                render_data.updateView(save);
                coordinate.y -= 0.03;
            }

            render_data.updateView(save);

        }
        

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
void Overlay::displayTimeInfoOverlay(RenderData &render_data)
{
    glm::mat4 save = render_data.getViewMat();
    float constance = 0.05f;

    float start_top_black_to_left = 0.0f;
    float start_top_white_to_left = 0.0f;

    float start_top_black_to_right = 0.05f;
    float start_top_white_to_right = 0.05f;

    if(render_data.getShader("square") != nullptr)
    {
        
        for (size_t i(0); i < 5; i++)
        {
                std::vector<glm::vec3> coordinates;
                coordinates.push_back(glm::vec3(start_top_white_to_left, 0.670f, -0.01f));
                coordinates.push_back(glm::vec3(start_top_black_to_left, 0.675f, 0.0f));
                displaySquares(render_data, coordinates);
               
            render_data.updateView(save);
            start_top_white_to_left = start_top_white_to_left - constance;
            start_top_black_to_left = start_top_black_to_left - constance;
        }

        for (size_t i(0); i < 4; i++)
        {
            std::vector<glm::vec3> coordinates;
            coordinates.push_back(glm::vec3(start_top_white_to_right, 0.670f, -0.01f));
            coordinates.push_back(glm::vec3(start_top_black_to_right, 0.675f, 0.0f));
            displaySquares(render_data, coordinates);

            render_data.updateView(save);
            start_top_white_to_right = start_top_white_to_right + constance;
            start_top_black_to_right = start_top_black_to_right + constance;
        }

        render_data.updateView(save);

            m_rect.updatePosition(glm::vec3(0.0f - 0.043f*5, 0.670f, -0.01f));
            m_rect.display(render_data, m_colorGrey);

        render_data.updateView(save);

            m_rect.updatePosition(glm::vec3(0.0f + 0.043f * 5, 0.670f, -0.01f));
            m_rect.display(render_data, m_colorGrey);

        render_data.updateView(save);

    }

    render_data.updateView(save);

        if(render_data.getShader("text") != nullptr)
        {
            setTimeInformation();

                m_texts[7]->updatePosition(glm::vec3(0.0f, 0.658f, -0.0f));
                m_texts[7]->updateScale(vec3(0.039f, 0.050f, 0.0f));
                m_texts[7]->renderText(render_data);

            render_data.updateView(save);
            
        }
        
}

/***********************************************************************************************************************************************************************/
/********************************************************************** setMusicInformation ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::setMusicInformation(std::string const track)
{
    if(track == "Mass Effect - Vigil")
    {
        assert(m_texts[1]->setText("Jack Wall"));
        assert(m_texts[2]->setText("EA Games Soundtrack"));
    }

    if(track == "Natural Splendor") 
    {
        assert(m_texts[1]->setText("Gerald M. Dorai"));
        assert(m_texts[2]->setText("Le Phonarium - Nantes"));
    }

    if(track == "Dying Star") 
    {
        assert(m_texts[1]->setText("Utho Riley"));
        assert(m_texts[2]->setText("Symphonic Orchestral Music"));
    }

    if(track == "Orizon Theme") 
    {
        assert(m_texts[1]->setText("Pedro Camacho"));
        assert(m_texts[2]->setText("Star Citizen Soundtrack"));
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

        assert(m_texts[6]->setText(tmp));
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
            assert(m_texts[7]->setText(time));
            m_ancient_time = time;
            m_sec = ltm->tm_sec;
        }
        
    }

    if(ltm->tm_sec == 59)
    {
        m_sec = 0;
    }
}