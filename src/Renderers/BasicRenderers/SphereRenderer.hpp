/*
AUTHOR : SUZEAU François

DATE : 06/06/2021

MODULE : Renderers::BasicRenderers

NAMEFILE : SphereRenderer.hpp

PURPOSE : header of the SphereRenderer class
*/

#ifndef SPHERE_RENDERER_H
#define SPHERE_RENDERER_H


/********************************************************************* includes *********************************************************************/

        #include "../Renderer.hpp"
        #include "../../Objects/BasicObjects/Square.hpp"

        

/********************************************************************* class definition *********************************************************************/

        class SphereRenderer : public Renderer
        {
            
            protected:

                GLuint                          m_vbo;
                GLuint                          m_ibo;
                GLsizei                         m_element_count;
                unsigned int                    m_vertCount;
                GLushort                        *m_tris;
                float                           m_radius;
                GLfloat                         ***tmp;
                unsigned int                    longVerts;
                unsigned int                    latVerts;
 
                
            public:

                SphereRenderer(const float radius, const unsigned int longSegs, const unsigned int latSegs);
                ~SphereRenderer();

                void load() override;
                void render(DataManager &data_manager, Object *sphere) override;
                void clean() override;
        };


#endif