/*
AUTHOR : SUZEAU François

DATE : 02/08/2021

MODULE : Settings

NAMEFILE : Settings.hpp

PURPOSE : header of the Settings class
*/

#ifndef SETTINGS_H
#define SETTINGS_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <glm/gtc/matrix_inverse.hpp>
        #include <glm/gtx/string_cast.hpp>

        #include <GL/glew.h>
        #include <iostream>
        #include <iomanip>
        #include <sstream>
        #include <string>
        #include <cstring>
        #include <vector>
        #include <cmath>
        #include <ctime>
        #include <Windows.h>
        #include <cassert>

        #if defined(IMGUI_IMPL_OPENGL_ES2)
        #include <SDL_opengles2.h>
        #else
        #include <SDL2/SDL_opengl.h>
        #endif

        #include "../OpenGlSketch/RenderData.hpp"

        #include "../../lib/imgui/imgui.h"
        #include "../../lib/imgui/imgui_impl_sdl.h"
        #include "../../lib/imgui/imgui_impl_opengl3.h"

        #include "../Saving/Saving.hpp"

        typedef struct imguiTexture_datas {

                int img_width;
                int img_height;
                GLuint text_id;
                std::string filepath;
                std::string name_disp;

        } imguiTexture_datas;

        

/********************************************************************* class definition *********************************************************************/

        class Settings
        {
            
            private:

                void managePerformance(RenderData &render_data);
                void manageHUD(RenderData &render_data);
                void manageNavigation(RenderData &render_data);
                void verifIndex();

                bool loadTextureFromFile(imguiTexture_datas &data);

                std::vector<imguiTexture_datas> textures_data;
                std::vector<float> min_distance;
                int index;

            public:
            
                Settings();
                ~Settings();

                void manageSettings(RenderData &render_data);
        };


#endif