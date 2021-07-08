/*
AUTHOR : SUZEAU François

DATE : 13/06/2021

MODULE : CelestialBody.Skybox

NAMEFILE : Skybox.h

PURPOSE : header of the Skybox class
*/

#ifndef SKYBOX_H
#define SKYBOX_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <GL/glew.h>
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_image.h>
        #include <iostream>
        #include <string>
        #include <cstring>
        #include <vector>

        #include "../../Shader/Shader.hpp"
        #include "../../FrameBuffer/FrameBuffer.hpp"


        

/********************************************************************* class definition *********************************************************************/

        class Skybox
        {
            
            private:

                
               std::vector<std::string>     m_faces;
               unsigned int                 m_texture_id;
               GLuint                       m_vboID;
               GLuint                       m_vaoID;

               Shader                       m_shader;
                
 
                
            public:

                
                Skybox();
                ~Skybox();

                unsigned int            loadSybox();
                void            display(glm::mat4 &projection, glm::mat4 &modelview);
                
        };


#endif