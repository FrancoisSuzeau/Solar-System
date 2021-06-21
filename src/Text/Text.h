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
        #include <iostream>
        #include <string>

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <GL/glew.h>

        #include "../Texture/Texture.h"
        #include "../Shader/Shader.h"

/********************************************************************* class definition *********************************************************************/

        class Text
        {
            
            private:
                
                std::string     m_file_path;
                TTF_Font        *m_police;
                SDL_Color       m_colorText;
                Shader          m_shader;
                float           m_vertices[18];
                float           m_texture_coord[12];
                GLuint          m_id;
                

                
            public:

                Text(float x, float y, float z, std::string file_path, std::string const vertex_shader, std::string const fragment_shader);
                Text();
                ~Text();

                bool loadTTF(std::string const text);
                SDL_Surface *reversePixels(SDL_Surface *src) const;
                void            renderText(glm::mat4 &projection, glm::mat4 &modelview, float const z);
                
        };


#endif