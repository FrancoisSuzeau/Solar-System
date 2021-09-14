/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : PlanetarySystem.h

PURPOSE : header of the virtual PlanetarySystem class
*/

#ifndef PLSYSTEM_H
#define PLSYSTEM_H


/********************************************************************* includes *********************************************************************/

        #include "System.hpp"

        #include "../Planete/PlaneteCreator.hpp"
        #include "../Planete/AtmoPlaneteCreator.hpp"
        #include "../Planete/SimplePlaneteCreator.hpp"
        #include "../Planete/PlaneteRingCreator.hpp"

        #include "../../Atmosphere/Atmosphere.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class PlanetarySystem : public System
        {
            
            private:

                std::vector<PlaneteCreator*>            m_moons_creator;
                PlaneteCreator                          *m_host_creator;

                Text            m_name_renderer;
                Atmosphere      *m_atmosphere;

                
                
                
            public:

                PlanetarySystem(std::string name_system, int companion_count);
                PlanetarySystem();
                ~PlanetarySystem();


                void loadSystem(int count) override;
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos = glm::vec3(0.0, 0.0, 0.0)) override;
                void displaySkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr) override;
                void displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos) override;
                void displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr) override;
                void displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, PlaneteInformation *planete_info = nullptr) override;


        };


#endif