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
                void display(RenderData &render_data, glm::vec3 &camPos, Shader *host_shader = nullptr, Shader *companion_shader = nullptr, Shader *ring_shader = nullptr) override;
                void displaySkybox(RenderData &render_data) override;
                void displayName(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, Shader *name_render_shader = nullptr) override;
                void displayAtmo(RenderData &render_data, glm::vec3 &camPos, Shader *atmo_shader = nullptr) override;
                void displayInfo(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, bool hdr, std::vector<Shader *> shaders, PlaneteInformation *planete_info = nullptr) override;
                void displayAsteroidField(std::vector<glm::mat4> projection_view_mat, glm::vec3 camPos, bool hdr) override;

        };


#endif