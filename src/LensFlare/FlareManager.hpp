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

/********************************************************************* class definition *********************************************************************/
        
        class FlareManager
        {
            private:
                
                std::vector<FlareTexture*> flare_textures;

                float spacing; 

                void calculateFlarePos(glm::vec2 sunToCenter, glm::vec2 sunCoords, FlareTexture *flare_text, int i);

                glm::vec2 convertToScreenSpace(glm::vec3 sunPos, glm::mat4 viewMat, glm::mat4 projMat);

            public:

                
                FlareManager();
                ~FlareManager();

                void renderLensFlare(RenderData &render_data);
            
        };


#endif