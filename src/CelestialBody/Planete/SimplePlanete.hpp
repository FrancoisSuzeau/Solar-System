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

        #include "../Geometry/Sphere.hpp"
        #include "../../Texture/Texture.hpp"
        #include "../../Text/Text.hpp"
        #include "../../Atmosphere/Atmosphere.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class SimplePlanete: public Sphere
        {
            
            protected:

                Texture         m_texture_surface;
                std::string     m_name;
                Text            m_name_renderer;
                int             nb_moon;
                Atmosphere      *m_atmosphere;

 
                
            public:

                SimplePlanete(std::string const texture_surf, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos);
                SimplePlanete();
                ~SimplePlanete();
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr);
                void displayName(glm::mat4 &projection, glm::mat4 &modelview, double ratio, float phi, float theta, float y);
                void updatePosition(glm::mat4 &projection, glm::mat4 &modelview);
                void updatePositionLight(glm::mat4 &projection, glm::mat4 &light_src);
                void updateAtmoInter(glm::mat4 &projection, glm::mat4 &light_src);
                void displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, float phi, float theta, glm::vec3 &body_pos, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr);
                std::string getName() const;
                
        };


#endif