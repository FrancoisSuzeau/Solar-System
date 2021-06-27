/*
AUTHOR : SUZEAU François

DATE : 15/06/2021

MODULE : CelestialBody.SimplePlanete

NAMEFILE : SimplePlanete.h

PURPOSE : header of the SimplePlanete class
*/

#ifndef SIMPPLANETE_H
#define SIMPPLANETE_H


/********************************************************************* includes *********************************************************************/

        #include "../Geometry/Sphere.h"
        #include "../../Texture/Texture.h"
        #include "../../Text/Text.h"
        

/********************************************************************* class definition *********************************************************************/

        class SimplePlanete: public Sphere
        {
            
            protected:

                Texture         m_texture_surface;
                std::string     m_name;
                Text            m_name_renderer;
                int             nb_moon;
        

 
                
            public:

                SimplePlanete(std::string const texture_surf, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos);
                SimplePlanete();
                ~SimplePlanete();
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos);
                void displayName(glm::mat4 &projection, glm::mat4 &modelview);
                void updatePosition(glm::mat4 &projection, glm::mat4 &modelview);
                void updatePositionLight(glm::mat4 &projection, glm::mat4 &light_src);
                
        };


#endif