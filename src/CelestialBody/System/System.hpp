/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : System.h

PURPOSE : header of the virtual System class
*/

#ifndef SYSTEM_H
#define SYSTEM_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <cstdlib>
        
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>
        #include "../../Shader/Shader.hpp"

        #include "../../PlaneteInformation/PlaneteInformation.hpp"

        typedef struct init_data {

                std::string texture_path;
                std::string name;
                float   size;
                float   inclinaison_angle;
                glm::vec3 position;

        } init_data;
       
/********************************************************************* class definition *********************************************************************/

        class System
        {
            
            protected:

                std::string                 m_system_name;
                int                         m_companion_count;

                std::vector<init_data>          m_data;

                virtual void initData() = 0;
                
            public:

                
                virtual ~System() {};
                virtual void loadSystem(int count, TTF_Font *police) = 0;
                virtual void display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos = glm::vec3(0.0, 0.0, 0.0), Shader *host_shader = nullptr, Shader *companion_shader = nullptr, Shader *ring_shader = nullptr) = 0;
                virtual void displaySkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr) = 0;
                virtual void displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, Shader *name_render_shader = nullptr) = 0;
                virtual void displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *atmo_shader = nullptr) = 0;
                virtual void displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, std::vector<Shader *> shaders, PlaneteInformation *planete_info = nullptr) = 0;
                virtual void displayAsteroidField(std::vector<glm::mat4> projection_view_mat, bool hdr) = 0;
                
        };


#endif