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
        #include "../../Shader/Shader.hpp"

        #include "../../PlaneteInformation/PlaneteInformation.hpp"

        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>

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

                std::vector<PlaneteCreator*>            m_moons_creator;
                PlaneteCreator                          *m_host_creator;

                Atmosphere      *m_atmosphere;

                void initData() override;
            public:

                PlanetarySystem(sys_init_data data, TTF_Font *police);
                PlanetarySystem();
                ~PlanetarySystem();


                void loadSystem(int count, TTF_Font *police) override;
                void display(RenderData &render_data, glm::vec3 &camPos) override;
                void displaySkybox(RenderData &render_data) override;
                void displayName(RenderData &render_data, glm::vec3 &camPos) override;
                void displayAtmo(RenderData &render_data, glm::vec3 &camPos) override;
                void displayInfo(RenderData &render_data, glm::vec3 &camPos, PlaneteInformation *planete_info = nullptr) override;
                void displayAsteroidField(RenderData &render_data, glm::vec3 camPos) override;

        };


#endif