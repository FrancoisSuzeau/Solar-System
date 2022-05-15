/*
AUTHOR : SUZEAU François

DATE : 06/02/2022

MODULE : Objects::TexturedObjects::Star::FlareManager

NAMEFILE : FlareManager.hpp

PURPOSE : 
*/

#ifndef FLAREMANAGER_H
#define FLAREMANAGER_H


/********************************************************************* includes *********************************************************************/

        #include <iostream>
        #include "../../../../Application/DataManager.hpp"
        #include "../../../../Renderers/TexturedRenderers/SquareTexturedRenderer/SquareTexturedRenderer.hpp"
        #include "../../SquareTextured/LensFlare/FlareTexture.hpp"
        

        typedef struct flare_datas {

                FlareTexture    *flare;
                float           depth_size;
                float           strength;

        } flare_datas;

/********************************************************************* class definition *********************************************************************/
        
        class FlareManager
        {
            private:

                SquareTexturedRenderer  *m_square_textured_renderer = nullptr;
                
                std::vector<flare_datas> m_flares;

                float spacing;
                std::string m_flares_type; 

            public:

                
                FlareManager(SquareTexturedRenderer  *square_textured_renderer, std::string const type);
                ~FlareManager();

                void clean();
                void makeChanges(DataManager &data_manager);

                void renderLensFlare(DataManager &data_manager);
            
        };


#endif