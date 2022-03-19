/*
AUTHOR : SUZEAU François

DATE : 06/03/2022

MODULE : Renderer::BasicRenderers

NAMEFILE : SquareRenderer.hpp

PURPOSE : header of the SquareRenderer class
*/

#ifndef SQUARE_RENDERER_H
#define SQUARE_RENDERER_H


/********************************************************************* includes *********************************************************************/

        #include "../Renderer.hpp"
        #include "../../Objects/BasicObjects/Square.hpp"

/********************************************************************* class definition *********************************************************************/

        class SquareRenderer : public Renderer
        {
            
            private:
                
                float   m_vertices[18];
                float   m_colors[18];

                // GLuint  m_vboID;
                int     m_bytes_vertices_size;
                int     m_bytes_colors_size;

                void    load() override;
                
            public:

                SquareRenderer(float const color);
                ~SquareRenderer();

                
                void render(DataManager &data_manager, Object *square) override;
                void clean() override;
        };


#endif