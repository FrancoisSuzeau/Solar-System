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
        
       
/********************************************************************* class definition *********************************************************************/

        class SolarSystem : public System
        {
            
            private:

                int                             m_planetarySYS_count;
                int                             m_simple_planete_count;
                std::vector<SystemCreator*>     m_planetary_system;
                Star                            *sun;
                Skybox                          *skybox;

                std::vector<PlaneteCreator*> m_planete_creator;

                PlaneteInformation              *m_planete_info;

                std::vector<Shader*>            m_body_shader;
                Shader*                         m_ring_shader;
                Shader                          *m_sphere_shader;
                Shader                          *m_sun_atmo_shader;

                
            public:

                SolarSystem(std::string name_system, TTF_Font *police, int celestial_object_count = 0);
                SolarSystem();
                ~SolarSystem();


                void loadSystem(int count, TTF_Font *police) override;
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos = glm::vec3(0.0, 0.0, 0.0), Shader *host_shader = nullptr, Shader *companion_shader = nullptr, Shader *ring_shader = nullptr) override;
                void displaySkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr) override;
                void displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, Shader *name_render_shader = nullptr) override;
                void displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *atmo_shader = nullptr) override;
                void displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, PlaneteInformation *planete_info = nullptr, Shader *text_shader = nullptr, Shader *square_shader = nullptr) override;


        };


#endif