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
Settings::Settings(TTF_Font *police):
m_titre(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_quit(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_hdr(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_exposure(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_speed(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_music_playing(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_music_volume(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_overlay_display(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
m_info_planete(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police),
display_name_plan(3.0, 0.2, 6, "../assets/font/aAtmospheric.ttf", police)
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
    display_name_plan.loadTTF("Show body name : ON / OFF");
    m_mouse_button_pressed = false;

    screen_width = GetSystemMetrics(SM_CXSCREEN);
    screen_height = GetSystemMetrics(SM_CYSCREEN);

    colorGrey = vec3(0.7);
    colorBlack = vec3(0.1);

    m_grey_rect = new Square(0.05, 0.7);
    if(m_grey_rect == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    initButtonCoord();

}

Settings::~Settings()
{
    if(m_grey_rect != nullptr)
    {
        delete m_grey_rect;
    }
    
}


/***********************************************************************************************************************************************************************/
/********************************************************************* initButtonCoord *********************************************************************************/
/***********************************************************************************************************************************************************************/
void Settings::initButtonCoord()
{
    float ratio_x = (float) 1920/screen_width; 
    float ratio_y = (float) 1080/screen_height;

    float tab_coords[17][5] = {

        {(screen_width/2) - (27/ratio_x), (screen_width/2) + (19/ratio_x), (screen_height/2) - (206/ratio_y), (screen_height/2) - (188/ratio_y), (float) ButtonChoice::Button::HDR_ON},
        {(screen_width/2) + (33/ratio_x), (screen_width/2) + (116/ratio_x), (screen_height/2) - (206/ratio_y),  (screen_height/2) - (188/ratio_y), (float) ButtonChoice::Button::HDR_OFF},
        {(screen_width/2) + (55/ratio_x), (screen_width/2) + (76/ratio_x), (screen_height/2) - (148/ratio_y), (screen_height/2) - (135/ratio_y), (float) ButtonChoice::Button::EXPOSURE_DEC},
        {(screen_width/2) + (97/ratio_x), (screen_width/2) + (120/ratio_x), (screen_height/2) - (148/ratio_y), (screen_height/2) - (135/ratio_y), (float) ButtonChoice::Button::EXPOSURE_INC}, 
        {(screen_width/2) + (28/ratio_x), (screen_width/2) + (55/ratio_x), (screen_height/2) - (93/ratio_y), (screen_height/2) - (80/ratio_y), (float) ButtonChoice::Button::SPEED_DEC},
        {(screen_width/2) + (96/ratio_x), (screen_width/2) + (117/ratio_x), (screen_height/2) - (93/ratio_y), (screen_height/2) - (80/ratio_y), (float) ButtonChoice::Button::SPEED_INC},
        {(screen_width/2) - (9/ratio_x), (screen_width/2) + (20/ratio_x), (screen_height/2) - (42/ratio_y), (screen_height/2) - (25/ratio_y), (float) ButtonChoice::Button::MUSIC_ON},
        {(screen_width/2) + (60/ratio_x), (screen_width/2) + (115/ratio_x), (screen_height/2) - (42/ratio_y), (screen_height/2) - (25/ratio_y), (float) ButtonChoice::Button::MUSIC_OFF},
        {(screen_width/2) + (36/ratio_x), (screen_width/2) + (56/ratio_x), (screen_height/2) + (14/ratio_y), (screen_height/2) + (28/ratio_y), (float) ButtonChoice::Button::MUSIC_DEC},
        {(screen_width/2) + (94/ratio_x), (screen_width/2) + (117/ratio_x), (screen_height/2) + (14/ratio_y), (screen_height/2) + (28/ratio_y), (float) ButtonChoice::Button::MUSIC_INC},
        {(screen_width/2) + (10/ratio_x), (screen_width/2) + (43/ratio_x), (screen_height/2) + (65/ratio_y), (screen_height/2) + (81/ratio_y), (float) ButtonChoice::Button::OVERLAY_ON},
        {(screen_width/2) + (68/ratio_x), (screen_width/2) + (115/ratio_x), (screen_height/2) + (65/ratio_y), (screen_height/2) + (81/ratio_y), (float) ButtonChoice::Button::OVERLAY_OFF},
        {(screen_width/2) + (73/ratio_x), (screen_width/2) + (103/ratio_x), (screen_height/2) + (115/ratio_y), (screen_height/2) + (141/ratio_y), (float) ButtonChoice::Button::PLANETE_INFO_ON},
        {(screen_width/2) + (122/ratio_x), (screen_width/2) + (163/ratio_x), (screen_height/2) + (115/ratio_y), (screen_height/2) + (141/ratio_y), (float) ButtonChoice::Button::PLANETE_INFO_OFF},
        {(screen_width/2) + (59/ratio_x), (screen_width/2) + (94/ratio_x), (screen_height/2) + (168/ratio_y), (screen_height/2) + (194/ratio_y), (float) ButtonChoice::Button::SHOW_NAME_ON},
        {(screen_width/2) + (115/ratio_x), (screen_width/2) + (161/ratio_x), (screen_height/2) + (168/ratio_y), (screen_height/2) + (194/ratio_y), (float) ButtonChoice::Button::SHOW_NAME_OFF},
        {(screen_width/2) - (115/ratio_x), (screen_width/2) + (115/ratio_x), (screen_height/2) + (258/ratio_y), (screen_height/2) + (272/ratio_y), (float) ButtonChoice::Button::QUIT}

    };

    for (int i(0); i < 17; i++)
    {
        button_coord a;
        a.x_left = tab_coords[i][0];
        a.x_right = tab_coords[i][1];
        a.y_up = tab_coords[i][2];
        a.y_down = tab_coords[i][3];
        a.button_type = (int) tab_coords[i][4];

        m_buttons_coord.push_back(a);
    } 

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
    
    if((square_shader != nullptr) && (m_grey_rect != nullptr))
    {
        //black fill
        for (size_t i(0); i < 15; i++)
        {
            for (size_t j(0); j < 13; j++)
            {
                    modelview = translate(modelview, vec3(start_x_black, start_y, 0.0));
                    m_grey_rect->display(projection, modelview, colorBlack, hdr, square_shader);
                
                modelview = save;
                start_x_black = start_x_black + constance;
            }

            start_y = start_y - constance;
            start_x_black = -0.3;

            modelview = save;
        }
        modelview = save;

        //white border top and bottom
        float start_x_white = -0.3;

        for (size_t i(0); i < 13; i++)
        {
                modelview = translate(modelview, vec3(start_x_white, 0.36, 0.0));
                m_grey_rect->display(projection, modelview, colorGrey, hdr, square_shader);
                
            modelview = save;

                modelview = translate(modelview, vec3(start_x_white, -0.36, 0.0));
                m_grey_rect->display(projection, modelview, colorGrey, hdr, square_shader);

            modelview = save;

            start_x_white = start_x_white + constance;
        }

        //white border left and right
        float start_y_white = 0.36;

        for (size_t i(0); i < 15; i++)
        {
                modelview = translate(modelview, vec3(-0.31, start_y_white, 0.0));
                m_grey_rect->display(projection, modelview, colorGrey, hdr, square_shader);
                
            modelview = save;

                modelview = translate(modelview, vec3(0.31, start_y_white, 0.0));
                m_grey_rect->display(projection, modelview, colorGrey, hdr, square_shader);
                
            modelview = save;

            start_y_white = start_y_white - constance;
        }

        //the last to white on the bottom corner left and right

            modelview = translate(modelview, vec3(-0.31, -0.36, 0.0));
            m_grey_rect->display(projection, modelview, colorGrey, hdr, square_shader);
                
        modelview = save;

            modelview = translate(modelview, vec3(0.31, -0.36, 0.0));
            m_grey_rect->display(projection, modelview, colorGrey, hdr, square_shader);
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

                modelview = translate(modelview, vec3(0.0, -0.24, -0.0));
                modelview = scale(modelview, vec3(0.07, 0.090, 0.0));
                display_name_plan.renderTextOverlay(projection, modelview, text_shader);
            modelview = save;
        }
        
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************* manageButton ************************************************************************************/
/***********************************************************************************************************************************************************************/
int Settings::checkCoordButton(Input const &input, button_coord coordinate)
{
    if( (input.getX() >= coordinate.x_left) && (input.getX() <= coordinate.x_right) )
    {
        if((input.getY() >= coordinate.y_up) && (input.getY() <= coordinate.y_down))
        {
            return coordinate.button_type;   
        }
    }

    return ButtonChoice::Button::NONE;

}

/***********************************************************************************************************************************************************************/
/********************************************************************* manageButton ************************************************************************************/
/***********************************************************************************************************************************************************************/
int Settings::manageButton(Input const &input)
{
    if((input.getMouseButton(SDL_MOUSEBUTTONDOWN)) && (!m_mouse_button_pressed))
    {
        m_mouse_button_pressed = true;
        

        for (int i(0); i < 17; i++)
        {
            int a = checkCoordButton(input, m_buttons_coord[i]);
            if(a != ButtonChoice::Button::NONE)
            {
                return a;
            }
        }

    }

    if(input.getMouseButton(SDL_MOUSEBUTTONDOWN) == false)
    {
        m_mouse_button_pressed = false;
    }
    

    return ButtonChoice::Button::NONE;
}