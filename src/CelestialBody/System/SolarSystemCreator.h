/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : SolarSystemCreator.h

PURPOSE : header of the virtual SolarSystemCreator class
*/

#ifndef SSSYSTEMCREATOR_H
#define SSSYSTEMCREATOR_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include "SystemCreator.h"
        #include "SolarSystem.h"
       
/********************************************************************* class definition *********************************************************************/

        class SolarSystemCreator : public SystemCreator 
        {
            
            private:

                
                
            public:


                System* FactoryMethod(std::string name_system, int companion_count) override
                {
                    return new SolarSystem(name_system, companion_count);
                }


        };


#endif