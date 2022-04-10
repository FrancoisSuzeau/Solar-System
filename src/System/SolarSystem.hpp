/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : System

NAMEFILE : SolarSystem.hpp

PURPOSE : header of the virtual SolarSystem class
*/

#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H


/********************************************************************* includes *********************************************************************/

        #include "System.hpp"
        #include "PlanetarySystemCreator.hpp"

        #include "../Objects/TexturedObjects/Star/Star.hpp"
        #include "../Renderers/TexturedRenderers/StarRenderer/StarRenderer.hpp"

        #include "../Objects/AsteroidField/AsteroidField.hpp"

        



        // #include "../../PlaneteInformation/PlaneteInformation.hpp"

        #include <cassert>
        
        
       
/********************************************************************* class definition *********************************************************************/

        class SolarSystem : public System
        {
            
            private:

                Star                            *m_sun = nullptr;
                Renderer                        *m_star_renderer = nullptr;
                
                std::vector<Planete*>           m_planetes;
                AsteroidField                   *m_asteroid_field = nullptr;

                // int                             m_planetarySYS_count;
                // int                             m_simple_planete_count;

                // FlareManager                    fm;

                // PlaneteInformation              *m_planete_info;

                std::vector<SystemCreator*>     m_planetary_systems;

                void            initDatas() override;
                
                
            public:

                SolarSystem(/*sys_init_data data, TTF_Font *police,*/Renderer *planete_renderer);
                ~SolarSystem();


                void loadSystem(/*int count, TTF_Font *police*/) override;
                void render(DataManager &data_manager) override;
                void makeChanges(DataManager &data_manager) override;
                // void displayName(RenderData &render_data) override;
                // void displayAtmo(RenderData &render_data) override;
                // void renderInfos(RenderData &render_data, PlaneteInformation *planete_info = nullptr) override;
                // void displayRing(RenderData &render_data) override;

                // void setMostGravInfluence(RenderData &render_data) override;
                // void approchBody(Spaceship *ship) override;

                // void renderFlareSun(RenderData &render_data) override;


        };

        


#endif