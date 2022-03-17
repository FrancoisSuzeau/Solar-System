/*
AUTHOR : SUZEAU François

DATE : 13/03/2022

MODULE : Loader

NAMEFILE : Loader.hpp

PURPOSE : header of the Loader class
*/

#ifndef LOADER_H
#define LOADER_H


/********************************************************************* includes *********************************************************************/

        #include <GL/glew.h>
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_image.h>
        #include <SDL2/SDL_mixer.h>

        #include <iostream>
        #include <vector>
        #include <cassert>
        
        #include "../ErrorHandler/ErrorHandler.hpp"
        

/********************************************************************* class definition *********************************************************************/


        class Loader
        {
            
            private:

                //This class cannot be instanced
                Loader();
                ~Loader();

            public:

                static bool loadWithStbi(std::string file_path, GLuint &id, int &w, int &h);
                static unsigned int loadWithStbi(const char *path, const std::string &directory);
                static  Mix_Music* loadWithSDLMixer(std::string file_path, Mix_Music *m_music);
                static unsigned int loadSkyboxTextures(std::vector<std::string> faces);
                
        };


#endif