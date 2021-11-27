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
        #include "../System/System.hpp"

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
                Texture         *m_normal_surface;
                std::string     m_name;
                Text            *m_name_renderer;
                int             nb_moon;
                Atmosphere      *m_atmosphere;
                
            public:

                SimplePlanete(init_data data, TTF_Font *police);
                SimplePlanete();
                ~SimplePlanete();
                void display(RenderData &render_data, glm::vec3 &camPos);
                void displayName(RenderData &render_data, glm::vec3 camPos, int threshold);
                void displayAtmo(RenderData &render_data, glm::vec3 &camPos);
                
                std::string getName() const;
                float getRadiusFromCam(glm::vec3 camPos);
                float getPhiFromCam(glm::vec3 camPos);
                float getThetaFromCam(glm::vec3 camPos, float r);
                
        };


#endif