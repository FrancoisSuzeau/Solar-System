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

                void initData() override;
                
            public:

                SolarSystem(sys_init_data data, TTF_Font *police);
                SolarSystem();
                ~SolarSystem();


                void loadSystem(int count, TTF_Font *police) override;
                void display(RenderData &render_data) override;
                void displaySkybox(RenderData &render_data) override;
                void displayName(RenderData &render_data) override;
                void displayAtmo(RenderData &render_data) override;
                void displayInfo(RenderData &render_data, PlaneteInformation *planete_info = nullptr) override;
                void displayAsteroidField(RenderData &render_data) override;


        };

        


#endif