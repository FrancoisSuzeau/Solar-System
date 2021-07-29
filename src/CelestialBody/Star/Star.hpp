/*
AUTHOR : SUZEAU François

DATE : 16/06/2021

MODULE : CelestialBody.Star

NAMEFILE : Star.h

PURPOSE : header of the Star class
*/

#ifndef STAR_H
#define STAR_H


/********************************************************************* includes *********************************************************************/

        #include "../Geometry/Sphere.hpp"
        #include "../../Texture/Texture.hpp"
        #include "../../Text/Text.hpp"

        #include "../../Atmosphere/StarAtmosphere.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Star: public Sphere
        {
            
            private:

                Texture         m_cloud_texture;
                std::string     m_name;
                Text            m_name_renderer;
                GLuint          m_light_vao;

                StarAtmosphere      *m_atmosphere;
        

 
                
            public:

                Star(const float radius, const unsigned int longSegs, const unsigned int latSegs, std::string const texture_surf, std::string const name, float const real_size);
                Star();
                ~Star();
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr);
                //void displayName(glm::mat4 &projection, glm::mat4 &modelview);
                void updatePosition(glm::mat4 &projection, glm::mat4 &modelview, float const rotation);
                void updatePositionLight(glm::mat4 &projection, glm::mat4 &light_src);
                void displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, float phi, float theta, glm::vec3 &camPosUpd, bool hdr);
                
                
        };


#endif