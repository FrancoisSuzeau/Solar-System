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

        #include "../Planete/PlaneteRender.hpp"
        #include "../Planete/Planete.hpp"
        #include "../../OpenGlSketch/RenderData.hpp"

        #include "../../PlaneteInformation/PlaneteInformation.hpp"

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
                PlaneteRender                           *planete_render;


                void initData() override;
                void displayInfo(RenderData &render_data, Planete *planete, PlaneteInformation *planete_info);
            public:

                PlanetarySystem(sys_init_data data, TTF_Font *police);
                PlanetarySystem();
                ~PlanetarySystem();


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


        };


#endif