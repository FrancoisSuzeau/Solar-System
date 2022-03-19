/*
AUTHOR : SUZEAU François

DATE : 18/03/2022

MODULE : Renderers::TexturedRenderers::StarRenderer

NAMEFILE : StarRenderer.hpp

PURPOSE : header of the StarRenderer class
*/

#ifndef STAR_RENDERER_H
#define STAR_RENDERER_H


/********************************************************************* includes *********************************************************************/

        #include "../../BasicRenderers/SphereRenderer.hpp"
        #include "../../../Objects/TexturedObjects/Star/Star.hpp"

        

/********************************************************************* class definition *********************************************************************/

        class StarRenderer : public SphereRenderer
        {
            private:

                typedef SphereRenderer super;
            
            protected:
 
                
            public:

                StarRenderer(const float radius, const unsigned int longSegs, const unsigned int latSegs);
                ~StarRenderer();

                void render(DataManager &data_manager, Object *star) override;
                void clean() override;
        };


#endif