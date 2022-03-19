/*
AUTHOR : SUZEAU François

DATE : 15/06/2021

MODULE : Renderer::TexturedRenderer::PlaneteRenderer

NAMEFILE : PlaneteRenderer.hpp

PURPOSE : header of the PlaneteRenderer class
*/

#ifndef PLANETE_RENDERER_H
#define PLANETE_RENDERER_H


/********************************************************************* includes *********************************************************************/

        // #include "../Geometry/Sphere.hpp"
        // #include "../../PlaneteInformation/PlaneteInformation.hpp"
        // #include "Planete.hpp"

        #include "../../BasicRenderers/SphereRenderer.hpp"
        #include "../../../Objects/TexturedObjects/Planete/Planete.hpp"
        

        #include <string>
        #include <vector>
        #include <iostream>
        #include <cassert>

        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        
/********************************************************************* class definition *********************************************************************/

        class PlaneteRenderer : public SphereRenderer
        {
                private:
                        typedef SphereRenderer super;
            
            protected:

                // std::string     m_name;
                
            public:

                PlaneteRenderer(const float radius, const unsigned int longSegs, const unsigned int latSegs);
                ~PlaneteRenderer();

                void render(DataManager &data_manager, Object *planete) override;
                void clean() override;

                // void display(RenderData &render_data, Planete *planete);
                // void displayName(RenderData &render_data, int threshold, Planete *planete);
                // void displayAtmo(RenderData &render_data, Planete *planete);
                // void renderRing(RenderData &render_data, Planete *planete);
                
        };


#endif