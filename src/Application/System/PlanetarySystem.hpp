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

                // void displayInfo(RenderData &render_data, Planete *planete, PlaneteInformation *planete_info);
            public:

                PlanetarySystem(Renderer *planete_renderer, Renderer *ring_renderer,  Renderer *sphere_renderer, std::string const system_name);
                ~PlanetarySystem();


                void loadSystem(int count = 0) override;
                void render(DataManager &data_manager) override;
                void makeChanges(DataManager &data_manager) override;
                void clean() override;
                void renderNameAndInfo(DataManager &data_manager) override;
                // void displayName(RenderData &render_data) override;
                // void displayAtmo(RenderData &render_data) override;
                // void renderInfos(RenderData &render_data, PlaneteInformation *planete_info = nullptr) override;
                void renderRing(DataManager &data_manager) override;
                void renderAtmosphere(DataManager &data_manager) override;
                // void setMostGravInfluence(RenderData &render_data) override;
                // void approchBody(Spaceship *ship) override;

                // void renderFlareSun(RenderData &render_data) override;


        };


#endif