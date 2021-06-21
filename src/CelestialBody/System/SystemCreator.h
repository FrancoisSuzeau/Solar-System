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

        #include "System.h"
       
/********************************************************************* class definition *********************************************************************/

        class SystemCreator
        {
            
            protected:

                System *m_system;
                
            public:

                virtual ~SystemCreator() {delete m_system;};

                virtual System* FactoryMethod(std::string name_system, int companion_count) = 0;

                void MakingSystem(std::string name_system, int companion_count) 
                {
                   m_system = this->FactoryMethod(name_system, companion_count);
                   puts("");
                   puts("");
                   std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> System Creator : " << name_system << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                   m_system->loadSystem();
                }

                void drawSystem(glm::mat4 &projection, glm::mat4 &modelview)
                {
                        m_system->display(projection, modelview);
                }


        };


#endif