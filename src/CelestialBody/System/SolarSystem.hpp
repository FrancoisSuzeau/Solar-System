/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : SolarSystem.h

PURPOSE : header of the virtual SolarSystem class
*/

#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H


/********************************************************************* includes *********************************************************************/

        #include "System.hpp"
        #include "SystemCreator.hpp"
        #include "PlanetarySystemCreator.hpp"
        
        #include "../Star/Star.hpp"
        #include "../Skybox/Skybox.hpp"

        #include "../Planete/PlaneteCreator.hpp"
        #include "../Planete/AtmoPlaneteCreator.hpp"
        #include "../Planete/SimplePlaneteCreator.hpp"
        #include "../Planete/PlaneteRingCreator.hpp"
        #include "../../Shader/Shader.hpp"

        #include "../../PlaneteInformation/PlaneteInformation.hpp"
        #include "../AsteroidField/AsteroidField.hpp"

        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>
        #include <cassert>
        
        
       
/********************************************************************* class definition *********************************************************************/

        class SolarSystem : public System
        {
            
            private:

                int                             m_planetarySYS_count;
                int                             m_simple_planete_count;
                std::vector<SystemCreator*>     m_planetary_system;
                Star                            *sun;
                Skybox                          *skybox;
                AsteroidField                   *m_asteroid_field;

                std::vector<PlaneteCreator*>    m_planete_creator;

                PlaneteInformation              *m_planete_info;

                std::vector<Shader*>            shaders;
                Shader                          *m_model_shader;
                

                void initData() override;
                
            public:

                SolarSystem(sys_init_data data, TTF_Font *police, Shader *model_shader = nullptr);
                SolarSystem();
                ~SolarSystem();


                void loadSystem(int count, TTF_Font *police) override;
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *host_shader = nullptr, Shader *companion_shader = nullptr, Shader *ring_shader = nullptr) override;
                void displaySkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr) override;
                void displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, Shader *name_render_shader = nullptr) override;
                void displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *atmo_shader = nullptr) override;
                void displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, std::vector<Shader *> shaders, PlaneteInformation *planete_info = nullptr) override;
                void displayAsteroidField(std::vector<glm::mat4> projection_view_mat, bool hdr) override;


        };

        


#endif