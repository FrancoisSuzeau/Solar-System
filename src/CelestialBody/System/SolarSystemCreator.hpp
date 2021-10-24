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

        #include "SystemCreator.hpp"
        #include "SolarSystem.hpp"

        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>
       
/********************************************************************* class definition *********************************************************************/

        class SolarSystemCreator : public SystemCreator 
        {
            
            private:

                
                
            public:


                System* FactoryMethod(std::string name_system, TTF_Font *police, int companion_count, Shader *model_shader = nullptr) override
                {
                        puts("");
                        puts("");
                        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> System Creator : " << name_system << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                        return new SolarSystem(name_system, police, companion_count, model_shader);
                }


        };


#endif