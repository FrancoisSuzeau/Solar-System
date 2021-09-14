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

                void drawName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos)
                {
                        m_system->displayName(projection, modelview, camPos);
                }

                void drawAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr)
                {
                        m_system->displayAtmo(projection, modelview, camPos, hdr);
                }

                void drawInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, PlaneteInformation *planete_info = nullptr)
                {
                        m_system->displayInfo(projection, modelview, camPos, hdr, planete_info);
                }

                void drawSkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr)
                {
                        m_system->displaySkybox(projection, modelview, hdr);
                }

                void drawSystem(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos = glm::vec3(0.0, 0.0, 0.0))
                {
                        m_system->display(projection, modelview, camPos, hdr, sun_pos);
                }


        };


#endif