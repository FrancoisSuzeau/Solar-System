/*
AUTHOR : SUZEAU François

DATE : 06/02/2022

MODULE : FlareManager

NAMEFILE : FlareManager.hpp

PURPOSE : Interface FlareManager
*/

#ifndef FLAREMANAGER_H
#define FLAREMANAGER_H


/********************************************************************* includes *********************************************************************/

        #include <iostream>

        #include "../OpenGlSketch/RenderData.hpp"
        #include "FlareTexture.hpp"
        #include <vector>
        #include <algorithm>

        typedef struct flare_datas {

                FlareTexture    *flare;
                glm::vec3       size;
                float           depth_size;
                float           strength;

        } flare_datas;

/********************************************************************* class definition *********************************************************************/
        
        class FlareManager
        {
            private:
                
                std::vector<flare_datas> flares;

                float spacing; 

                void calculateFlarePos(glm::vec2 sunToCenter, glm::vec2 sunCoords, flare_datas fd, int i);

                glm::vec2 convertToScreenSpace(glm::vec3 sunPos, glm::mat4 viewMat, glm::mat4 projMat);

            public:

                
                FlareManager();
                ~FlareManager();

                void renderLensFlare(RenderData &render_data);
            
        };


#endif