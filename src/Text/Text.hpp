/*
AUTHOR : SUZEAU François

DATE : 10/06/2021

MODULE : Text

NAMEFILE : Text.h

PURPOSE : header of the Text class
*/

#ifndef TEXT_H
#define TEXT_H


/********************************************************************* includes *********************************************************************/
        
        #include <SDL2/SDL_ttf.h>
        #include <SDL2/SDL.h>
        #include <iostream>
        #include <string>

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <GL/glew.h>

        #include "../Texture/Texture.hpp"
        #include "../OpenGlSketch/RenderData.hpp"

/********************************************************************* class definition *********************************************************************/

        class Text
        {
            
            private:
                
                std::string     m_file_path;
                TTF_Font        *m_police;
                SDL_Color       m_colorText;
                float           m_vertices[18];
                float           m_texture_coord[12];
                GLuint          m_id;

                glm::mat4 m_model_mat;
                
                SDL_Surface *reversePixels(SDL_Surface *src) const;
                void rotateText(float const z, double ratio, float phi, float theta, float y);
                
            public:

                Text(float x, float y, float z, std::string file_path);
                Text(float x, float y, float z, std::string file_path, TTF_Font *police);
                Text();
                Text& operator=(Text const &text_to_copy);
                ~Text();

                bool loadTTF(std::string const text);
                
                void            updatePosition(glm::vec3 position);
                void            updateScale(glm::vec3 scale_data);
                void            renderMovingText(RenderData &render_data, float const z, double ratio, float phi, float theta, float y);
                void            renderText(RenderData &render_data);
                bool            setText(std::string const text);
                
        };


#endif