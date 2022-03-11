/*
AUTHOR : SUZEAU François

DATE : 21/07/2021

MODULE : Overlay

NAMEFILE : Overlay.hpp

PURPOSE : header of the Overlay class
*/

#ifndef OVERLAY_H
#define OVERLAY_H


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
        #include <map>
        #include <cassert>

        #if defined(IMGUI_IMPL_OPENGL_ES2)
        #include <SDL_opengles2.h>
        #else
        #include <SDL2/SDL_opengl.h>
        #endif

        #include "../../../lib/imgui/imgui.h"
        #include "../../../lib/imgui/imgui_impl_sdl.h"
        #include "../../../lib/imgui/imgui_impl_opengl3.h"

        #include "../../Objects/BasicObjects/Square.hpp"
        #include "../../Renderers/BasicRenderers/SquareRenderer.hpp"
        #include "../DataManager.hpp"

        typedef struct music_data {
                std::string title;
                std::string author;
                std::string studio;

        } music_data;

        typedef struct nav_datas {

                ImVec4 color_text;
                float min_grav_inf;

        } nav_datas;
        

/********************************************************************* class definition *********************************************************************/

        class Overlay
        {
            
            private:

                Square          *m_square_ptr;
                Renderer        *m_square_renderer;

                // float           m_ancient_radius;
                // float           m_ancient_speed;

                // std::map<int, music_data> map_music_data;
                // std::map<std::string, nav_datas> map_nav_data;

                void displaySquares(DataManager &data_manager, std::vector<glm::vec3> coordinates);
                void renderHorizontal(DataManager &data_manager, float side);
                void renderVertical(DataManager &data_manager, float side);

            public:
            
                Overlay();
                ~Overlay();

                void            initOverlayAssets(Renderer *square_rend, Square *square);

                void            renderEdges(DataManager &data_manager);
                // void displayMusicInfo(RenderData &render_data);
                // void displayNavigation(RenderData &render_data);
                // void displayAppInfo(RenderData &render_data);

        };


#endif