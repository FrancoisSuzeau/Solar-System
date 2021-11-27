/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : SystemCreator.h

PURPOSE : header of the virtual SystemCreator class
*/

#ifndef SYSTEMCREATOR_H
#define SYSTEMCREATOR_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>

        #include "../../Shader/Shader.hpp"

        #include "System.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class SystemCreator
        {
            
            protected:

                System *m_system;
                
            public:

                virtual ~SystemCreator() {delete m_system;};

                virtual System* FactoryMethod(sys_init_data data, TTF_Font *police, Shader *model_shader = nullptr) = 0;

                bool MakingSystem(sys_init_data data, TTF_Font *police, Shader *model_shader = nullptr) 
                {
                        m_system = this->FactoryMethod(data, police, model_shader);
                        return true;
                }

                int loadSystem(int count, TTF_Font *police)
                {
                        m_system->loadSystem(count, police);
                        return 1;
                }

                void drawName(RenderData &render_data, glm::vec3 &camPos, Shader *name_render_shader = nullptr)
                {
                        m_system->displayName(render_data, camPos, name_render_shader);
                }

                void drawAtmo(RenderData &render_data, glm::vec3 &camPos, Shader *atmo_shader = nullptr)
                {
                        m_system->displayAtmo(render_data, camPos, atmo_shader);
                }

                void drawInfo(RenderData &render_data, glm::vec3 &camPos, std::vector<Shader *> shaders, PlaneteInformation *planete_info = nullptr)
                {
                        m_system->displayInfo(render_data, camPos, shaders, planete_info);
                }

                void drawSkybox(RenderData &render_data)
                {
                        m_system->displaySkybox(render_data);
                }

                void drawSystem(RenderData &render_data, glm::vec3 &camPos, Shader *shader_host = nullptr, Shader *companion_shader = nullptr, Shader *ring_shader = nullptr)
                {
                        m_system->display(render_data, camPos, shader_host, companion_shader, ring_shader);
                }

                void drawAsteroidField(std::vector<glm::mat4> projection_view_mat, glm::vec3 camPos, bool hdr)
                {
                        m_system->displayAsteroidField(projection_view_mat, camPos, hdr);
                }


        };


#endif