/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : System.h

PURPOSE : header of the virtual System class
*/

#ifndef SYSTEM_H
#define SYSTEM_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <cstdlib>
        
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include "../../PlaneteInformation/PlaneteInformation.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class System
        {
            
            protected:

                std::string                 m_system_name;
                std::vector<std::string>    m_companion_name;
                int                         m_companion_count;

                
                
            public:

                
                virtual ~System() {};
                virtual void loadSystem(int count) = 0;
                virtual void display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, glm::vec3 sun_pos = glm::vec3(0.0, 0.0, 0.0), Shader *host_shader = nullptr, Shader *companion_shader = nullptr) = 0;
                virtual void displaySkybox(glm::mat4 &projection, glm::mat4 &modelview, bool hdr) = 0;
                virtual void displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos) = 0;
                virtual void displayAtmo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr) = 0;
                virtual void displayInfo(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, PlaneteInformation *planete_info = nullptr) = 0;
                
        };


#endif