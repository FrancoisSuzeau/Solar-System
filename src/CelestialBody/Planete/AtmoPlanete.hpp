/*
AUTHOR : SUZEAU François

DATE : 07/06/2021

MODULE : CelestialBody.AtmoPlanete

NAMEFILE : AtmoPlanete.h

PURPOSE : header of the AtmoPlanete class
*/

#ifndef ATMOPLANETE_H
#define ATMOPLANETE_H


/********************************************************************* includes *********************************************************************/

        #include "SimplePlanete.hpp"
        
        #include <string>
        #include <vector>
        #include <iostream>
        #include <cassert>

        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        
        
       
/********************************************************************* class definition *********************************************************************/

        class AtmoPlanete: public SimplePlanete
        {
            
            private:

                
                Texture         *m_cloud_texture;
                float           m_oppacity;
                
                
                
            public:

                AtmoPlanete(init_data data, TTF_Font *police);
                AtmoPlanete();
                ~AtmoPlanete();
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *atmo_plan_shader = nullptr, Shader *ring_shader = nullptr);

        };


#endif