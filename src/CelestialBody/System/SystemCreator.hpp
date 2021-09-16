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

        #include "System.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class SystemCreator
        {
            
            protected:

                System *m_system;
                
            public:

                virtual ~SystemCreator() {delete m_system;};

                virtual System* FactoryMethod(std::string name_system, int companion_count) = 0;

                bool MakingSystem(std::string name_system, int companion_count) 
                {
                        m_system = this->FactoryMethod(name_system, companion_count);
                        return true;
                }

                int loadSystem(int count)
                {
                        m_system->loadSystem(count);
                        return 1;
                }

                void drawName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, Shader *name_render_shader = nullptr)
                {
                        m_system->displayName(projection, modelview, camPos, name_render_shader);
                }

                void drawAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *atmo_shader = nullptr)
                {
                        m_system->displayAtmo(projection, modelview, camPos, hdr, atmo_shader);
                }

                void drawInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, PlaneteInformation *planete_info = nullptr, Shader *text_shader = nullptr, Shader *square_shader = nullptr)
                {
                        m_system->displayInfo(projection, modelview, camPos, hdr, planete_info, text_shader, square_shader);
                }

                void drawSkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
                {
                        m_system->displaySkybox(projection, modelview, hdr);
                }

                void drawSystem(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos = glm::vec3(0.0, 0.0, 0.0), Shader *shader_host = nullptr, Shader *companion_shader = nullptr)
                {
                        m_system->display(projection, modelview, camPos, hdr, sun_pos, shader_host, companion_shader);
                }


        };


#endif