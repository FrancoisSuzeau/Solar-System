/*
AUTHOR : SUZEAU François

DATE : 29/06/2021

MODULE : Objects::BasicObjects

NAMEFILE : Square.hpp

PURPOSE : header of the Square class
*/

#ifndef SQUARE_H
#define SQUARE_H


/********************************************************************* includes *********************************************************************/

        #include "../Object.hpp"

/********************************************************************* class definition *********************************************************************/

        class Square : public Object
        {
            
            private:
                
                float   m_vertices[18];
                float   m_colors[18];

                GLuint  m_vboID;
                int     m_bytes_vertices_size;
                int     m_bytes_colors_size;

                GLuint  m_vaoID;
                
            public:

                Square(float size, float const color);
                ~Square();

                void load() override;
                void render(DataManager &data_manager) override;
                void transform() override;


                // void drawLoad(int count, RenderData &render_data, glm::vec3 color);
                
        };


#endif