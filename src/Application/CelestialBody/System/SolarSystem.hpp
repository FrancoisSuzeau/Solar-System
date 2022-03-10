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

        #include "../Planete/PlaneteRender.hpp"
        #include "../Planete/Planete.hpp"

        #include "../../PlaneteInformation/PlaneteInformation.hpp"
        #include "../AsteroidField/AsteroidField.hpp"

        #include "../../OpenGlSketch/RenderData.hpp"

        #include <cassert>
        
        
       
/********************************************************************* class definition *********************************************************************/

        class SolarSystem : public System
        {
            
            private:

                int                             m_planetarySYS_count;
                int                             m_simple_planete_count;
                Star                            *sun;
                Skybox                          *skybox;
                AsteroidField                   *m_asteroid_field;

                FlareManager                    fm;

                std::vector<Planete*>              m_planetes;
                PlaneteRender *planete_render;

                PlaneteInformation              *m_planete_info;

                std::vector<SystemCreator*>    m_planetary_system;

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
                void renderInfos(RenderData &render_data, PlaneteInformation *planete_info = nullptr) override;
                void displayAsteroidField(RenderData &render_data) override;
                void displayRing(RenderData &render_data) override;

                void setMostGravInfluence(RenderData &render_data) override;
                void approchBody(Spaceship *ship) override;

                void renderFlareSun(RenderData &render_data) override;


        };

        


#endif