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

Overlay::Overlay() : m_black_rect(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.05),
m_grey_rect(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.1),
m_track_music(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_Author_music(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_studio_music(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_move_info(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_position(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_position_info_x(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_position_info_y(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_position_info_z(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_speed_info(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_speed(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_time_info(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag")
{
    m_track_music.loadTTF("None");
    m_Author_music.loadTTF("None");
    m_studio_music.loadTTF("None");

    m_move_info.loadTTF("Move Information");
    m_position.loadTTF("Position :");
    m_position_info_x.loadTTF("None");
    m_position_info_y.loadTTF("None");
    m_position_info_z.loadTTF("None");
    m_speed_info.loadTTF("Speed :");
    m_speed.loadTTF("None");


    m_time_info.loadTTF("None");
    setTimeInformation();

    m_ancient_track = "None";
    m_ancient_radius = 0.0;
    ancient_x = "None";
    ancient_y = "None";
    ancient_z = "None";
    m_ancient_speed = 0.0;
    m_ancient_time = "None";
    m_sec = 0;
}

Overlay::~Overlay()
{
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************** displayGeneralOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayGeneralOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
{   
    glm::mat4 save = modelview;
    float constance = 0.05;

    /************************************************************************ horizontal bar *******************************************************************/
        float start_top_black = 1.285;
        float start_top_white = 1.285;
        
        float start_bottom_black = 1.285;
        float start_bottom_white = 1.285;

        for (size_t i(0); i < 52; i++) // 25 * 2 + 2
        {
            //top bar
                modelview = translate(modelview, vec3(start_top_white, 0.720, -0.01)); //from bottom right to bottom left
                m_grey_rect.display(projection, modelview, hdr);

            modelview = save;
            start_top_white = start_top_white - constance;

                modelview = translate(modelview, vec3(start_top_black, 0.725, 0.0)); //from top right to top left
                m_black_rect.display(projection, modelview, hdr);

            modelview = save;
            start_top_black = start_top_black - constance;

            //bottom bar
                modelview = translate(modelview, vec3(start_bottom_white, -0.720, -0.01)); //from bottom right to bottom left
                m_grey_rect.display(projection, modelview, hdr);

            modelview = save;
            start_bottom_white = start_bottom_white - constance;

                modelview = translate(modelview, vec3(start_bottom_black, -0.725, 0.0)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, hdr);

            modelview = save;
            start_bottom_black = start_bottom_black - constance;
        }

            modelview = translate(modelview, vec3(-1.285, 0.725, 0.0)); //top left
            m_black_rect.display(projection, modelview, hdr);

        modelview = save;

            modelview = translate(modelview, vec3(-1.285, -0.725, 0.0)); //bottom left
            m_black_rect.display(projection, modelview, hdr);

        modelview = save;
    //=======================================================================================================================================================

    /*************************************************************************** vertical bar ******************************************************************/

            float start_left_black = 0.675; //minus one square because of the top bar
            float start_left_white = 0.675; //minus one square because of the top bar

            float start_right_black = 0.675; //minus one square because of the top bar
            float start_right_white = 0.675; //minus one square because of the top bar

            for (size_t i(0); i < 28; i++) //goes to bottom bar
            {
                //left bar
                    modelview = translate(modelview, vec3(-1.285, start_left_black, 0.0)); ////from top left to bottom left
                    m_black_rect.display(projection, modelview, hdr);

                start_left_black = start_left_black - constance;
                modelview = save;

                    modelview = translate(modelview, vec3(-1.285, start_left_white, -0.01)); ////from top left to bottom left
                    m_grey_rect.display(projection, modelview, hdr);

                start_left_white = start_left_white - constance;
                modelview = save;

                //right bar
                    modelview = translate(modelview, vec3(1.285, start_right_black, 0.0)); //from top right to bottom right
                    m_black_rect.display(projection, modelview, hdr);

                start_right_black = start_right_black - constance;
                modelview = save;

                    modelview = translate(modelview, vec3(1.285, start_right_white, -0.01)); ////from top left to bottom left
                    m_grey_rect.display(projection, modelview, hdr);

                start_right_white = start_right_white - constance;
                modelview = save;
            }
            
            modelview = save;

    // //=======================================================================================================================================================
}

/***********************************************************************************************************************************************************************/
/********************************************************************** displayMusicOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayMusicOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, std::string const track)
{
    glm::mat4 save = modelview;
    float constance = 0.05;

    float start_bottom_black_first = 1.265;
    float start_bottom_black_second = 1.265;
    float start_bottom_white = 1.265;

        for (size_t i(0); i < 10; i++)
        {
            /*In the first pass, we do not render the grey square because they will be cover by black square*/

                modelview = translate(modelview, vec3(start_bottom_black_first, -0.675, 0.0)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, hdr);

            modelview = save;
            start_bottom_black_first = start_bottom_black_first - constance;
        }

        for (size_t i(0); i < 10; i++)
        {
                modelview = translate(modelview, vec3(start_bottom_white, -0.620, -0.01)); //from bottom right to bottom left
                m_grey_rect.display(projection, modelview, hdr);

            modelview = save;
            start_bottom_white = start_bottom_white - constance;

                modelview = translate(modelview, vec3(start_bottom_black_second, -0.625, 0.0)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, hdr);

            modelview = save;
            start_bottom_black_second = start_bottom_black_second - constance;
        }
        
    modelview = save;

        /*We only draw the last one to make the border*/

        modelview = translate(modelview, vec3(1.265 - 0.05*9, -0.670, -0.01)); //from bottom right to bottom left
        m_grey_rect.display(projection, modelview, hdr);

    modelview = save;

        if(track != m_ancient_track)
        {
            //std::string tmp = "Music :\n" + track;
            m_track_music.setText(track);
            m_ancient_track = track;
            setMusicInformation(track);
        }

        modelview = translate(modelview, vec3(0.91, -0.61, -0.0));
        modelview = scale(modelview, vec3(0.04, 0.035, 0.0));
        m_track_music.renderTextOverlay(projection, modelview);

    modelview = save;

        modelview = translate(modelview, vec3(0.85, -0.64, -0.0));
        modelview = scale(modelview, vec3(0.02, 0.035, 0.0));
        m_Author_music.renderTextOverlay(projection, modelview);

    modelview = save;

        modelview = translate(modelview, vec3(0.91, -0.67, -0.0));
        modelview = scale(modelview, vec3(0.04, 0.035, 0.0));
        m_studio_music.renderTextOverlay(projection, modelview);

    modelview = save;


}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayMoveInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayMoveInfoOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, glm::vec3 &position, float const speed)
{
    glm::mat4 save = modelview;
    float constance = 0.05;

    float start_bottom_black_first = -1.265;
    float start_bottom_black_second = -1.265;
    float start_bottom_black_third = -1.265;
    float start_bottom_black_fourth = -1.265;
    float start_bottom_white = -1.265;

        for (size_t i(0); i < 10; i++)
        {
            /*In the first pass, we do not render the grey square because they will be cover by black square*/

                modelview = translate(modelview, vec3(start_bottom_black_first, -0.675, 0.0)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, hdr);

            modelview = save;
            start_bottom_black_first = start_bottom_black_first + constance;
        }

        for (size_t i(0); i < 10; i++)
        {
            /*In the second pass, we do not render the grey square because they also will be cover by black square*/

                modelview = translate(modelview, vec3(start_bottom_black_second, -0.625, 0.0)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, hdr);

            modelview = save;
            start_bottom_black_second = start_bottom_black_second + constance;
        }

        for (size_t i(0); i < 10; i++)
        {
            /*In the third pass, we do not render the grey square because they also will be cover by black square*/

                modelview = translate(modelview, vec3(start_bottom_black_third, -0.575, 0.0)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, hdr);

            modelview = save;
            start_bottom_black_third = start_bottom_black_third + constance;
        }

        //fourth and last pass with white border on the top
        for (size_t i(0); i < 10; i++)
        {
                modelview = translate(modelview, vec3(start_bottom_white, -0.525, -0.01)); //from bottom right to bottom left
                m_grey_rect.display(projection, modelview, hdr);

            modelview = save;
            start_bottom_white = start_bottom_white + constance;

                modelview = translate(modelview, vec3(start_bottom_black_fourth, -0.530, 0.0)); //from bottom right to bottom left
                m_black_rect.display(projection, modelview, hdr);

            modelview = save;
            start_bottom_black_fourth = start_bottom_black_fourth + constance;
        }

        /*We only draw the lasts ones to make the border*/

        modelview = translate(modelview, vec3(-1.265 + 0.05*9, -0.670, -0.01)); 
        m_grey_rect.display(projection, modelview, hdr);

    modelview = save;

        modelview = translate(modelview, vec3(-1.265 + 0.05*9, -0.625, -0.01)); 
        m_grey_rect.display(projection, modelview, hdr);

    modelview = save;

        modelview = translate(modelview, vec3(-1.265 + 0.05*9, -0.575, -0.01));
        m_grey_rect.display(projection, modelview, hdr);

    modelview = save;

        modelview = translate(modelview, vec3(-1.03, -0.515, -0.0));
        modelview = scale(modelview, vec3(0.05, 0.05, 0.0));
        m_move_info.renderTextOverlay(projection, modelview);

    modelview = save;

    setPostionInformation(position, speed);

        modelview = translate(modelview, vec3(-1.15, -0.564, -0.0));
        modelview = scale(modelview, vec3(0.02, 0.045, 0.0));
        m_position.renderTextOverlay(projection, modelview);

    modelview = save;

        modelview = translate(modelview, vec3(-1.17, -0.594, -0.0));
        modelview = scale(modelview, vec3(0.01, 0.045, 0.0));
        m_position_info_x.renderTextOverlay(projection, modelview);

    modelview = save;

        modelview = translate(modelview, vec3(-1.17, -0.624, -0.0));
        modelview = scale(modelview, vec3(0.01, 0.045, 0.0));
        m_position_info_y.renderTextOverlay(projection, modelview);

    modelview = save;

        modelview = translate(modelview, vec3(-1.17, -0.654, -0.0));
        modelview = scale(modelview, vec3(0.01, 0.045, 0.0));
        m_position_info_z.renderTextOverlay(projection, modelview);

    modelview = save;

        modelview = translate(modelview, vec3(-0.92, -0.564, -0.0));
        modelview = scale(modelview, vec3(0.02, 0.038, 0.0));
        m_speed_info.renderTextOverlay(projection, modelview);

    modelview = save;

    setSpeedInformation(speed);

        modelview = translate(modelview, vec3(-0.92, -0.614, -0.0));
        modelview = scale(modelview, vec3(0.04, 0.058, 0.0));
        m_speed.renderTextOverlay(projection, modelview);

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayTimeInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayTimeInfoOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
{
    glm::mat4 save = modelview;
    float constance = 0.05;

    float start_top_black_to_left = 0;
    float start_top_white_to_left = 0;

    float start_top_black_to_right = 0.05;
    float start_top_white_to_right = 0.05;

        for (size_t i(0); i < 5; i++)
        {
                modelview = translate(modelview, vec3(start_top_white_to_left, 0.670, -0.01)); 
                m_grey_rect.display(projection, modelview, hdr);

            modelview = save;
            start_top_white_to_left = start_top_white_to_left - constance;

                modelview = translate(modelview, vec3(start_top_black_to_left, 0.675, 0.0)); 
                m_black_rect.display(projection, modelview, hdr);

            modelview = save;
            start_top_black_to_left = start_top_black_to_left - constance;
        }

        for (size_t i(0); i < 4; i++)
        {

                modelview = translate(modelview, vec3(start_top_white_to_right, 0.670, -0.01)); 
                m_grey_rect.display(projection, modelview, hdr);

            modelview = save;
            start_top_white_to_right = start_top_white_to_right + constance;

                modelview = translate(modelview, vec3(start_top_black_to_right, 0.675, 0.0)); 
                m_black_rect.display(projection, modelview, hdr);

            modelview = save;
            start_top_black_to_right = start_top_black_to_right + constance;
        }


        /*We only draw the lasts whites squares to make the border ont left and the right*/

        modelview = translate(modelview, vec3(0 - 0.043*5, 0.670, -0.01)); 
        m_grey_rect.display(projection, modelview, hdr);
    
    modelview = save;

        modelview = translate(modelview, vec3(0 + 0.043 * 5, 0.670, -0.01)); 
        m_grey_rect.display(projection, modelview, hdr);
    
    modelview = save;

        setTimeInformation();

        modelview = translate(modelview, vec3(0.0, 0.658, -0.0));
        modelview = scale(modelview, vec3(0.039, 0.050, 0.0));
        m_time_info.renderTextOverlay(projection, modelview);

    modelview = save;
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

    if(track == "Star Citizen - ArcCorp Theme")
    {
        m_Author_music.setText("P. Macedo Camacho");
        m_studio_music.setText("Star Citizen Soundtrack");
    }
    
    if(track == "Space Suite Generic 02")
    {
        m_Author_music.setText("Darren Lambourne");
        m_studio_music.setText("Star Citizen Soundtrack");
    }

    if(track == "The Darkness")
    {
        m_Author_music.setText("P. Macedo Camacho");
        m_studio_music.setText("Star Citizen Soundtrack");
    }
    if(track == "Into the Void") 
    {
        m_Author_music.setText("P. Macedo Camacho");
        m_studio_music.setText("Star Citizen Soundtrack");
    }

    if(track == "Natural Splendor") 
    {
        m_Author_music.setText("Gerald M. Dorai");
        m_studio_music.setText("Le Phonarium - Nantes");
    }
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************** setPostionInformation **************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::setPostionInformation(glm::vec3 &position, float const speed)
{
    float x = position[0];
    float y = position[1];
    float z = position[2];
    double r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
    double r = std::sqrt(r_squarre);
    
    if( (r + (10.0 + speed * 10) <= m_ancient_radius) || (r - (10.0 + speed * 10) >= m_ancient_radius))
    {
        //recover the first two digits
        std::ostringstream oss_x;
        oss_x << std::setprecision(3) << x;
        std::string tmp_x = "x : " + oss_x.str();

        std::ostringstream oss_y;
        oss_y << std::setprecision(3) << y;
        std::string tmp_y = "y : " + oss_y.str();

        std::ostringstream oss_z;
        oss_z << std::setprecision(3) << z;
        std::string tmp_z = "z : " + oss_z.str();

        if(ancient_x != oss_x.str())
        {
            m_position_info_x.setText(tmp_x);
            ancient_x = oss_x.str();
        }
        if(ancient_y != oss_y.str())
        {
            m_position_info_y.setText(tmp_y);
            ancient_y = oss_y.str();
        }
        if(ancient_z != oss_z.str())
        {
            m_position_info_z.setText(tmp_z);
            ancient_z = oss_z.str();
        }

        m_ancient_radius = r;
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************** setSpeedInformation **************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::setSpeedInformation(float const speed)
{
    double light_speed = 299792458;
    double new_light_speed = light_speed * speed;

    if(m_ancient_speed != speed)
    {
        std::string tmp = std::to_string(new_light_speed) + "m/s";
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