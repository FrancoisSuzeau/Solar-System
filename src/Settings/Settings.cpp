/*
AUTHOR : SUZEAU François

DATE : 02/08/2021

MODULE : Settings

NAMEFILE : Settings.cpp

PURPOSE : class Settings
*/

#include "Settings.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Settings::Settings() : m_black_rect(0.05, 0.1),
m_grey_rect(0.05, 0.7),
m_titre(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf"),
m_quit(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf"),
m_hdr(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf"),
m_exposure(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf"),
m_speed(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf"),
m_music_playing(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf"),
m_music_volume(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf"),
m_overlay_display(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf"),
m_info_planete(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf")
{
    m_titre.loadTTF("Settings");
    m_quit.loadTTF("Quit Simulation");
    m_hdr.loadTTF("HDR : ON / OFF");
    m_exposure.loadTTF("Exposure : - / +");
    m_speed.loadTTF("Speed : - / +");
    m_music_playing.loadTTF("Music : ON / OFF");
    m_music_volume.loadTTF("Music : - / +");
    m_overlay_display.loadTTF("Overlay : ON / OFF");
    m_info_planete.loadTTF("Planete information : ON / OFF");
    m_mouse_button_pressed = false;

    screen_width = GetSystemMetrics(SM_CXSCREEN);
    screen_height = GetSystemMetrics(SM_CYSCREEN);
}

Settings::~Settings()
{

}

/***********************************************************************************************************************************************************************/
/********************************************************************* displayFrameSettings ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::displayFrameSettings(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, Shader *text_shader, Shader *square_shader)
{
    glm::mat4 save = modelview;
    float constance = 0.05;

    float start_x_black = -0.3;
    float start_y = 0.35;

    if(square_shader != nullptr)
    {
        //black fill
        for (size_t i(0); i < 15; i++)
        {
            for (size_t j(0); j < 13; j++)
            {
                    modelview = translate(modelview, vec3(start_x_black, start_y, 0.0));
                    m_black_rect.display(projection, modelview, hdr, square_shader);
                
                modelview = save;
                start_x_black = start_x_black + constance;
            }

            start_y = start_y - constance;
            start_x_black = -0.3;
        }

        //white border top and bottom
        float start_x_white = -0.3;

        for (size_t i(0); i < 13; i++)
        {
                modelview = translate(modelview, vec3(start_x_white, 0.36, 0.0));
                m_grey_rect.display(projection, modelview, hdr, square_shader);
                
            modelview = save;

                modelview = translate(modelview, vec3(start_x_white, -0.36, 0.0));
                m_grey_rect.display(projection, modelview, hdr, square_shader);

            modelview = save;

            start_x_white = start_x_white + constance;
        }

        //white border left and right
        float start_y_white = 0.36;

        for (size_t i(0); i < 15; i++)
        {
                modelview = translate(modelview, vec3(-0.31, start_y_white, 0.0));
                m_grey_rect.display(projection, modelview, hdr, square_shader);
                
            modelview = save;

                modelview = translate(modelview, vec3(0.31, start_y_white, 0.0));
                m_grey_rect.display(projection, modelview, hdr, square_shader);
                
            modelview = save;

            start_y_white = start_y_white - constance;
        }

        //the last to white on the bottom corner left and right

            modelview = translate(modelview, vec3(-0.31, -0.36, 0.0));
            m_grey_rect.display(projection, modelview, hdr, square_shader);
                
        modelview = save;

            modelview = translate(modelview, vec3(0.31, -0.36, 0.0));
            m_grey_rect.display(projection, modelview, hdr, square_shader);
    }
    
            
    modelview = save;


    //******************************************************************* render titre settings ***********************************************************************

        if(text_shader != nullptr)
        {
                modelview = translate(modelview, vec3(0.0, 0.34, -0.0));
                modelview = scale(modelview, vec3(0.075, 0.09, 0.0));
                m_titre.renderTextOverlay(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(0.0, -0.345, -0.0));
                modelview = scale(modelview, vec3(0.05, 0.060, 0.0));
                m_quit.renderTextOverlay(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(0.0, 0.25, -0.0));
                modelview = scale(modelview, vec3(0.05, 0.060, 0.0));
                m_hdr.renderTextOverlay(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(0.0, 0.18, -0.0));
                modelview = scale(modelview, vec3(0.05, 0.060, 0.0));
                m_exposure.renderTextOverlay(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(0.0, 0.11, -0.0));
                modelview = scale(modelview, vec3(0.05, 0.060, 0.0));
                m_speed.renderTextOverlay(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(0.0, 0.04, -0.0));
                modelview = scale(modelview, vec3(0.05, 0.060, 0.0));
                m_music_playing.renderTextOverlay(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(0.0, -0.03, -0.0));
                modelview = scale(modelview, vec3(0.05, 0.060, 0.0));
                m_music_volume.renderTextOverlay(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(0.0, -0.1, -0.0));
                modelview = scale(modelview, vec3(0.05, 0.060, 0.0));
                m_overlay_display.renderTextOverlay(projection, modelview, text_shader);

            modelview = save;

                modelview = translate(modelview, vec3(0.0, -0.17, -0.0));
                modelview = scale(modelview, vec3(0.07, 0.090, 0.0));
                m_info_planete.renderTextOverlay(projection, modelview, text_shader);

            modelview = save;
        }
        
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************* quitSimulation **********************************************************************************/
/***********************************************************************************************************************************************************************/
int Settings::manageButton(Input const &input)
{
    /*
        For portable aspect towards the screen resolution (may be the GPU resolution), i need the ratio between my resolution (1920x1080) and other under
        this threshold. It is not optimum but I don't have an other screen with a better resolution to work on it
    */
    float ratio_x = (float) 1920/screen_width; 
    float ratio_y = (float) 1080/screen_height;

    if((input.getMouseButton(SDL_MOUSEBUTTONDOWN)) && (!m_mouse_button_pressed))
    {
        m_mouse_button_pressed = true;
        // std::cout << "x = " << input.getX() << std::endl;
        // std::cout << "y = " << input.getY() << std::endl;

        // std::cout << "width : " << screen_width << std::endl;
        // std::cout << "height : " << screen_height << std::endl;

        //HDR : ON
        if( (input.getX() >= (screen_width/2) - (27/ratio_x)) && (input.getX() <= (screen_width/2) + (19/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) - (206/ratio_y)) && (input.getY() <= (screen_height/2) - (188/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::HDR_ON;
            }
        }

        //HDR : OFF
        if( (input.getX() >= (screen_width/2) + (33/ratio_x)) && (input.getX() <= (screen_width/2) + (116/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) - (206/ratio_y)) && (input.getY() <= (screen_height/2) - (188/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::HDR_OFF;
            }
        }

        //EXPOSURE : -
        if( (input.getX() >= (screen_width/2) + (55/ratio_x)) && (input.getX() <= (screen_width/2) + (76/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) - (148/ratio_y)) && (input.getY() <= (screen_height/2) - (135/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::EXPOSURE_DEC;
            }
        }

        //EXPOSURE : +
        if( (input.getX() >= (screen_width/2) + (97/ratio_x)) && (input.getX() <= (screen_width/2) + (120/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) - (148/ratio_y)) && (input.getY() <= (screen_height/2) - (135/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::EXPOSURE_INC;
            }
        }

        //SPEED : -
        if( (input.getX() >= (screen_width/2) + (28/ratio_x)) && (input.getX() <= (screen_width/2) + (55/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) - (93/ratio_y)) && (input.getY() <= (screen_height/2) - (80/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::SPEED_DEC;
            }
        }

        //SPEED : +
        if( (input.getX() >= (screen_width/2) + (96/ratio_x)) && (input.getX() <= (screen_width/2) + (117/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) - (93/ratio_y)) && (input.getY() <= (screen_height/2) - (80/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::SPEED_INC;
            }
        }

        //MUSIC ON
        if( (input.getX() >= (screen_width/2) - (9/ratio_x)) && (input.getX() <= (screen_width/2) + (20/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) - (42/ratio_y)) && (input.getY() <= (screen_height/2) - (25/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::MUSIC_ON;
            }
        }

        //MUSIC OFF
        if( (input.getX() >= (screen_width/2) + (60/ratio_x)) && (input.getX() <= (screen_width/2) + (115/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) - (42/ratio_y)) && (input.getY() <= (screen_height/2) - (25/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::MUSIC_OFF;
            }
        }

        //MUSIC VOLUME : -
        if( (input.getX() >= (screen_width/2) + (36/ratio_x)) && (input.getX() <= (screen_width/2) + (56/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) + (14/ratio_y)) && (input.getY() <= (screen_height/2) + (28/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::MUSIC_DEC;
            }
        }

        //MUSIC VOLUME : +
        if( (input.getX() >= (screen_width/2) + (94/ratio_x)) && (input.getX() <= (screen_width/2) + (117/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) + (14/ratio_y)) && (input.getY() <= (screen_height/2) + (28/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::MUSIC_INC;
            }
        }

        //OVERLAY : ON
        if( (input.getX() >= (screen_width/2) + (10/ratio_x)) && (input.getX() <= (screen_width/2) + (43/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) + (65/ratio_y)) && (input.getY() <= (screen_height/2) + (81/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::OVERLAY_ON;
            }
        }

        //OVERLAY : OFF
        if( (input.getX() >= (screen_width/2) + (68/ratio_x)) && (input.getX() <= (screen_width/2) + (115/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) + (65/ratio_y)) && (input.getY() <= (screen_height/2) + (81/ratio_y)))
            {
                //std::cout << "YES !" << std::endl;
                return ButtonChoice::Button::OVERLAY_OFF;
            }
        }

        //PLANETE INFO : ON
        if( (input.getX() >= (screen_width/2) + (73/ratio_x)) && (input.getX() <= (screen_width/2) + (103/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) + (115/ratio_y)) && (input.getY() <= (screen_height/2) + (141/ratio_y)))
            {
                // std::cout << "YES ON !" << std::endl;
                return ButtonChoice::Button::PLANETE_INFO_ON;
            }
        }

        //PLANETE INFO : OFF
        if( (input.getX() >= (screen_width/2) + (122/ratio_x)) && (input.getX() <= (screen_width/2) + (163/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) + (115/ratio_y)) && (input.getY() <= (screen_height/2) + (141/ratio_y)))
            {
                // std::cout << "YES OFF !" << std::endl;
                return ButtonChoice::Button::PLANETE_INFO_OFF;
            }
        }

        //QUIT SIMULATION
        if( (input.getX() >= (screen_width/2) - (115/ratio_x)) && (input.getX() <= (screen_width/2) + (115/ratio_x)) )
        {
            if((input.getY() >= (screen_height/2) + (258/ratio_y)) && (input.getY() <= (screen_height/2) + (272/ratio_y)))
            {
                return ButtonChoice::Button::QUIT;
            }
        }
    }

    if(input.getMouseButton(SDL_MOUSEBUTTONDOWN) == false)
    {
        m_mouse_button_pressed = false;
    }
    

    return ButtonChoice::Button::NONE;
}