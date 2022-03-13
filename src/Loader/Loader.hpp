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
        #include <iostream>
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
                
        };


#endif