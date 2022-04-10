/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : System

NAMEFILE : PlanetarySystem.hpp

PURPOSE : header of the virtual PlanetarySystem class
*/

#ifndef PLSYSTEM_H
#define PLSYSTEM_H


/********************************************************************* includes *********************************************************************/

        #include "System.hpp"

        // #include "../../PlaneteInformation/PlaneteInformation.hpp"

        #include <string>
        #include <vector>
        #include <iostream>
        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <cassert>
       
/********************************************************************* class definition *********************************************************************/

        class PlanetarySystem : public System
        {
            
            private:

                std::vector<Planete*>                   m_moons;
                Planete                                 *m_host;
                // PlaneteRender                           *planete_render;


                void            initDatas() override;
                // void displayInfo(RenderData &render_data, Planete *planete, PlaneteInformation *planete_info);
            public:

                PlanetarySystem(/*sys_init_data data, TTF_Font *police,*/ Renderer *planete_renderer);
                ~PlanetarySystem();


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