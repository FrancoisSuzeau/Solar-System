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
        
        
       
/********************************************************************* class definition *********************************************************************/

        class AtmoPlanete: public SimplePlanete
        {
            
            private:

                
                Texture         m_cloud_texture;
                float           m_oppacity;
                
                
                
            public:

                AtmoPlanete(std::string const texture_surf, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos);
                AtmoPlanete();
                ~AtmoPlanete();
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos);
                //void displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, float phi, float theta, float y, glm::mat4 &light_src, glm::vec3 &camPos);

        };


#endif