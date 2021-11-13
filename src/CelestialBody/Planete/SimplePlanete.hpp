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
        #include "../../PlaneteInformation/PlaneteInformation.hpp"
        #include "../../Shader/Shader.hpp"

        #include <string>
        #include <vector>
        #include <iostream>
        #include <cassert>

        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>
        

/********************************************************************* class definition *********************************************************************/

        class SimplePlanete: public Sphere
        {
            
            protected:

                Texture         *m_texture_surface;
                std::string     m_name;
                Text            *m_name_renderer;
                int             nb_moon;
                Atmosphere      *m_atmosphere;
                
            public:

                SimplePlanete(std::string const texture_surf, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos, TTF_Font *police);
                SimplePlanete();
                ~SimplePlanete();
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *simple_plan_shader = nullptr, Shader *ring_shader = nullptr);
                void displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 camPos, int threshold, Shader *name_render_shader = nullptr);
                void updatePosition(glm::mat4 &projection, glm::mat4 &modelview);
                void updatePositionLight(glm::mat4 &projection, glm::mat4 &light_src);
                void displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *atmo_shader = nullptr);
                
                std::string getName() const;
                float getRadiusFromCam(glm::vec3 camPos);
                float getPhiFromCam(glm::vec3 camPos);
                float getThetaFromCam(glm::vec3 camPos, float r);
                
        };


#endif