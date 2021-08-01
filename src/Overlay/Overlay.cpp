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
m_text_music(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_move_info(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag"),
m_time_info(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", "../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag")
{
    m_text_music.loadTTF("music");
    m_move_info.loadTTF("Move Information");
    m_time_info.loadTTF("Time Information");
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
void Overlay::displayMusicOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
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

        modelview = translate(modelview, vec3(0.85, -0.61, -0.0));
        modelview = scale(modelview, vec3(0.02, 0.035, 0.0));
        m_text_music.renderTextOverlay(projection, modelview);

    modelview = save;


}

/***********************************************************************************************************************************************************************/
/******************************************************************* displayMoveInfoOverlay ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Overlay::displayMoveInfoOverlay(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
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

        modelview = translate(modelview, vec3(-1.12, -0.515, -0.0));
        modelview = scale(modelview, vec3(0.03, 0.045, 0.0));
        m_move_info.renderTextOverlay(projection, modelview);

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

        modelview = translate(modelview, vec3(0.0, 0.668, -0.0));
        modelview = scale(modelview, vec3(0.03, 0.045, 0.0));
        m_time_info.renderTextOverlay(projection, modelview);

    modelview = save;
}