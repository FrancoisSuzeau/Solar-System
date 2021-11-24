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
void Overlay::displaySquares(RenderData &render_data, std::vector<glm::vec3> coordinates, Shader *square_shader)
{
    glm::mat4 save = render_data.getViewMat();

        glm::mat4 tmp = render_data.getViewMat();
        tmp = translate(tmp, coordinates[0]); //from bottom right to bottom left
        render_data.updateView(tmp);
        m_rect.display(render_data.getProjectionMat(), render_data.getViewMat(), m_colorGrey, render_data.getHDR(), square_shader);

    render_data.updateView(save);

        tmp = render_data.getViewMat();
        tmp = translate(tmp, coordinates[1]); //from top right to top left
        render_data.updateView(tmp);
        m_rect.display(render_data.getProjectionMat(), render_data.getViewMat(), m_colorBlack, render_data.getHDR(), square_shader);

    render_data.updateView(save);
}

/***********************************************************************************************************************************************************************/
/******************************************************************** displayGeneralOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayGeneralOverlay(RenderData &render_data, Shader *square_shader)
{   
    glm::mat4 save = render_data.getViewMat();
    float constance = 0.05f;

    /************************************************************************ horizontal bar *******************************************************************/
        float start_horizontal = 1.285f;

        if(square_shader != nullptr)
        {
            glUseProgram(square_shader->getProgramID());

                square_shader->setInt("load", false);

            glUseProgram(0);

            for (size_t i(0); i < 52; i++) // 25 * 2 + 2
            {
                std::vector<glm::vec3> coordinates1;
                std::vector<glm::vec3> coordinates2;

                    coordinates1.push_back(glm::vec3(start_horizontal, 0.720f, -0.01f));
                    coordinates1.push_back(glm::vec3(start_horizontal, 0.725f, 0.0f));
                    coordinates2.push_back(glm::vec3(start_horizontal, -0.720f, -0.01f));
                    coordinates2.push_back(glm::vec3(start_horizontal, -0.725f, 0.0f));

                    displaySquares(render_data, coordinates1, square_shader);
                    displaySquares(render_data, coordinates2, square_shader);

                start_horizontal = start_horizontal - constance;

                render_data.updateView(save);
            }

            render_data.updateView(save);
            //TODO change square.display()
                render_data.getViewMat() = translate(render_data.getViewMat(), vec3(-1.285f, 0.725f, 0.0f)); //top left
                m_rect.display(render_data.getProjectionMat(), render_data.getViewMat(), m_colorBlack, render_data.getHDR(), square_shader);

            render_data.updateView(save);

                render_data.getViewMat() = translate(render_data.getViewMat(), vec3(-1.285f, -0.725f, 0.0f)); //bottom left
                m_rect.display(render_data.getProjectionMat(), render_data.getViewMat(), m_colorBlack, render_data.getHDR(), square_shader);

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

                    displaySquares(render_data, coordinates1, square_shader);
                    displaySquares(render_data, coordinates2, square_shader);

                start_verticale = start_verticale - constance;

                render_data.updateView(save);
            }
        }
        
    render_data.updateView(save);
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************** displayMusicOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayMusicOverlay(RenderData &render_data, std::string const track, Shader *text_shader, Shader *square_shader)
{
    glm::mat4 save = render_data.getViewMat();
    float constance = 0.05f;

    float start = 1.265f;

    if(square_shader != nullptr)
    {
        for (size_t i(0); i < 9; i++)
        {
            /*In the first pass, we do not render the grey square because they will be cover by black square*/

                glm::mat4 tmp = render_data.getViewMat();
                tmp = translate(tmp, glm::vec3(start, -0.675f, 0.0f)); //from bottom right to bottom left
                render_data.updateView(tmp);
                m_rect.display(render_data.getProjectionMat(), render_data.getViewMat(), m_colorBlack, render_data.getHDR(), square_shader);

            render_data.updateView(save);
            
                std::vector<glm::vec3> coordinates;

                    coordinates.push_back(glm::vec3(start, -0.620f, -0.01f));
                    coordinates.push_back(glm::vec3(start, -0.625f, 0.0f));
            
                    displaySquares(render_data, coordinates, square_shader);

            start = start - constance;

            render_data.updateView(save);
        }

        render_data.updateView(save);

            /*We only draw the last one to make the border*/
            glm::mat4 tmp = render_data.getViewMat();
            tmp = translate(tmp, glm::vec3(1.265f - 0.05f*8, -0.670f, -0.01f)); //from bottom right to bottom left
            render_data.updateView(tmp);
            m_rect.display(render_data.getProjectionMat(), render_data.getViewMat(), m_colorGrey, render_data.getHDR(), square_shader);
    }

    render_data.updateView(save);

        if(track != m_ancient_track)
        {
            assert(m_texts[0]->setText(track));
            m_ancient_track = track;
            setMusicInformation(track);
        }

        // if(text_shader != nullptr)
        // {
        //     view = translate(view, vec3(0.99f, -0.61f, -0.0f));
        //         view = scale(view, vec3(0.04f, 0.035f, 0.0f));
        //         m_texts[0]->renderText(projection, view, text_shader);

        //     view = save;

        //         view = translate(view, vec3(0.93f, -0.64f, -0.0f));
        //         view = scale(view, vec3(0.02f, 0.035f, 0.0f));
        //         m_texts[1]->renderText(projection, view, text_shader);

        //     view = save;

        //         view = translate(view, vec3(0.99f, -0.67f, -0.0f));
        //         view = scale(view, vec3(0.04f, 0.035f, 0.0f));
        //         m_texts[2]->renderText(projection, view, text_shader);

        //     view = save;

        // }
        

}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayMoveInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayMoveInfoOverlay(glm::mat4 &projection, glm::mat4 &view, bool hdr, glm::vec3 &position, float const speed, Shader *text_shader, Shader *square_shader)
{
    glm::mat4 save = view;
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

                view = translate(view, vec3(start_bottom_black_first, -0.675f, 0.0f)); //from bottom right to bottom left
                m_rect.display(projection, view, m_colorBlack, hdr, square_shader);

            view = save;
            start_bottom_black_first = start_bottom_black_first + constance;
        }

        for (size_t i(0); i < 10; i++)
        {
            /*In the second pass, we do not render the grey square because they also will be cover by black square*/

                view = translate(view, vec3(start_bottom_black_second, -0.625f, 0.0f)); //from bottom right to bottom left
                m_rect.display(projection, view, m_colorBlack, hdr, square_shader);

            view = save;
            start_bottom_black_second = start_bottom_black_second + constance;
        }

        for (size_t i(0); i < 10; i++)
        {
            /*In the third pass, we do not render the grey square because they also will be cover by black square*/

                view = translate(view, vec3(start_bottom_black_third, -0.575f, 0.0f)); //from bottom right to bottom left
                m_rect.display(projection, view, m_colorBlack, hdr, square_shader);

            view = save;
            start_bottom_black_third = start_bottom_black_third + constance;
        }

        //fourth and last pass with white border on the top
        for (size_t i(0); i < 10; i++)
        {
                view = translate(view, vec3(start_bottom_white, -0.525f, -0.01f)); //from bottom right to bottom left
                m_rect.display(projection, view, m_colorGrey, hdr, square_shader);

            view = save;
            start_bottom_white = start_bottom_white + constance;

                view = translate(view, vec3(start_bottom_black_fourth, -0.530f, 0.0f)); //from bottom right to bottom left
                m_rect.display(projection, view, m_colorBlack, hdr, square_shader);

            view = save;
            start_bottom_black_fourth = start_bottom_black_fourth + constance;
        }

        /*We only draw the lasts ones to make the border*/

        view = translate(view, vec3(-1.265f + 0.05f*9, -0.670f, -0.01f)); 
        m_rect.display(projection, view, m_colorGrey, hdr, square_shader);

        view = save;

            view = translate(view, vec3(-1.265f + 0.05f*9, -0.625f, -0.01f)); 
            m_rect.display(projection, view, m_colorGrey, hdr, square_shader);

        view = save;

            view = translate(view, vec3(-1.265f + 0.05f*9, -0.575f, -0.01f));
            m_rect.display(projection, view, m_colorGrey, hdr, square_shader);
    }

    view = save;

        if(text_shader != nullptr)
        {
                view = translate(view, vec3(-1.03f, -0.515f, -0.0f));
                view = scale(view, vec3(0.05f, 0.05f, 0.0f));
                m_texts[3]->renderText(projection, view, text_shader);

            view = save;


                view = translate(view, vec3(-1.15f, -0.564f, -0.0f));
                view = scale(view, vec3(0.02f, 0.045f, 0.0f));
                m_texts[4]->renderText(projection, view, text_shader);

            view = save;

                view = translate(view, vec3(-1.15f, -0.650f, -0.0f));
                view = scale(view, vec3(0.02f, 0.038f, 0.0f));
                m_texts[5]->renderText(projection, view, text_shader);

            view = save;

            setSpeedInformation(speed);

                view = translate(view, vec3(-0.95f, -0.650f, -0.0f));
                view = scale(view, vec3(0.04f, 0.04f, 0.0f));
                m_texts[6]->renderText(projection, view, text_shader);

            view = save;
        }

        
}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayTimeInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayTimeInfoOverlay(glm::mat4 &projection, glm::mat4 &view, bool hdr, Shader *text_shader, Shader *square_shader)
{
    glm::mat4 save = view;
    float constance = 0.05f;

    float start_top_black_to_left = 0.0f;
    float start_top_white_to_left = 0.0f;

    float start_top_black_to_right = 0.05f;
    float start_top_white_to_right = 0.05f;

    if(square_shader != nullptr)
    {
        
        for (size_t i(0); i < 5; i++)
        {
                view = translate(view, vec3(start_top_white_to_left, 0.670f, -0.01f)); 
                m_rect.display(projection, view, m_colorGrey, hdr, square_shader);

            view = save;
            start_top_white_to_left = start_top_white_to_left - constance;

                view = translate(view, vec3(start_top_black_to_left, 0.675f, 0.0f)); 
                m_rect.display(projection, view, m_colorBlack, hdr, square_shader);

            view = save;
            start_top_black_to_left = start_top_black_to_left - constance;
        }

        for (size_t i(0); i < 4; i++)
        {

                view = translate(view, vec3(start_top_white_to_right, 0.670f, -0.01f)); 
                m_rect.display(projection, view, m_colorGrey, hdr, square_shader);

            view = save;
            start_top_white_to_right = start_top_white_to_right + constance;

                view = translate(view, vec3(start_top_black_to_right, 0.675f, 0.0f)); 
                m_rect.display(projection, view, m_colorBlack, hdr, square_shader);

            view = save;
            start_top_black_to_right = start_top_black_to_right + constance;
        }


            /*We only draw the lasts whites squares to make the border ont left and the right*/

            view = translate(view, vec3(0.0f - 0.043f*5, 0.670f, -0.01f)); 
            m_rect.display(projection, view, m_colorGrey, hdr, square_shader);
        
        view = save;

            view = translate(view, vec3(0.0f + 0.043f * 5, 0.670f, -0.01f)); 
            m_rect.display(projection, view, m_colorGrey, hdr, square_shader);

    }

    
    view = save;

        if(text_shader != nullptr)
        {
            setTimeInformation();

                view = translate(view, vec3(0.0f, 0.658f, -0.0f));
                view = scale(view, vec3(0.039f, 0.050f, 0.0f));
                m_texts[7]->renderText(projection, view, text_shader);

            view = save;
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