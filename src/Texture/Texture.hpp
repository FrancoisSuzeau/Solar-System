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

        #include <GL/glew.h>

/********************************************************************* class definition *********************************************************************/

        class Texture
        {
            
            private:

                GLuint          m_id;
                std::string     m_file_picture;

                
            public:

                Texture();
                Texture& operator=(Texture const &texture_to_copy);
                Texture(std::string file_image);
                ~Texture();

                bool loadTexture();
                GLuint getID() const;
                void setFilePicture(const std::string &file_image);
                SDL_Surface *pixelsInverter(SDL_Surface *src_img) const;
                std::string getFileName() const;
                
        };


#endif