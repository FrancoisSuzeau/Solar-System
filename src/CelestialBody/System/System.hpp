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
        #include "../../OpenGlSketch/RenderData.hpp"

        typedef struct init_data {

                std::string texture_path;
                std::string normal_path;
                std::string disp_path;
                std::string name;
                float   size;
                float   inclinaison_angle;
                glm::vec3 position;

        } init_data;

        typedef struct sys_init_data {

                std::string     name_sys;
                int     companion_count;

        } sys_init_data;
       
/********************************************************************* class definition *********************************************************************/

        class System
        {
            
            protected:

                std::string                 m_system_name;
                int                         m_companion_count;

                std::vector<init_data>          m_data;
                std::vector<sys_init_data>     sys_data;

                virtual void initData() = 0;
                
            public:

                
                virtual ~System() {};
                virtual void loadSystem(int count, TTF_Font *police) = 0;
                virtual void display(RenderData &render_data) = 0;
                virtual void displaySkybox(RenderData &render_data) = 0;
                virtual void displayName(RenderData &render_data) = 0;
                virtual void displayAtmo(RenderData &render_data) = 0;
                virtual void displayInfo(RenderData &render_data, PlaneteInformation *planete_info = nullptr) = 0;
                virtual void displayAsteroidField(RenderData &redner_data) = 0;
                
        };


#endif