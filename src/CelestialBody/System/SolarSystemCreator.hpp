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


                System* FactoryMethod(sys_init_data data, TTF_Font *police, Shader *model_shader = nullptr) override
                {
                        puts("");
                        puts("");
                        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> System Creator : " << data.name_sys << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                        return new SolarSystem(data, police, model_shader);
                }


        };


#endif