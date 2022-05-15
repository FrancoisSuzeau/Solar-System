/*
AUTHOR : SUZEAU François

DATE : 14/05/2022

MODULE : Renderer::TexturedRenderer::SquareTexturedRenderer

NAMEFILE : SquareTexturedRenderer.hpp

PURPOSE : header of the SquareTexturedRenderer class

*/

#ifndef SQUARE_TEXTURED_REN_H
#define SQUARE_TEXTURED_REN_H


/********************************************************************* includes *********************************************************************/

        #include "../../BasicRenderers/SquareRenderer.hpp"
        #include "../../../Objects/TexturedObjects/SquareTextured/LensFlare/FlareTexture.hpp"
        

        #include <string>
        #include <vector>
        #include <iostream>
        #include <cassert>

        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        
/********************************************************************* class definition *********************************************************************/

        class SquareTexturedRenderer : public SquareRenderer
        {
                private:
                        typedef SquareRenderer super;
                
                public:

                    SquareTexturedRenderer();
                    ~SquareTexturedRenderer();

                    void render(DataManager &data_manager, Object *FlareTexture) override;
                    void clean() override;

                    // void display(RenderData &render_data, Planete *planete);
                    // void displayName(RenderData &render_data, int threshold, Planete *planete);
                    // void displayAtmo(RenderData &render_data, Planete *planete);
                    // void renderRing(RenderData &render_data, Planete *planete);
                
        };


#endif