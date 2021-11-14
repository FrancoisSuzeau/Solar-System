/*
AUTHOR : SUZEAU François

DATE : 27/05/2021

MODULE : Texture

NAMEFILE : Texture.h

PURPOSE : header of the Texture class
*/

#ifndef TEXTURE_H
#define TEXTURE_H


/********************************************************************* includes *********************************************************************/
        
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_image.h>
        #include <iostream>
        #include <string>
        #include <cassert>
        #include <GL/glew.h>

/********************************************************************* class definition *********************************************************************/

        class Texture
        {
            
            private:

                GLuint          m_id;
                std::string     m_file_picture;

                int             m_width;
                int             m_height;
                GLenum          m_format;
                GLenum          m_internal_format;
                bool            m_empty_texture;

                SDL_Surface *pixelsInverter(SDL_Surface *src_img) const;

                
            public:

                Texture();
                Texture& operator=(Texture const &texture_to_copy);
                Texture(std::string file_image);
                Texture(int width, int height, GLenum format, GLenum internal_format, bool empty_texture);
                ~Texture();

                bool loadTexture();
                void loadEmptyTexture();
                GLuint getID() const;
                void setFilePicture(const std::string &file_image);
                std::string getFileName() const;
                
        };


#endif