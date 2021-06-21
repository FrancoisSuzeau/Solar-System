/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : PlanetarySystemCreator.h

PURPOSE : header of the virtual PlanetarySystemCreator class
*/

#ifndef PLSYSTEMCREATOR_H
#define PLSYSTEMCREATOR_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include "SystemCreator.h"
        #include "PlanetarySystem.h"
       
/********************************************************************* class definition *********************************************************************/

        class PlanetarySystemCreator : public SystemCreator 
        {
            
            private:

                
                
            public:


                System* FactoryMethod(std::string name_system, int companion_count) override
                {
                    return new PlanetarySystem(name_system, companion_count);
                }


        };


#endif