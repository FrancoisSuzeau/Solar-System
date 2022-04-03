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
        #include "../../Objects/BasicObjects/Sphere.hpp"

        

/********************************************************************* class definition *********************************************************************/

        class SphereRenderer : public Renderer
        {
                private:

                        typedef Renderer super;
            
                protected:

                        GLuint                          m_ibo;
                        GLsizei                         m_element_count;
                        unsigned int                    m_vertCount;
                        GLushort                        *m_tris;
                        float                           m_radius;
                        GLfloat                         ***tmp;
                        unsigned int                    longVerts;
                        unsigned int                    latVerts;

                        int                             m_bytes_vertices_size;
                        int                             m_bytes_normals_size;
                        int                             m_bytes_texture_size;

                        void                            load() override;
        
                        
                public:

                        SphereRenderer(const float radius, const unsigned int longSegs, const unsigned int latSegs);
                        ~SphereRenderer();

                
                        void render(DataManager &data_manager, Object *sphere) override;
                        void clean() override;
        };


#endif