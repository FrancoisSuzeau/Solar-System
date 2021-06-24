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

        #include "System.h"

        #include "../Planete/AtmoPlanete.h"
        #include "../Planete/SimplePlanete.h"
        #include "../Planete/PlaneteRing.h"
       
/********************************************************************* class definition *********************************************************************/

        class PlanetarySystem : public System
        {
            
            private:

                std::vector<SimplePlanete*>      m_moons;
                SimplePlanete                   *m_host;
                
                
                
            public:

                PlanetarySystem(std::string name_system, int companion_count);
                PlanetarySystem();
                ~PlanetarySystem();


                void loadSystem() override;
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos) override;
                void displaySkybox(glm::mat4 &projection, glm::mat4 &modelview) override;

        };


#endif