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

/********************************************************************* class definition *********************************************************************/
        
        class FlareManager
        {
            private:
                
                FlareTexture fl;

                void calculateFlarePos();

            public:

                
                FlareManager();
                ~FlareManager();

                void renderLensFlare(RenderData &render_data);
            
        };


#endif