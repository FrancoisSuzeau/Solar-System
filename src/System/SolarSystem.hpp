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

        #include "SystemCreator.hpp"
        #include "PlanetarySystemCreator.hpp"

        #include "../Objects/TexturedObjects/Star/Star.hpp"
        #include "../Renderers/TexturedRenderers/StarRenderer/StarRenderer.hpp"



        // #include "../../PlaneteInformation/PlaneteInformation.hpp"

        #include <cassert>
        
        
       
/********************************************************************* class definition *********************************************************************/

        class SolarSystem : public System
        {
            
            private:

                Star                            *m_sun = nullptr;
                Renderer                        *m_star_renderer = nullptr;

                // int                             m_planetarySYS_count;
                // int                             m_simple_planete_count;

                // FlareManager                    fm;

                // PlaneteInformation              *m_planete_info;

                // std::vector<SystemCreator*>    m_planetary_system;

                // void initData() override;
                
                
            public:

                // SolarSystem(sys_init_data data, TTF_Font *police);
                SolarSystem();
                ~SolarSystem();


                // void loadSystem(int count, TTF_Font *police) override;
                void render(DataManager &data_manager) override;
                void makeChanges(DataManager &data_manager) override;
                // void displayName(RenderData &render_data) override;
                // void displayAtmo(RenderData &render_data) override;
                // void renderInfos(RenderData &render_data, PlaneteInformation *planete_info = nullptr) override;
                // void displayAsteroidField(RenderData &render_data) override;
                // void displayRing(RenderData &render_data) override;

                // void setMostGravInfluence(RenderData &render_data) override;
                // void approchBody(Spaceship *ship) override;

                // void renderFlareSun(RenderData &render_data) override;


        };

        


#endif