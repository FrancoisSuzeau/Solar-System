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

        #include "System.h"
        #include "SystemCreator.h"
        #include "PlanetarySystemCreator.h"
        #include "../Planete/AtmoPlanete.h"
        #include "../Planete/SimplePlanete.h"
        #include "../Planete/PlaneteRing.h"
        #include "../Star/Star.h"


       
/********************************************************************* class definition *********************************************************************/

        class SolarSystem : public System
        {
            
            private:

                int                             m_planetarySYS_count;
                int                             m_simple_planete_count;
                std::vector<SystemCreator*>     m_planetary_system;
                std::vector<SimplePlanete*>     m_simple_planete;
                Star                            sun;
                
                
                
            public:

                SolarSystem(std::string name_system, int celestial_object_count = 0);
                SolarSystem();
                ~SolarSystem();


                void loadSystem() override;
                void display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos) override;

        };


#endif