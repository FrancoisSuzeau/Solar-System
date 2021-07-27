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
                
                
                
            public:

                SolarSystem(std::string name_system, int celestial_object_count = 0);
                SolarSystem();
                ~SolarSystem();


                void loadSystem(int count) override;
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, glm::vec3 sun_pos = glm::vec3(0.0, 0.0, 0.0)) override;
                void displaySkybox(glm::mat4 &projection, glm::mat4 &modelview) override;
                void displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos) override;
                void displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos) override;


        };


#endif